//=============================================================================
//
// 各ゲームのチュートリアルクラス [mini_tutorial.cpp]
// Author : AYANO KUDO
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "mini_tutorial.h"
#include "manager.h"
#include "joypad.h"
#include "keyboard.h"
#include "renderer.h"
#include "mouse.h"
#include "resource_texture.h"
#include "polygon.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CMini_Tutorial::m_pTexture = nullptr;    // テクスチャへのポインタ
CResourceTexture::TEXTURE_TYPE CMini_Tutorial::m_TextureData = CResourceTexture::TEXTURE_TUTORIAL;

//=============================================================================
// [CMini_Tutorial]コンストラクタ
//=============================================================================
CMini_Tutorial::CMini_Tutorial()
{
    m_pPolygon = NULL;
    m_IsTutorialEnd = false;
}

//=============================================================================
// [~CMini_Tutorial]デストラクタ
//=============================================================================
CMini_Tutorial::~CMini_Tutorial()
{
}

//=============================================================================
// [Create]オブジェクトの生成
//=============================================================================
CMini_Tutorial *CMini_Tutorial::Create(CResourceTexture::TEXTURE_TYPE texture)
{
    CMini_Tutorial *pMiniTutorial = new CMini_Tutorial;

    m_TextureData = texture;

    // 初期化処理
    pMiniTutorial->Init();

    return pMiniTutorial;
}

//=============================================================================
// [Init]初期化処理
//=============================================================================
HRESULT CMini_Tutorial::Init(void)
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    // テクスチャの生成
    m_pTexture = CResourceTexture::GetTexture(m_TextureData);

    m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
        D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
        D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

    m_pPolygon->BindTexture(m_pTexture);
    return S_OK;
}

//=============================================================================
// [Uninit]終了処理
//=============================================================================
void CMini_Tutorial::Uninit(void)
{
    if (m_pPolygon != NULL)
    {
        // ポリゴンの終了処理
        m_pPolygon->Uninit();

        // メモリの解放
        delete m_pPolygon;
        m_pPolygon = NULL;
    }

    // 開放処理
    Release();
}

//=============================================================================
// [Update]更新処理
//=============================================================================
void CMini_Tutorial::Update(void)
{
    // ENTERキー押下でゲーム開始フラグ
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
        CManager::GetMouse()->GetMouseTrigger(0) ||
        CManager::GetJoypad()->GetJoystickTrigger(3, 0))
    {
        m_IsTutorialEnd = true;// チュートリアル終了フラグをtrueにする
    }

}

//=============================================================================
// [Draw]描画処理
//=============================================================================
void CMini_Tutorial::Draw(void)
{
    // ポリゴンの描画処理
    m_pPolygon->Draw();
}
