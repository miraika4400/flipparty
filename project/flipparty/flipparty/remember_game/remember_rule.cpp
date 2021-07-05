//=============================================================================
//
// 記憶ゲームルールクラス [remember_rule.cpp]
// Author : AYANOKUDO
//
//=============================================================================
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "joypad.h"
#include "keyboard.h"
#include "polygon.h"
#include "remember_rule.h"
#include "resource_texture.h"
#include "count_selection.h"
#include "player.h"
#include "camera_tps.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_SPACE (150.0f) //　プレイヤー位置の間隔
#define INPUT_COUNT (5)        // 入力してから再入力できるまでの待ち時間

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CRememjber_rule* CRememjber_rule::m_pinstace = nullptr;// インスタンスへのポインタ

//=============================================================================
// [CRememjber_rule]コンストラクタ
//=============================================================================
CRememjber_rule::CRememjber_rule()
{
    m_nTurn = 0;            // ターン数初期化
    m_nTurnPlayer = 0;      // どのプレイヤーのターンか
    m_nNumInput = 0;        //  プレイヤーが入力した回数
    m_nInputCount = 0;
    m_pPolygon = nullptr;   // ポリゴンへのポインタ
    m_IsinputEnd = false;   // プレイヤーが入力し終わったかのフラグ
    ZeroMemory(&FlipperData, sizeof(FlipperData));      // 見本データの配列
    ZeroMemory(&PlayerInput, sizeof(PlayerInput));      // プレイヤーの入力情報
}

//=============================================================================
// [~CRememjber_rule]デストラクタ
//=============================================================================
CRememjber_rule::~CRememjber_rule()
{

}

//=============================================================================
// [Create]インスタンス生成
//=============================================================================
CRememjber_rule * CRememjber_rule::Create(void)
{
    if (!m_pinstace)
    {
        m_pinstace = new CRememjber_rule;
        m_pinstace->Init();
    }
    return m_pinstace;
}

//=============================================================================
// [Init]初期化処理
//=============================================================================
HRESULT CRememjber_rule::Init(void)
{
    //-----------------------------
    // メンバ変数の初期化
    //-----------------------------
    m_nTurn = 0;            // ターン数初期化
    m_nTurnPlayer = 1;      // 度のプレイヤーのターンか
    m_nNumInput = 0;        // プレイヤーが入力した回数
    m_IsinputEnd = false;   // プレイヤーが入力し終わったかのフラグ
    m_nInputCount = 0;
    ZeroMemory(&FlipperData, sizeof(FlipperData));      // 見本データの配列
    ZeroMemory(&PlayerInput, sizeof(PlayerInput));      // プレイヤーの入力情報
    ZeroMemory(&m_apAnswer, sizeof(m_apAnswer));        // 回答のポリゴン表示

    //-----------------------------
    // 各オブジェクト生成
    //-----------------------------
    // カメラの生成
     CGame::SetCamera(CTpsCamera::Create());

    // プレイヤーの人数取得
     int nPlayerNum = CCountSelect::GetPlayerNum();

     // プレイヤーの人数分プレイヤー生成
     for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
     {
         float posX = 0 + ((float)(nCntPlayer)*PLAYER_SPACE) / 2;// 位置の調整
         // プレイヤーの生成
         CPlayer::Create(D3DXVECTOR3(posX, -35.0f, 0.0f), nCntPlayer);
     }

    // UIの生成
     for (int nCntUI = 0; nCntUI < MAX_TARN; nCntUI++)
     {
         float posX = 100 + ((float)(nCntUI) * PLAYER_SPACE) / 2;// 位置の調整
         m_apAnswer[nCntUI] = CPolygon::Create(D3DXVECTOR3(posX, 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// ポリゴンクラスのポインタ
     }
    m_pPolygon = CPolygon::Create(D3DXVECTOR3(500.0f, 100.0f, 0.0f), D3DXVECTOR3(32.0f, 32.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// ポリゴンクラスのポインタ
    m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_UP));
    return S_OK;
}

//=============================================================================
// [Uninit]終了処理
//=============================================================================
void CRememjber_rule::Uninit(void)
{
    //-----------------------------
    // 各オブジェクトの解放
    //-----------------------------
    // ポリゴンの解放
#ifdef _DEBUG
        if (m_pPolygon != NULL)
        {
            m_pPolygon->Uninit();
            delete m_pPolygon;
            m_pPolygon = NULL;
        }
#endif // _DEBUG

        // ポリゴンの解放
        for (int nCnt = 0; nCnt < MAX_TARN; nCnt++)
        {
            m_apAnswer[nCnt]->Uninit();
            delete m_apAnswer[nCnt];
            m_apAnswer[nCnt] = nullptr;
        }

        m_pinstace = nullptr;
}

//=============================================================================
// [Uninit]更新処理
//=============================================================================
void CRememjber_rule::Update(void)
{
    // プレイヤーの入力
    InputPlayer();

    // 入力された数がターン数と同じになった
    if (m_IsinputEnd)
    {
        Comparison();   // 入力内容の比較
    }

    // リザルト遷移
    if (m_nTurn== MAX_TARN)
        CManager::SetMode(CManager::MODE_TITLE);
}

//=============================================================================
// [Draw]描画処理
//=============================================================================
void CRememjber_rule::Draw(void)
{
#ifdef _DEBUG
    m_pPolygon->Draw();
#endif // _DEBU

    for (int nCnt = 0; nCnt < MAX_TARN; nCnt++)
    {
        m_apAnswer[nCnt]->Draw();
    }
}

//=============================================================================
// [InputPlayer]プレイヤーの入力
//=============================================================================
void CRememjber_rule::InputPlayer(void)
{
    // 入力待ち時間が残っているときは処理を行わない
    if (m_nInputCount > 0)
    {
        // プレイヤーの入力できるまでのカウントを減らす
        m_nInputCount--;
        return;

    }

    // テクスチャの設定
    m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_UP));

    //プレイヤーの入力内容を比較用データに保存
    // 右を押したとき
    if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lRz <= -10 ||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_UP))
    {
        PlayerInput[m_nNumInput] = CFlipper::FLIPPER_TYPE_RIGHT;
        m_nNumInput++;
        m_nInputCount = INPUT_COUNT;
    }
    // 左を押したとき
    else if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lY <= -10 ||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_W))
    {
        PlayerInput[m_nNumInput] = CFlipper::FLIPPER_TYPE_LEFT;
        m_nNumInput++;
        m_nInputCount = INPUT_COUNT;
    }

// プレイヤーの最後の入力を見本に追加
    if (m_nNumInput == m_nTurn + 1)
    {
        m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_UP));
        FlipperData[m_nTurn] = PlayerInput[m_nTurn];    // プレイヤーの入力を見本データに保存
        m_IsinputEnd = true;                            // プレイヤーの入力完了フラグオン
        m_nTurn++;                                      // ターン数を増やす
        m_nNumInput = 0;                                // 入力回数をリセット
        // プレイヤーのターン変更
        m_nTurnPlayer= (m_nTurn+1) % 4;
    }
}

//=============================================================================
// [Comparison]入力されたデータの比較
//=============================================================================
void CRememjber_rule::Comparison(void)
{
    // プレイヤーの入力フラグをオフにする
    m_IsinputEnd = false;

    // テクスチャの設定
    m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_DOWN));

    for (int nCnt = 0; nCnt < m_nTurn; nCnt++)
    {
        if (FlipperData[nCnt] != PlayerInput[nCnt])
        {
            // 外れた場合×を表示
            m_apAnswer[nCnt]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_BATU));
        }
        else
        {
            m_apAnswer[nCnt]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_MARU));
        }
    }

}
