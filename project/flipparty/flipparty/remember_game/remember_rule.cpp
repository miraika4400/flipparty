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
    m_nTurnPlayer = 0;      // 度のプレイヤーのターンか
    m_nNumInput = 0;        //  プレイヤーが入力した回数
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
    // メンバ変数の初期化
    m_nTurn = 0;            // ターン数初期化
    m_nTurnPlayer = 0;      // 度のプレイヤーのターンか
    m_nNumInput = 0;        // プレイヤーが入力した回数
    m_IsinputEnd = false;   // プレイヤーが入力し終わったかのフラグ

    ZeroMemory(&FlipperData, sizeof(FlipperData));      // 見本データの配列
    ZeroMemory(&PlayerInput, sizeof(PlayerInput));      // プレイヤーの入力情報

    m_pPolygon = CPolygon::Create(D3DXVECTOR3(500.0f, 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// ポリゴンクラスのポインタ
    m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_UP));
    return S_OK;
}

//=============================================================================
// [Uninit]終了処理
//=============================================================================
void CRememjber_rule::Uninit(void)
{
    // ポリゴンの解放
#ifdef _DEBUG
        if (m_pPolygon != NULL)
        {
            m_pPolygon->Uninit();
            delete m_pPolygon;
            m_pPolygon = NULL;
        }
#endif // _DEBUG

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
        Comparison();   // 比較
    }
}

//=============================================================================
// [Draw]描画処理
//=============================================================================
void CRememjber_rule::Draw(void)
{
#ifdef _DEBUG
    m_pPolygon->Draw();
#endif // _DEBU
}

//=============================================================================
// [InputPlayer]プレイヤーの入力
//=============================================================================
void CRememjber_rule::InputPlayer(void)
{
    m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_UP));
    //プレイヤーの入力内容を比較用データに保存
    // 右
    if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lRz <= -10 ||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_UP))
    {
        PlayerInput[m_nNumInput] = CFlipper::FLIPPER_TYPE_RIGHT;
        m_nNumInput++;
    }
    // 左
    else if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lY <= -10 ||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_W))
    {
        PlayerInput[m_nNumInput] = CFlipper::FLIPPER_TYPE_LEFT;
        m_nNumInput++;
    }

// プレイヤーの最後の入力を見本に追加
    if (m_nNumInput == m_nTurn + 1)
    {
        m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_UP));
        FlipperData[m_nTurn] = PlayerInput[m_nTurn];// プレイヤーの入力を見本データに保存
        m_IsinputEnd = true;    // プレイヤーの入力完了フラグオン
        m_nTurn++;              // ターン数を増やす
        m_nNumInput = 0;        // 入力回数をリセット
    }
}

//=============================================================================
// [Comparison]入力されたデータの比較
//=============================================================================
void CRememjber_rule::Comparison(void)
{
    m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_DOWN));
    for (int nCnt = 0; nCnt < m_nTurn; nCnt++)
    {
        if (FlipperData[nCnt] != PlayerInput[nCnt])
        {
            // 外れた場合の処理
            m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_BATU));
        }
    }
    m_IsinputEnd = false;
}
