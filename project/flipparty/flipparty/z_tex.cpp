////////////////////////////////////////////////////
//
//    Z値テクスチャクラスの処理[Z_Tex.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "z_tex.h"
#include "manager.h"
#include "renderer.h"

//=============================
// マクロ定義
//=============================

//=============================
// 静的メンバ変数宣言
//=============================

//=============================
// コンストラクタ
//=============================
CZTex::CZTex()
{
	// 変数のクリア
	m_pZBufTex  = NULL;
	m_pZTexSurf = NULL;
	m_pZTexZBuf = NULL;
}

//=============================
// デストラクタ
//=============================
CZTex::~CZTex()
{
}

//=============================
// クリエイト
//=============================
CZTex * CZTex::Create(void)
{
	CZTex *pZtex = new CZTex;
	pZtex->Init();

	return pZtex;
}

//=============================
// 初期化処理
//=============================
HRESULT CZTex::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	UINT width;    // 幅
	UINT height;   // 高

	LPDIRECT3DSURFACE9 pTmpSf;
	pDevice->GetDepthStencilSurface(&pTmpSf);

	// デバイスの深度バッファの幅と高さを取得
	D3DSURFACE_DESC sufDesc;
	pTmpSf->GetDesc(&sufDesc);
	width = sufDesc.Width;
	height = sufDesc.Height;

	pTmpSf->Release();

	// テクスチャの生成
	D3DXCreateTexture(pDevice, width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pZBufTex);

	m_pZBufTex->GetSurfaceLevel(0, &m_pZTexSurf);
	m_pZTexSurf->GetDesc(&sufDesc);
	width = sufDesc.Width;
	height = sufDesc.Height;

	// 深度バッファサーフェイスの作成
	pDevice->CreateDepthStencilSurface(width, height, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, &m_pZTexZBuf, NULL);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CZTex::Uninit(void)
{
	if (m_pZBufTex != NULL)
	{
		m_pZBufTex->Release();
		m_pZBufTex = NULL;
	}

	if (m_pZTexSurf != NULL)
	{
		m_pZTexSurf->Release();
		m_pZTexSurf = NULL;
	}

	if (m_pZTexZBuf != NULL)
	{
		m_pZTexZBuf->Release();
		m_pZTexZBuf = NULL;
	}
}


//=============================
// テクスチャ書き込み開始
//=============================
void CZTex::Begin(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderTarget(0, m_pZTexSurf);
	pDevice->SetDepthStencilSurface(m_pZTexZBuf);
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0);
}

//=============================
// テクスチャ書き込み終了
//=============================
void CZTex::End(void)
{
}
