////////////////////////////////////////////////////
//
//    タイトルクラスの処理[title.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "sound.h"
#include "resource_texture.h"
#include "count_selection.h"

//**********************************
// 静的メンバ変数宣言
//**********************************

//**********************************
// マクロ定義
//**********************************

//=============================
// コンストラクタ
//=============================
CTitle::CTitle()
{
	m_pPolygon = NULL;
}

//=============================
// デストラクタ
//=============================
CTitle::~CTitle()
{
}

//=============================
// クリエイト
//=============================
CTitle * CTitle::Create(void)
{
	// メモリの確保
	CTitle *pTitle = new CTitle;
	// 初期化
	pTitle->Init();
	return pTitle;
}

//=============================
// 初期化処理
//=============================
HRESULT CTitle::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TITLE));
	
	// 人数選択クラスの生成
	CCountSelect::Create();
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CTitle::Uninit(void)
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


//=============================
// 更新処理
//=============================
void CTitle::Update(void)
{
	// ポリゴンの更新処理
	m_pPolygon->Update();

	//if( CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) || 
	//	CManager::GetMouse()->GetMouseTrigger(0) || 
	//	CManager::GetJoypad()->GetJoystickTrigger(3, 0)||
	//	CManager::GetJoypad()->GetJoystickTrigger(11, 0))
	//{
	//	CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
	//}
}


//=============================
// 描画処理
//=============================
void CTitle::Draw(void)
{
	// ポリゴンの描画処理
	m_pPolygon->Draw();
}
