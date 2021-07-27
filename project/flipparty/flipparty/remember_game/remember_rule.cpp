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
#include "camera_remember.h"
#include "remember_rule.h"
#include "resource_texture.h"
#include "count_selection.h"
#include "bg.h"
#include "player_remember.h"
#include "camera_tps.h"
#include "mini_result.h"
#include "snow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_SPACE (300.0f) //　プレイヤー位置の間隔
#define INPUT_COUNT  (30)        // 入力してから再入力できるまでの待ち時間
#define FLIPPER_NONE D3DXToRadian(0.0f)
#define FLIPPER_UP_LEFT D3DXToRadian(70.0f)
#define FLIPPER_UP_RIGHT D3DXToRadian(-70.0f)
#define CAMERA_POS (150)        // カメラの基準位置

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
    m_nInputCount = 0;      // 入力を受け付けないカウント
    ZeroMemory(&m_pPolygon, sizeof(m_pPolygon));        // ポリゴンへのポインタ
    m_IsinputEnd = false;                               // プレイヤーが入力し終わったかのフラグ
    ZeroMemory(&FlipperData, sizeof(FlipperData));      // 見本データの配列
    ZeroMemory(&PlayerInput, sizeof(PlayerInput));      // プレイヤーの入力情報

    m_pPlayer.clear();// プレイヤーの初期化
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

    // ターン数の管理
    for (int nCnt = 0; nCnt < MAX_PLAYER_NUM; nCnt++)
    {
        m_aTurn[nCnt] = nCnt; // 入っている番号がプレイヤーの番号になる
    }

    m_nTurnPlayer = 0;      // どのプレイヤーのターンか
    m_nNumInput = 0;        // プレイヤーが入力した回数
    m_IsinputEnd = false;   // プレイヤーが入力し終わったかのフラグ
    m_nInputCount = 0;
    ZeroMemory(&FlipperData, sizeof(FlipperData));      // 見本データの配列
    ZeroMemory(&PlayerInput, sizeof(PlayerInput));      // プレイヤーの入力情報
    ZeroMemory(&m_apAnswer, sizeof(m_apAnswer));        // 回答のポリゴン表示
    m_IsPlay = true;                // ゲームをプレイ中かどうか

    //-----------------------------
    // 各オブジェクト生成
    //-----------------------------
    // 背景の生成
    CBg::Create();

    // カメラの生成
    CGame::SetCamera(CCameraRemember::Create());

    // 吹雪の生成
    //CSnow::Create();

    // プレイヤーの人数取得
    m_nNumPlayer = CCountSelect::GetPlayerNum();

    // プレイヤーの人数分プレイヤー生成
    for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
    {
        float posX = 0 + ((float)(nCntPlayer)*PLAYER_SPACE) / 2;// 位置の調整
        // プレイヤーの生成
        CPlayerRemember* pPlayer;
        pPlayer = CPlayerRemember::Create(D3DXVECTOR3(posX, -35.0f, 0.0f), nCntPlayer);

        m_pPlayer.push_back(pPlayer);
    }

    m_pPlayer.at(m_nTurnPlayer)->SetMoveFlag(true); // 最初のプレイヤーの操作フラグオン

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

    ChangeTurnUI();

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
    if (m_IsPlay)
    {
        // プレイヤーの入力
        InputPlayer();
    }

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

    // 手の状態をリセット
    ControllFlipper(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPER_STATE_NONE);
    ControllFlipper(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPER_STATE_NONE);

    // プレイヤーがターン数と同じ数入力したら
    if (m_nNumInput == m_nTurn + 1)
    {
        FlipperData[m_nTurn] = PlayerInput[m_nTurn];    // プレイヤーの入力を見本データに保存
        m_nNumInput = 0;                                // 入力回数をリセット
        m_nTurn++;                                      // ターン数を増やす
        TurnChange();                                   // プレイヤーのターン変更
    }
    else if(m_pPlayer[m_nTurnPlayer]->GetIsLoss())
    {
        TurnChange();                                   // プレイヤーのターン変更
    }

    //プレイヤーの入力内容を比較用データに保存
    // 右を押したとき
    if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lRz <= -10 ||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_UP))
    {
        PlayerInput[m_nNumInput] = CFlipper::FLIPPER_TYPE_RIGHT;
        m_nNumInput++;
        m_nInputCount = INPUT_COUNT;
        // 右手を上げる
        ControllFlipper(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
        Comparison();                                   // 入力内容の比較

    }
    // 左を押したとき
    else if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lY <= -10 ||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_W))
    {
        PlayerInput[m_nNumInput] = CFlipper::FLIPPER_TYPE_LEFT;
        m_nNumInput++;
        m_nInputCount = INPUT_COUNT;
        // 左手を上げる
        ControllFlipper(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
        Comparison();                                   // 入力内容の比較

    }

}

//=============================================================================
// [ChangeTurnUI]プレイヤー番号UIの変更処理
//=============================================================================
void CRememjber_rule::ChangeTurnUI(void)
{
    D3DXVECTOR2 Vtx[NUM_VERTEX];
    float fv = 1.0/ MAX_PLAYER_NUM;

    Vtx[0] = {0.0,fv * m_nTurnPlayer};
    Vtx[1] = {1.0,fv * m_nTurnPlayer};
    Vtx[2] = {0.0,fv * m_nTurnPlayer+ fv };
    Vtx[3] = {1.0,fv * m_nTurnPlayer+ fv };

    // uv座標のセット
    m_pPolygon[0]->SetTextureUV(Vtx);
}

//=============================================================================
// [TurnChange]ターンの変更
//=============================================================================
void CRememjber_rule::TurnChange(void)
{
// 現在のターンのプレイヤーの操作フラグオフ
    m_pPlayer[m_nTurnPlayer]->SetMoveFlag(false);

    // ターン変更
    if (m_nTurnPlayer == m_pPlayer.size() -1)
    {
        m_nTurnPlayer = 0;
    }
    else
    {
        m_nTurnPlayer++;
    }

    // 変更後のターンのプレイヤーの操作フラグオン
    m_pPlayer[m_nTurnPlayer]->SetMoveFlag(true);

    // カメラの位置変更
    CCameraRemember::GetInsutance()->SetDest(CAMERA_POS * m_nTurnPlayer);

   // テクスチャ変更
   ChangeTurnUI();
}

//=============================================================================
// [PlayerChange]プレイヤー番号の並び替え
// 引数: 脱落したプレイヤーの番号
//=============================================================================
void CRememjber_rule::PlayerChange(int nPlayerNum)
{
   // 脱落したプレイヤーの番号を配列の最後に移動
   // バブルソートで入れ替えれば最終的に順位と同じ順番になる
    for (int nData = nPlayerNum; nData < m_nNumPlayer - m_nLossPlayer; nData++)
    {
        int nSwap = m_aTurn[nData];// 入れ替え用変数

        m_aTurn[nData] = m_aTurn[nData + 1];
        m_aTurn[nData + 1] = nSwap;
    }

}

//=============================================================================
// [Comparison]入力されたデータの比較
//=============================================================================
void CRememjber_rule::Comparison(void)
{
    //// プレイヤーの入力フラグをオフにする
    //m_IsinputEnd = false;

    // データの比較
        if (FlipperData[m_nNumInput] != PlayerInput[m_nNumInput])
        {
            // 外れた場合×を表示
            m_apAnswer[m_nNumInput]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_BATU));
            // ミスしたプレイヤーの順位をつける
            Ranking();
            return;
        }
        else
        {
            m_apAnswer[m_nNumInput]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_MARU));
        }
}

//=============================================================================
// [Ranking]順位の設定
//=============================================================================
void CRememjber_rule::Ranking(void)
{
    m_nLossPlayer++;// 脱落したプレイヤーの人数をカウント
    PlayerChange(m_nTurnPlayer);    // プレイヤーの順番変更
    m_pPlayer[m_nTurnPlayer]->SetIsLoss(true);// 脱落フラグをたてる

    // プレイヤーが最後の1人になったらリザルト生成
    if (m_nNumPlayer - m_nLossPlayer == 1)
    {
        // 順位の設定
        for (int nRank = 0; nRank < m_nNumPlayer; nRank++)
        {
            m_pPlayer[m_aTurn[nRank]]->SetRank(nRank);
        }
        m_IsPlay = false;
        CMiniResult::Create();
    }
}

//=============================================================================
// [ControllFlipper] 羽を動かす処理
//=============================================================================
void CRememjber_rule::ControllFlipper(CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state)
{
    m_pPlayer[m_nTurnPlayer]->GetFlipper()->SetState(type, state);
    float fAngle = 0;

    switch (state)
    {
    case CFlipper::FLIPPER_STATE_NONE:
            fAngle = FLIPPER_NONE;
            break;
    case CFlipper::FLIPPERSTATE_UP:
        if (type== CFlipper::FLIPPER_TYPE_LEFT)
        {
            fAngle = FLIPPER_UP_LEFT;
        }
        else
        {
            fAngle = FLIPPER_UP_RIGHT;
        }

        break;
    }
        m_pPlayer[m_nTurnPlayer]->SetFlipperDist(type, fAngle);
}
