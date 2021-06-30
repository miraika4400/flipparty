////////////////////////////////////////////////////
//
//    scene3dクラスの処理[scene3d.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "resource_texture.h"
#include "renderer.h"
#include "manager.h"

//******************************
// マクロ定義
//******************************

//******************************
// 静的メンバ変数宣言
//******************************
CResourceTexture *CResourceTexture::m_pSingleTex = NULL; // テクスチャクラスのポインタ*シングルトン用
// テクスチャのパス
const std::string CResourceTexture::m_aTexPath[CResourceTexture::TEXTURE_MAX]
{
	"./data/Textures/title.png",        // タイトル背景
	"./data/Textures/tutorial_1.png",   // チュートリアル
	"./data/Textures/particle001.png",  // パーティクル*箱
	"./data/Textures/particle000.png",  // パーティクル*星
	"./data/Textures/particle004.png",  // パーティクル*円
	"./data/Textures/number.png",       // ナンバー
	"./data/Textures/debug_left.png",   // 左
	"./data/Textures/debug_right.png",  // 右
	"./data/Textures/debug_up.png",     // 上
	"./data/Textures/debug_down.png",   // 下
	"./data/Textures/1p_ui.png",        // 1pアイコン
	"./data/Textures/2p_ui.png",        // 2pアイコン
	"./data/Textures/3p_ui.png",        // 3pアイコン
	"./data/Textures/4p_ui.png",        // 4pアイコン
	"./data/Textures/select2.png",      // 人数選択UI2人
	"./data/Textures/select3.png",      // 人数選択UI3人
	"./data/Textures/select4.png",      // 人数選択UI4人
	"./data/Textures/Toon_Shadow.png",  // トゥーンシャドウ
	
    "./data/Textures/ui_up.png",        // UI「あげて」
    "./data/Textures/ui_down.png",      // UI「さげて」
    "./data/Textures/UI_maru.png",      // UI「〇」
    "./data/Textures/UI_batu.png",      // UI「×」
};

//===================================
// コンストラクタ
//===================================
CResourceTexture::CResourceTexture()
{
	memset(&m_apTexture, 0, sizeof(m_apTexture));
}

//===================================
// デストラクタ
//===================================
CResourceTexture::~CResourceTexture()
{
}

//=============================================================================
//モデルクラスのクリエイト処理
//=============================================================================
CResourceTexture * CResourceTexture::Create(void)
{
	if (m_pSingleTex == NULL)
	{
		// メモリ確保
		m_pSingleTex = new CResourceTexture;

		if (m_pSingleTex != NULL)
		{
			// メモリ確保に成功したとき
			m_pSingleTex->Load();
		}
		else
		{
			// メモリ確保に失敗したとき
			return NULL;
		}
	}
	
	return m_pSingleTex;
}

//===================================
// クラスの破棄
//===================================
void CResourceTexture::Release(void)
{
	if (m_pSingleTex != NULL)
	{
		// テクスチャ破棄
		m_pSingleTex->Unload();
		// メモリの破棄
		delete m_pSingleTex;
		m_pSingleTex = NULL;
	}
}

//===================================
// テクスチャ取得
//===================================
LPDIRECT3DTEXTURE9 CResourceTexture::GetTexture(TEXTURE_TYPE type)
{
	if (m_pSingleTex != NULL)
	{
		return m_pSingleTex->m_apTexture[type];
	}
	else
	{
		return NULL;
	}
}

//===================================
// テクスチャ読み込み
//===================================
void CResourceTexture::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ数分ループ
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		// テクスチャの生成
		D3DXCreateTextureFromFile(pDevice, m_aTexPath[nCnt].c_str(), &m_apTexture[nCnt]);
	}
}

//===================================
// テクスチャ破棄
//===================================
void CResourceTexture::Unload(void)
{
	// テクスチャ数分ループ
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			// テクスチャの破棄
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
