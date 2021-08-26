//=============================================================================
//
// seaヘッダ [sea.cpp]
// Author : 増澤 未来
//
//=============================================================================

//******************************
// インクルード
//******************************
#include "sea.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"

//*****************************
// マクロ定義
//*****************************
#define BMP_TEX_PATH     "data/Textures/sea/BMP_water4.png"   // バンプマップテクスチャのパス
#define BMP_TEX_PATH2    "data/Textures/sea/BMP_water4.png"   // バンプマップテクスチャのパス
#define CUBE_TEX_PATH    "data/Textures/sea/cube_sky.dds"   // キューブテクスチャのパス
#define SHADER_PATH      "data/HLSL/SeaShader.fx"        // HLSLファイルのパス
#define SIZE D3DXVECTOR3(2500.0f,1.0f,2500.0f)

//#define COLOR D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)               // カラー
//#define COLOR D3DXCOLOR(0.3f,0.4f,1.0f,1.0f)             // カラー

// キューブテクスチャ割合
#define CUB_RATE_DIRTY  4.0f
#define CUB_RATE_NORMAL 4.0f
#define CUB_RATE_EVENING 6.0f

// カラー
#define COLOR_DIRTY D3DXCOLOR( 0.5f,0.0f,0.3f,1.0f)   
#define COLOR_NORMAL D3DXCOLOR(0.3f,0.4f,1.0f,1.0f)
#define COLOR_EVENING D3DXCOLOR(1.0f,0.2f,0.1f,1.0f)

//*****************************
// 静的メンバ変数宣言
//*****************************
CObject3dShader::Shader CSea::m_shader = {};  // シェーダー構造体
LPDIRECT3DTEXTURE9 CSea::m_apBmpTex[2] = {};

//******************************
// コンストラクタ
//******************************
CSea::CSea() :CObject3dShader(OBJTYPE_SEA)
{
	m_fWaveaRate = 0.0f;
	m_fWaveSpeed = 0.0f;
	m_seaType = TYPE_DIRTY;
}

//******************************
// デストラクタ
//******************************
CSea::~CSea()
{
}

//******************************
// クリエイト
//******************************
CSea * CSea::Create(const D3DXVECTOR3 pos, const float fWaveSeed, SEA_TYPE seaType)
{
	// メモリの確保
	CSea *pSea;
	pSea = new CSea;

	// タイプの設定
	pSea->m_seaType = seaType;
	// 初期化
	pSea->Init();

	// 各値の代入・セット
	pSea->SetPos(pos);               // 座標のセット

	pSea->BindTexture(m_apBmpTex[0]);
	pSea->m_fWaveSpeed = fWaveSeed;
	return pSea;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CSea::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// HLSLファイルの読み込み
	D3DXCreateEffectFromFile(pDevice, SHADER_PATH, NULL, NULL, 0, NULL, &m_shader.pEffect, NULL);
	// テクニック名
	sprintf(&m_shader.achTechniqueName[0], "%s", "Shader");

	// キューブテクスチャの生成
	D3DXCreateCubeTextureFromFile(pDevice, CUBE_TEX_PATH, &m_shader.pCubeTex);

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BMP_TEX_PATH, &m_apBmpTex[0]);
	D3DXCreateTextureFromFile(pDevice, BMP_TEX_PATH2, &m_apBmpTex[1]);
	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CSea::Unload(void)
{
	if (m_shader.pEffect != NULL)
	{
		m_shader.pEffect->Release();
		m_shader.pEffect = NULL;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apBmpTex[nCnt] != NULL)
		{
			m_apBmpTex[nCnt]->Release();
			m_apBmpTex[nCnt] = 0;
		}
	}
}

//******************************
// 初期化処理
//******************************
HRESULT CSea::Init(void)
{
	if (FAILED(CObject3dShader::Init()))
	{
		return E_FAIL;
	}

	// シェーダーのセット
	SetShader(m_shader);

	// タイプによって色分け
	switch (m_seaType)
	{
	case TYPE_DIRTY:
		// 色の設定　
		SetColor(COLOR_DIRTY);

		break;

	case TYPE_NORMAL:
		SetColor(COLOR_NORMAL);
		break;

	case TYPE_EVENING:
		SetColor(COLOR_EVENING);
		break;
	default:
		break;
	}

	SetSize(SIZE);
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CSea::Uninit(void)
{
	CObject3dShader::Uninit();
}

//******************************
// 更新処理
//******************************
void CSea::Update(void)
{
	//SetRot(D3DXVECTOR3(0.0001f,0.0f,0.01f));
	m_fWaveaRate += m_fWaveSpeed;
}

//******************************
// 描画処理
//******************************
void CSea::Draw(void)
{
	CObject3dShader::Draw();
}

//******************************
// HLSLに値を送る
//******************************
void CSea::SetShaderValue(void)
{
	D3DXVECTOR3 eye = D3DXVECTOR3(0, 0, -2);
	GetShader().pEffect->SetFloatArray("Eye", (float*)&eye, 3);
	GetShader().pEffect->SetFloatArray("SpecularColor", (float*)&D3DXVECTOR4(1, 1, 1, 1), 4);
	GetShader().pEffect->SetTexture("Tex", m_apBmpTex[0]);
	GetShader().pEffect->SetTexture("TexNormal", m_apBmpTex[0]);
	GetShader().pEffect->SetTexture("TexNormal2", m_apBmpTex[1]);
	GetShader().pEffect->SetTexture("CubeTex", GetShader().pCubeTex);

	float fWave = sinf(m_fWaveaRate);

	if (fWave < 0) fWave *= -1;
	GetShader().pEffect->SetFloat("fWaveRate", fWave);
	GetShader().pEffect->SetFloat("fWaveMove", m_fWaveaRate);

	switch (m_seaType)
	{
	case TYPE_DIRTY:
		// 色の設定　
		GetShader().pEffect->SetFloat("fCubeRate", CUB_RATE_DIRTY);
		break;

	case TYPE_NORMAL:
		GetShader().pEffect->SetFloat("fCubeRate", CUB_RATE_NORMAL);
		break;

	case TYPE_EVENING:
		GetShader().pEffect->SetFloat("fCubeRate", CUB_RATE_EVENING);
		break;
	default:
		break;
	}


}
