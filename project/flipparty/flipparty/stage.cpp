////////////////////////////////////////////////////
//
//    stageの処理[stage.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "stage.h"
#include "manager.h"
#include "renderer.h"
#include "resource_model.h"
#include "game.h"
#include "camera_base.h"
#include "light.h"
#include "resource_shader.h"
#include "resource_texture.h"

//**********************************
// 静的メンバ変数宣言
//**********************************

//**********************************
// マクロ定義
//**********************************

//=============================
// コンストラクタ
//=============================
CStage::CStage() :CModel(OBJTYPE_MAP)
{
	m_type = STAGE_TYPE_NORMAL;
}

//=============================
// デストラクタ
//=============================
CStage::~CStage()
{
}

//=============================
// クリエイト
//=============================
CStage * CStage::Create(D3DXVECTOR3 pos , STAGE_TYPE type)
{
	// メモリの確保
	CStage *pStage = new CStage;

	// タイプ
	pStage->m_type = type;

	// 初期化
	pStage->Init();

	// 座標の設定
	pStage->SetPos(pos);

 	return pStage;
}

//=============================
// 初期化処理
//=============================
HRESULT CStage::Init(void)
{
	// モデルクラスの初期化
	CModel::Init();

	if (m_type == STAGE_TYPE_NORMAL)
	{
		// モデルの割り当て
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_STAGE));
	}
	else
	{
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_STAGE_LARGE));
	}

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CStage::Uninit(void)
{
	CModel::Uninit();
}


//=============================
// 更新処理
//=============================
void CStage::Update(void)
{
}

//=============================
// 描画処理
//=============================
void CStage::Draw(void)
{
	CModel::Draw();
}

//=============================
// モデル描画
//=============================
void CStage::DrawModel(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef; //現在のマテリアル保持用
	D3DXMATERIAL*pMat;   //マテリアルデータへのポインタ

						 // モデルデータの取得
	CResourceModel::Model * pModelData = GetModelData();

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &pModelData->mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	// シェーダー情報の取得
	CResourceShader::Shader shader = CResourceShader::GetShader(CResourceShader::SHADER_ICEBERG);

	if (shader.pEffect != NULL)
	{
		// シェーダープログラムに値を送る
		SetShaderVariable(shader.pEffect, pModelData);
		if (pModelData->pBuffMat != NULL)
		{
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)pModelData->pBuffMat->GetBufferPointer();

			// パス数の取得
			UINT numPass = 0;
			shader.pEffect->Begin(&numPass, 0);

			// パス数分描画処理のループ
			for (int nCntEffect = 0; nCntEffect < (int)numPass; nCntEffect++)
			{
				for (int nCntMat = 0; nCntMat < (int)pModelData->nNumMat; nCntMat++)
				{
					//マテリアルのアンビエントにディフューズカラーを設定
					pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// テクスチャ
					pDevice->SetTexture(0, pModelData->apTexture[nCntMat]);

					// テクスチャをシェーダーに送る
					shader.pEffect->SetTexture("Tex", pModelData->apTexture[nCntMat]);
					shader.pEffect->SetTexture("ToonTex", CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TOONSHADOW));
					// 色
					shader.pEffect->SetFloatArray("DiffuseColor", (float*)&pMat[nCntMat].MatD3D.Diffuse, 4);
					// シェーダパスの描画開始
					shader.pEffect->BeginPass(nCntEffect);
					//モデルパーツの描画
					pModelData->pMesh->DrawSubset(nCntMat);
					// シェーダパスの終了
					shader.pEffect->EndPass();

					pMat[nCntMat] = pModelData->defMat[nCntMat];
				}
			}
			// シェーダー終了
			shader.pEffect->End();
		}
	}
	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
	// テクスチャ情報の初期化
	pDevice->SetTexture(0, 0);
}

//=============================
// ワールドマトリックスの設定
//=============================
void CStage::SetWorldmtx(void)
{

	D3DXMATRIX  mtxRot;   // 回転行列
	D3DXMATRIX	mtxTrans; // 位置行列
	D3DXMATRIX	mtxScail; // サイズ行列

						  // モデルデータの取得
	CResourceModel::Model * pModelData = GetModelData();
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&pModelData->mtxWorld);

	// サイズを反映
	D3DXMatrixScaling(&mtxScail, pModelData->size.x, pModelData->size.y, pModelData->size.z);
	D3DXMatrixMultiply(&pModelData->mtxWorld, &pModelData->mtxWorld, &mtxScail);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pModelData->rot.y, pModelData->rot.x, pModelData->rot.z);
	D3DXMatrixMultiply(&pModelData->mtxWorld, &pModelData->mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, pModelData->pos.x, pModelData->pos.y, pModelData->pos.z);
	D3DXMatrixMultiply(&pModelData->mtxWorld, &pModelData->mtxWorld, &mtxTrans);
}

//=============================
// シェーダーに値を送る
//=============================
void CStage::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
{
	if (pEffect != NULL)
	{
		// シェーダーに情報を渡す
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		mat = pModelData->mtxWorld * (*CManager::GetCamera()->GetViewMtx())* (*CManager::GetCamera()->GetProjectionMtx());
		// ワールドプロジェクション
		pEffect->SetMatrix("WorldViewProj", &mat);
		// ワールド座標
		pEffect->SetMatrix("World", &pModelData->mtxWorld);
		// ライトディレクション
		pEffect->SetFloatArray("LightDirection", (float*)&D3DXVECTOR3(LIGHT_DIR_BASE.x, -LIGHT_DIR_BASE.y, -LIGHT_DIR_BASE.z), 3);
		// 視点位置
		D3DXVECTOR3 eye = CManager::GetCamera()->GetPos();
		pEffect->SetFloatArray("Eye", (float*)&eye, 3);

	}
}
