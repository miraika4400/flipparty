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
#include "number.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_SPACE (300.0f)             //　プレイヤー位置の間隔
#define INPUT_COUNT  (30)                 // 入力してから再入力できるまでの待ち時間

#define CAMERA_POS (150)                        // カメラの基準位置
#define SNOWSTORM_TURN (m_nNumPlayer * 2)       // 吹雪の登場ターン

// 羽の角度の設定
#define FLIPPER_NONE D3DXToRadian(0.0f)         // デフォルトのとき
#define FLIPPER_UP_RIGHT D3DXToRadian(-70.0f)   // 右を上げているとき
#define FLIPPER_UP_LEFT D3DXToRadian(70.0f)     // 左をあげているとき

// 答えのUIの設定
#define ANSWER_UI_POS  D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f)    // 位置
#define ANSWER_UI_SIZE D3DXVECTOR3(128,64,0.0f)                     // サイズ

// 制限時間の設定
#define TIME_LIMIT (3)                                    // 制限時間
#define MAX_INPUT_TIME (TIME_LIMIT * 60)                  // 制限時間(フレーム)
#define TIME_LIMIT_UI_POS {SCREEN_WIDTH / 2.0f,200,0}     // UIの位置
#define TIME_LIMIT_UI_SIZE {50,50,0}                      // UIのサイズ
#define TIME_LIMIT_UI_COLOR {1.0,1.0,1.0,1.0}             // UIの色

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CRememjber_rule* CRememjber_rule::m_pinstace = nullptr;// インスタンスへのポインタ
CRememjber_rule::UI_DATA CRememjber_rule::m_UIData[MAX_UI_REMEMBER] = 
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
    m_nInputTime = 0;       // 入力の制限時間
    ZeroMemory(&m_pPolygon, sizeof(m_pPolygon));        // ポリゴンへのポインタ
    m_IsinputEnd = false;                               // プレイヤーが入力し終わったかのフラグ
    ZeroMemory(&m_FlipperData, sizeof(m_FlipperData));      // 見本データの配列
    ZeroMemory(&m_PlayerInput, sizeof(m_PlayerInput));      // プレイヤーの入力情報
    m_pNumber = nullptr;
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
CRememjber_rule *CRememjber_rule::Create(void)
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
    m_nInputCount = 0;      // プレイヤーが入力できるようになるまでのカウント
    m_nInputTime = MAX_INPUT_TIME;                   // 入力できる制限時間の回復
    ZeroMemory(&m_FlipperData, sizeof(m_FlipperData));      // 見本データの配列
    ZeroMemory(&m_PlayerInput, sizeof(m_PlayerInput));      // プレイヤーの入力情報
    ZeroMemory(&m_apAnswer, sizeof(m_apAnswer));        // 回答のポリゴン表示
    m_IsPlay = true;                // ゲームをプレイ中かどうか
    m_IsSnow = false;       // 吹雪が出ているかどうか

    //-----------------------------
    // 各オブジェクト生成
    //-----------------------------
    // 背景の生成
    CBg::Create();

    // カメラの生成
	CManager::SetCamera(CCameraRemember::Create());

    // プレイヤーの人数取得
    m_nNumPlayer = CCountSelect::GetPlayerNum();

    // プレイヤーの人数分プレイヤー生成
    for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
    {
        float posX = 0 + ((float)(nCntPlayer)*PLAYER_SPACE) / 2 * -1;// 位置の調整
        // プレイヤーの生成
        CPlayerRemember* pPlayer;
        pPlayer = CPlayerRemember::Create(D3DXVECTOR3(posX, -35.0f, 0.0f), nCntPlayer);

        m_pPlayer.push_back(pPlayer);
    }

    m_pPlayer.at(m_nTurnPlayer)->SetMoveFlag(true); // 最初のプレイヤーの操作フラグオン

    // UIの生成
        m_apAnswer = CPolygon::Create(ANSWER_UI_POS, ANSWER_UI_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// ポリゴンクラスのポインタ

    for (int nCntUI = 0; nCntUI < MAX_UI_REMEMBER; nCntUI++)
    {
        m_pPolygon[nCntUI] = CPolygon::Create(m_UIData[nCntUI].pos, m_UIData[nCntUI].size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// ポリゴンクラスのポインタ
        m_pPolygon[nCntUI]->BindTexture(CResourceTexture::GetTexture(m_UIData[nCntUI].pTexture));
    }

    m_pNumber = CNumber::Create(TIME_LIMIT, TIME_LIMIT_UI_POS, TIME_LIMIT_UI_SIZE, TIME_LIMIT_UI_COLOR);

    ChangeTurnUI();
    CManager::GetSound()->Play(CSound::LABEL_BGM_REMEMBER_GAME);

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

        // ポリゴンの解放
            m_apAnswer->Uninit();
            delete m_apAnswer;
            m_apAnswer = nullptr;

            m_pinstace = nullptr;

            m_pNumber->Uninit();
            CManager::GetSound()->Stop();
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

    // 吹雪の生成
    if (IsSnowstormTurn())
    {
        m_IsSnow = true;// フラグをオンにする
        CSnow::Create();// 生成
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
        // あっているかのUI描画
    if (m_nInputCount)
    {
        m_apAnswer->Draw();
    }

    // 制限時間の描画
    if (m_pNumber)
    {
    m_pNumber->Draw();
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

    // 手の状態をリセット
    ControllFlipper(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPER_STATE_NONE);
    ControllFlipper(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPER_STATE_NONE);

    // プレイヤーがターン数と同じ数入力したら
    if (m_nNumInput == m_nTurn + 1)
    {
        m_nNumInput = 0;                                // 入力回数をリセット
        m_nTurn++;                                      // ターン数を増やす
        TurnChange();                                   // プレイヤーのターン変更
    }
    else if (m_pPlayer[m_nTurnPlayer]->GetIsLoss())
    {
        TurnChange();                                   // プレイヤーのターン変更
    }

    // 条件の定義
    // 右手を上げる条件
    bool IsRight = CManager::GetJoypad()->GetStick(m_nTurnPlayer).lRz <= -10 || CManager::GetKeyboard()->GetKeyTrigger(DIK_UP);
    // 左手をあげる条件
    bool IsLeft = CManager::GetJoypad()->GetStick(m_nTurnPlayer).lY <= -10 || CManager::GetKeyboard()->GetKeyTrigger(DIK_W);

    if (IsRight)
    {    // 右を上げたとき
        SetRememberData(CFlipper::FLIPPER_TYPE_LEFT);
    }
    else if (IsLeft)
    {    // 左を上げたとき
        
        SetRememberData(CFlipper::FLIPPER_TYPE_RIGHT);
    }

    // 入力できる制限時間を過ぎたら脱落
    m_nInputTime--;
    m_pNumber->SetNumber(((int)m_nInputTime / 60)+1);

    if ((m_nInputTime == 0))
    {
        Ranking();
        m_nInputTime = MAX_INPUT_TIME;                   // 入力できる制限時間の回復
    }
}

//=============================================================================
// [ChangeTurnUI]プレイヤー番号UIの変更処理
//=============================================================================
void CRememjber_rule::ChangeTurnUI(void)
{
    D3DXVECTOR2 Vtx[NUM_VERTEX];
    float fv = 1.0/ MAX_PLAYER_NUM;// 1枚当たりの大きさ

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
    if (m_nTurnPlayer == m_pPlayer.size() - 1)
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
    CCameraRemember::GetInsutance()->SetDest(CAMERA_POS * m_nTurnPlayer*-1);

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
    // 見本と入力したデータの比較
        if (m_FlipperData[m_nNumInput] != m_PlayerInput[m_nNumInput])
        {
            // 外れた場合×を表示
            m_apAnswer->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_BATU));
            CManager::GetSound()->Play(CSound::LABEL_SE_MISS);
            // ミスしたプレイヤーの順位をつける
            Ranking();
        }
        else
        {   // 正解の場合〇を表示
            m_apAnswer->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_MARU));
            CManager::GetSound()->Play(CSound::LABEL_SE_OK);
        }
}

//=============================================================================
// [Ranking]順位の設定
//=============================================================================
void CRememjber_rule::Ranking(void)
{
    m_nLossPlayer++;                // 脱落したプレイヤーの人数をカウント
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
        CSnow::GetInstancce()->CSnow::Uninit();
        CMiniResult::Create();
    }
}

//=============================================================================
// [SetRememberData] 入力した後の処理
//=============================================================================
void CRememjber_rule::SetRememberData(CFlipper::FLIPPER_TYPE type)
{
    m_PlayerInput[m_nNumInput] = type;                 // 入力した情報を保存

    // 入力した回数がターンと同じとき
    if (m_nNumInput == m_nTurn)
        m_FlipperData[m_nTurn] = m_PlayerInput[m_nTurn];    // プレイヤーの入力を見本データに保存

    Comparison();                                   // 入力内容の比較

    m_nInputCount = INPUT_COUNT;                     // 再入力できるまでの時間をセット
    m_nInputTime = MAX_INPUT_TIME;                   // 入力できる制限時間の回復
    ControllFlipper(type, CFlipper::FLIPPERSTATE_UP);// 手をあげるモーションにする
    m_nNumInput++;                                   // 入力した回数の追加
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

//=============================================================================
// [IsSnowstormTurn] 吹雪を発生させるかどうかの判定
// 返り値: 判定結果を返す
//=============================================================================
bool CRememjber_rule::IsSnowstormTurn(void)
{
    // 吹雪生成用条件
    // 条件：吹雪が出ていない、かつ吹雪出現ターンになったか
    bool IsSnowstormTurn = !m_IsSnow && m_nTurn == SNOWSTORM_TURN;

    return IsSnowstormTurn;
}
