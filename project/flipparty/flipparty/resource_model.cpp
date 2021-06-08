////////////////////////////////////////////////////
//
//    resource_modelクラスの処理[resource_model.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "resource_model.h"
#include "renderer.h"
#include "manager.h"

//******************************
// マクロ定義
//******************************
#define GENERAL_MODEL_COLOR D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)

//******************************
// 静的メンバ変数宣言
//******************************
CResourceModel *CResourceModel::m_pSingle = NULL; //モデルクラスのポインタ*シングルトン用
// モデルのパス
const std::string CResourceModel::m_aModelPath[CResourceModel::MODEL_MAX]
{
	"PATH_NONE_SPHERE",   // 汎用モデル(球)*xファイルじゃない
	"PATH_NONE_BOX",      // 汎用モデル(箱)*xファイルじゃない
	"data/Models/player.x",

};

//===================================
// コンストラクタ
//===================================
CResourceModel::CResourceModel()
{
	memset(&m_apModel, 0, sizeof(m_apModel));
}

//===================================
// デストラクタ
//===================================
CResourceModel::~CResourceModel()
{
}

//=============================================================================
//モデルクラスのクリエイト処理
//=============================================================================
CResourceModel * CResourceModel::Create(void)
{
	if (m_pSingle == NULL)
	{
		// メモリ確保
		m_pSingle = new CResourceModel;

		if (m_pSingle != NULL)
		{
			// メモリ確保に成功したとき
			m_pSingle->Load();
		}
		else
		{
			// メモリ確保に失敗したとき
			return NULL;
		}
	}

	return m_pSingle;
}

//===================================
// クラスの破棄
//===================================
void CResourceModel::Release(void)
{
	if (m_pSingle != NULL)
	{
		// テクスチャ破棄
		m_pSingle->Unload();
		// メモリの破棄
		delete m_pSingle;
		m_pSingle = NULL;
	}
}

//===================================
// モデル取得
//===================================
CResourceModel::Model* CResourceModel::GetModel(MODEL_TYPE type)
{
	if (m_pSingle != NULL)
	{
		return &m_pSingle->m_apModel[type];
	}
	else
	{
		return NULL;
	}
}

//===================================
// テクスチャ読み込み
//===================================
void CResourceModel::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// モデル数分ループ
	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
	{
		// モデルの読み込み
		if (strcmp(m_aModelPath[nCntModel].c_str(), "PATH_NONE_SPHERE") == 0 || strcmp(m_aModelPath[nCntModel].c_str(), "PATH_NONE_BOX") == 0)
		{// 汎用モデル
			
			// モデル生成
			// 球
			if(strcmp(m_aModelPath[nCntModel].c_str(), "PATH_NONE_SPHERE") == 0) D3DXCreateSphere(pDevice, 1, 10, 10, &m_apModel[nCntModel].pMesh, &m_apModel[nCntModel].pBuffMat);
			// 箱
			else D3DXCreateBox(pDevice, 1, 1, 1, &m_apModel[nCntModel].pMesh, &m_apModel[nCntModel].pBuffMat);
			
			m_apModel[nCntModel].nNumMat = 1;
			// 色の初期設定
			D3DXMATERIAL* mat = (D3DXMATERIAL*)m_apModel[nCntModel].pBuffMat->GetBufferPointer();
			mat->MatD3D.Ambient  = GENERAL_MODEL_COLOR;
			mat->MatD3D.Diffuse  = GENERAL_MODEL_COLOR;
			mat->MatD3D.Specular = GENERAL_MODEL_COLOR;
			mat->MatD3D.Emissive = GENERAL_MODEL_COLOR;
		}
		else
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX(m_aModelPath[nCntModel].c_str(), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_apModel[nCntModel].pBuffMat, NULL, &m_apModel[nCntModel].nNumMat, &m_apModel[nCntModel].pMesh);

			// テクスチャ読み込み
			if (m_apModel[nCntModel].nNumMat != 0)
			{
				D3DXMATERIAL*pMat = (D3DXMATERIAL*)m_apModel[nCntModel].pBuffMat->GetBufferPointer();
				for (int nCnt = 0; nCnt < (int)m_apModel[nCntModel].nNumMat; nCnt++)
				{
					if (pMat[nCnt].pTextureFilename != NULL)
					{
						char cPath[128] = {};
						sprintf(cPath, "./data/Textures/%s", pMat[nCnt].pTextureFilename);
						// テクスチャの生成
						D3DXCreateTextureFromFile(pDevice, cPath, &m_apModel[nCntModel].apTexture[nCnt]);
					}
				}
			}
		}
	}
}

//===================================
// 破棄
//===================================
void CResourceModel::Unload(void)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// メッシュの解放
		if (m_apModel[nCnt].pMesh != NULL)
		{
			m_apModel[nCnt].pMesh->Release();
			m_apModel[nCnt].pMesh = NULL;
		}
		// バッファの解放
		if (m_apModel[nCnt].pBuffMat != NULL)
		{
			m_apModel[nCnt].pBuffMat->Release();
			m_apModel[nCnt].pBuffMat = NULL;
		}

		// マテリアル数分ループ
		for (int nCntTex = 0; nCntTex < (int)m_apModel[nCnt].nNumMat; nCntTex++)
		{
			// テクスチャの解放
			if (m_apModel[nCnt].apTexture[nCntTex] != NULL)
			{
				m_apModel[nCnt].apTexture[nCntTex]->Release();
				m_apModel[nCnt].apTexture[nCntTex] = NULL;
			}
		}
	}
}
