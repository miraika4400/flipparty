////////////////////////////////////////////////////
//
//    Resource_Shaderクラスの処理[Resource_Shader.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "Resource_Shader.h"
#include "renderer.h"
#include "manager.h"

//******************************
// マクロ定義
//******************************

//******************************
// 静的メンバ変数宣言
//******************************
CResourceShader *CResourceShader::m_pSingleTex = NULL; // shaderポインタ*シングルトン用

//shaderのパス
const std::string CResourceShader::m_aEffectPath[CResourceShader::SHADER_MAX]
{
	"data/HLSL/PlayerShader.fx",       // プレイヤー
	"data/HLSL/CloudShader.fx",        // 雲
	"data/HLSL/IcebergShader.fx",        // 雲
	"data/HLSL/ZValuePlot.fx",         // Z値テクスチャ
	
};

// テクニック名
const std::string CResourceShader::m_aTechniqueName[CResourceShader::SHADER_MAX]
{
	"Shader",        // プレイヤー
	"Shader",        // 雲
	"Shader",
	"ZValuePlotTec", // Z値テクスチャ
};

//===================================
// コンストラクタ
//===================================
CResourceShader::CResourceShader()
{
	memset(&m_apShader, 0, sizeof(m_apShader));
}

//===================================
// デストラクタ
//===================================
CResourceShader::~CResourceShader()
{
}

//=============================================================================
//モデルクラスのクリエイト処理
//=============================================================================
CResourceShader * CResourceShader::Create(void)
{
	if (m_pSingleTex == NULL)
	{
		// メモリ確保
		m_pSingleTex = new CResourceShader;

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
void CResourceShader::Release(void)
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
CResourceShader::Shader CResourceShader::GetShader(SHADER_TYPE type)
{
	return m_pSingleTex->m_apShader[type];
}

//===================================
// テクスチャ読み込み
//===================================
void CResourceShader::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ数分ループ
	for (int nCnt = 0; nCnt < SHADER_MAX; nCnt++)
	{
		// HLSLファイルの読み込み
		D3DXCreateEffectFromFile(pDevice, m_aEffectPath[nCnt].c_str(), NULL, NULL, 0, NULL, &m_apShader[nCnt].pEffect, NULL);

		// テクニック名
		sprintf(&m_apShader[nCnt].achTechniqueName[0], "%s", m_aTechniqueName[nCnt].c_str());

		// テクニックのセット
		m_apShader[nCnt].pEffect->SetTechnique(m_apShader[nCnt].achTechniqueName);
	}
}

//===================================
// テクスチャ破棄
//===================================
void CResourceShader::Unload(void)
{
	// テクスチャ数分ループ
	for (int nCnt = 0; nCnt < SHADER_MAX; nCnt++)
	{
		if (m_apShader[nCnt].pEffect != NULL)
		{
			// テクスチャの破棄
			m_apShader[nCnt].pEffect->Release();
			m_apShader[nCnt].pEffect = NULL;
		}
	}
}
