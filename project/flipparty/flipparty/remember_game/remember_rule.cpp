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
#include "bg.h"
#include "player_remember.h"
#include "camera_tps.h"
#include "mini_result.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_SPACE (150.0f) //　プレイヤー位置の間隔
#define INPUT_COUNT (5)        // 入力してから再入力できるまでの待ち時間

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CRememjber_rule* CRememjber_rule::m_pinstace = nullptr;// インスタンスへのポインタ
CRememjber_rule::UI_DATA CRememjber_rule::UIData[MAX_UI_REMEMBER] = 
{
    { D3DXVECTOR3(500, 100.0f, 0.0f), D3DXVECTOR3(64.f, 16.f, 0.0f) ,CResourceTexture::TEXTURE_UI_000 },
    { D3DXVECTOR3(700, 100.0f, 0.0f), D3DXVECTOR3(128.f, 32.f, 0.0f) ,CResourceTexture::TEXTURE_UI_001 }
};
//=============================================================================
// [CRememjber_rule]コンストラクタ
//=============================================================================
CRememjber_rule::CRememjber_rule()
{
    m_nNumPlayer = 0;       // プレイヤーの人数
    m_nLossPlayer = 0;      // 脱落したプレイヤーの人数
    m_nTurn = 0;            // ターン数初期化
    m_nTurnPlayer = 0;      // どのプレイヤーのターンか
    m_nNumInput = 0;        //  プレイヤーが入力した回数
    m_nInputCount = 0;
    ZeroMemory(&m_pPolygon, sizeof(m_pPolygon));        // ポリゴンへのポインタ
    m_IsinputEnd = false;                               // プレイヤーが入力し終わったかのフラグ
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
    m_nLossPlayer = 0;      // 脱落したプレイヤーの人数
    m_nTurn = 0;            // ターン数初期化
    m_nTurnPlayer = 1;      // どのプレイヤーのターンか
    m_nNumInput = 0;        // プレイヤーが入力した回数
    m_IsinputEnd = false;   // プレイヤーが入力し終わったかのフラグ
    m_nInputCount = 0;
    ZeroMemory(&FlipperData, sizeof(FlipperData));      // 見本データの配列
    ZeroMemory(&PlayerInput, sizeof(PlayerInput));      // プレイヤーの入力情報
    ZeroMemory(&m_apAnswer, sizeof(m_apAnswer));        // 回答のポリゴン表示

    //-----------------------------
    // 各オブジェクト生成
    //-----------------------------
    // 背景の生成
    CBg::Create();

    // カメラの生成
    CGame::SetCamera(CTpsCamera::Create());

    // プレイヤーの人数取得
    m_nNumPlayer = CCountSelect::GetPlayerNum();

    // プレイヤーの人数分プレイヤー生成
    for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
    {
        float posX = 0 + ((float)(nCntPlayer)*PLAYER_SPACE) / 2;// 位置の調整
        // プレイヤーの生成
        m_pPlayer[nCntPlayer] = CPlayerRemember::Create(D3DXVECTOR3(posX, -35.0f, 0.0f), nCntPlayer);
    }

    // UIの生成
    for (int nCntUI = 0; nCntUI < MAX_TARN; nCntUI++)
    {
        float posX = 100 + ((float)(nCntUI)* 100) / 2;// 位置の調整
        m_apAnswer[nCntUI] = CPolygon::Create(D3DXVECTOR3(posX, 200.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// ポリゴンクラスのポインタ
    }

    for (int nCntUI = 0; nCntUI < MAX_UI_REMEMBER; nCntUI++)
    {
        m_pPolygon[nCntUI] = CPolygon::Create(UIData[nCntUI].pos, UIData[nCntUI].size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// ポリゴンクラスのポインタ
        m_pPolygon[nCntUI]->BindTexture(CResourceTexture::GetTexture(UIData[nCntUI].pTexture));
    }
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
    for (int nCntUI = 0; nCntUI < MAX_UI_REMEMBER; nCntUI++)
    {
        if (m_pPolygon != nullptr)
        {
            m_pPolygon[nCntUI]->Uninit();
            delete m_pPolygon[nCntUI];
            m_pPolygon[nCntUI] = nullptr;
        }
    }
#ifdef _DEBUG
        // ポリゴンの解放
        for (int nCntUI = 0; nCntUI < MAX_TARN; nCntUI++)
        {
            m_apAnswer[nCntUI]->Uninit();
            delete m_apAnswer[nCntUI];
            m_apAnswer[nCntUI] = nullptr;
        }

        m_pinstace = nullptr;
#endif // _DEBUG
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
    // UIの描画
    for (int nCntUI = 0; nCntUI < MAX_UI_REMEMBER; nCntUI++)
    {
        m_pPolygon[nCntUI]->Draw();
    }

#ifdef _DEBUG
    for (int nCntUI = 0; nCntUI < MAX_TARN; nCntUI++)
    {
        m_apAnswer[nCntUI]->Draw();
    }
#endif // _DEBUG
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
        FlipperData[m_nTurn] = PlayerInput[m_nTurn];    // プレイヤーの入力を見本データに保存
        m_IsinputEnd = true;                            // プレイヤーの入力完了フラグオン
        m_nTurn++;                                      // ターン数を増やす
        m_nNumInput = 0;                                // 入力回数をリセット
        TurnChange();                                   // プレイヤーのターン変更
    }
}

//=============================================================================
// [TurnChange]ターンの変更
//=============================================================================
void CRememjber_rule::TurnChange(void)
{
   m_nTurnPlayer = (m_nTurn + 1) % m_nNumPlayer;

   // プレイヤーが脱落していた場合
   if (m_pPlayer[m_nTurnPlayer]->GetIsLoss() == false)
   {
       // 脱落しているプレイヤーを飛ばす
       // テクスチャ変更
   }

}

//=============================================================================
// [Comparison]入力されたデータの比較
//=============================================================================
void CRememjber_rule::Comparison(void)
{
    // プレイヤーの入力フラグをオフにする
    m_IsinputEnd = false;

    // データの比較
    for (int nCnt = 0; nCnt < m_nTurn; nCnt++)
    {
        if (FlipperData[nCnt] != PlayerInput[nCnt])
        {
            // 外れた場合×を表示
            m_apAnswer[nCnt]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_BATU));

            // ミスしたプレイヤーの順位をつける
            Ranking();
            return;
        }
        else
        {
            m_apAnswer[nCnt]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_MARU));
        }
    }

}

//=============================================================================
// [Ranking]順位の設定
//=============================================================================
void CRememjber_rule::Ranking(void)
{
    // 順位の設定
    m_pPlayer[m_nTurnPlayer]->SetRank(m_nNumPlayer - m_nLossPlayer);
    m_pPlayer[m_nTurnPlayer]->SetIsLoss(true);// 脱落フラグをたてる

    // プレイヤーが最後の1人になったらリザルト生成
    if (m_nNumPlayer - m_nLossPlayer == 1)
    {
        CMiniResult::Create();
    }
    m_nLossPlayer++;// 脱落したプレイヤーの人数をカウント
}
