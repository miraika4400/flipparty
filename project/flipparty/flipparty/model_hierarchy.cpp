//=============================================================================
//
// モデル処理 [ModelHirarchy.cpp]
// Author : 増澤未来
//
//=============================================================================
#include "model_hierarchy.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CModelHierarchy::CModelHierarchy(int nPriority) :CScene(nPriority)
{
	// 変数のクリア
	memset(&m_model, 0, sizeof(m_model));
	m_nNumParts = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	for (int nCnt = 0; nCnt < MAX_PARTS_NUM; nCnt++)
	{
		m_model[nCnt].size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}
}

//=============================================================================
//デストラクタ
//=============================================================================
CModelHierarchy::~CModelHierarchy()
{
}

//=============================================================================
// 階層構造の読み込みクラス
//=============================================================================
void CModelHierarchy::LoadModels(char * pPath, CResourceModel::Model *model,int * pNumModel)
{
	// ファイルオープン
	FILE*pFile = NULL;
	pFile = fopen(pPath, "r");

	if (pFile != NULL)
	{
		// テキストファイルの解析

		char chChar[256] = {};
		fscanf(pFile, "%s", chChar);

		// "NUM_MODEL"読み込むまでループ
		while (strcmp(chChar, "NUM_MODEL") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}

		// 読み込むモデルの数
		fscanf(pFile, "%*s %d # %*s", pNumModel);

		// デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		for (int nCnt = 0; nCnt < *pNumModel; nCnt++)
		{
			// 読み込んだ文字格納用
			char chPath[64] = {};
			// "MODEL_FILENAME"を読み込むまでループ
			while (strcmp(chChar, "MODEL_FILENAME") != 0)
			{
				fscanf(pFile, "%s", chChar);
			}
			// ファイルパスの読み込み
			fscanf(pFile, "%*s %s", chPath);

			// Xファイルの読み込み
			D3DXLoadMeshFromX(chPath,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&model[nCnt].pBuffMat,
				NULL,
				&model[nCnt].nNumMat,
				&model[nCnt].pMesh);

			// テクスチャ読み込み
			if (model[nCnt].nNumMat != 0)
			{
				D3DXMATERIAL*pMat = (D3DXMATERIAL*)model[nCnt].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)model[nCnt].nNumMat; nCntMat++)
				{
					model[nCnt].defMat[nCntMat] = pMat[nCntMat];
					if (pMat[nCntMat].pTextureFilename != NULL)
					{
						char cPath[128] = {};
						sprintf(cPath, "./data/Textures/%s", pMat[nCntMat].pTextureFilename);
						// テクスチャの生成
						D3DXCreateTextureFromFile(pDevice, cPath, &model[nCnt].apTexture[nCntMat]);
					}
				}
			}

			// 次の文字を読み込む
			fscanf(pFile, "%s", chChar);
		}
	}
}

//=============================================================================
//テキストファイルの読み込み
//=============================================================================
void CModelHierarchy::LoadHierarchy(CResourceModel::Model * model, char * pPath)
{
	// ファイルオープン
	FILE*pFile = NULL;
	pFile = fopen(pPath, "r");

	// パーツ数
	int nPartsNum = 0;

	if (pFile != NULL)
	{
		// テキストファイルの解析

		char chChar[256] = {};
		fscanf(pFile, "%s", chChar);

		// "SCRIPT"読み込むまでループ
		while (strcmp(chChar, "CHARACTERSET") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}

		// 文字排除用
		char cString[32] = {};

		fscanf(pFile, "%s %s %d", &cString, &cString, &nPartsNum);

		// "END_PARTSSET"読み込むまでループ
		while (strcmp(chChar, "END_CHARACTERSET") != 0)
		{
			fscanf(pFile, "%s", chChar);
			if (strcmp(chChar, "PARTSSET") == 0)
			{
				// インデックス一時保管用
				int nIndex = 0;
				// インデックスの読み込み
				fscanf(pFile, "%*s %*s %d # %*s", &nIndex);
				// 親番号の読み込み
				fscanf(pFile, "%*s %*s %d # %*s", &model[nIndex].nParent);
				// 座標の読み込み
				fscanf(pFile, "%*s %*s %f %f %f", &model[nIndex].pos.x, &model[nIndex].pos.y, &model[nIndex].pos.z);
				// 回転の読み込み
				fscanf(pFile, "%*s %*s %f %f %f", &model[nIndex].rot.x, &model[nIndex].rot.y, &model[nIndex].rot.z);

				fscanf(pFile, "%*s");
			}

		}
		fclose(pFile);
	}
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CModelHierarchy::Init(void)
{

	return S_OK;
}

HRESULT CModelHierarchy::Init(int nNumParts, CResourceModel::Model * model, char*pPath)
{
	LoadHierarchy(model, pPath);
	// 引数の代入
	m_nNumParts = nNumParts;
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_model[nCnt] = model[nCnt];

		for (int nCntMat = 0; nCntMat < (int)m_model[nCnt].nNumMat; nCntMat++)
		{
			m_model[nCnt].defMat[nCntMat] = ((D3DXMATERIAL*)m_model[nCnt].pBuffMat->GetBufferPointer())[nCntMat];

		}
	}

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CModelHierarchy::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CModelHierarchy::Update(void)
{
}

//=============================================================================
//描画処理
//=============================================================================
void CModelHierarchy::Draw(void)
{
	// 座標、サイズ、回転の設定
	SetWorldmtx();
	// モデルの描画処理
	DrawModel();
}

//=============================================================================
//モデルデータのセット
//=============================================================================
void CModelHierarchy::SetModelData(CResourceModel::Model *pModel)
{
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		m_model[nCnt].pos = pModel[nCnt].pos;
		m_model[nCnt].rot = pModel[nCnt].rot;
	}
}

//=============================================================================
//ワールドマトリックスの設定
//=============================================================================
void CModelHierarchy::SetWorldmtx(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// 回転、位置、サイズ行列
	D3DXMATRIX mtxRot, mtxTrans, mtxScail;

	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_model[nCntParts].mtxWorld);

		if (m_model[nCntParts].nParent == -1)
		{// 自分が一番の親のとき
		
			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_model[nCntParts].rot.y, m_model[nCntParts].rot.x, m_model[nCntParts].rot.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxRot, m_model[nCntParts].pos.x, m_model[nCntParts].pos.y, m_model[nCntParts].pos.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//スケールの反映（スケール座標の変換行列）
			D3DXMatrixScaling(&mtxScail, m_size.x, m_size.y, m_size.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxScail);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxTrans);

		}
		else
		{// 自分が一番の親じゃないとき

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_model[nCntParts].rot.y, m_model[nCntParts].rot.x, m_model[nCntParts].rot.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, m_model[nCntParts].pos.x, m_model[nCntParts].pos.y, m_model[nCntParts].pos.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxTrans);

			// 親のワールドマトリックスを掛け合わせる
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &m_model[m_model[nCntParts].nParent].mtxWorld);
		}
	}
}

//=============================================================================
//モデルの描画処理
//=============================================================================
void CModelHierarchy::DrawModel(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;	//現在のマテリアル保持用
	D3DXMATERIAL*pMat;	//マテリアルデータへのポインタ

	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_model[nCntParts].mtxWorld);

		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得

		pMat = (D3DXMATERIAL*)m_model[nCntParts].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_model[nCntParts].nNumMat; nCntMat++)
		{
			//マテリアルのアンビエントにディフューズカラーを設定
			pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// テクスチャ
			pDevice->SetTexture(0, m_model[nCntParts].apTexture[nCntMat]);
			//モデルパーツの描画
			m_model[nCntParts].pMesh->DrawSubset(nCntMat);

			pMat[nCntMat] = m_model[nCntParts].defMat[nCntMat];
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
		// テクスチャの初期化
		pDevice->SetTexture(0, 0);
	}
}
