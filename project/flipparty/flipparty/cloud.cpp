////////////////////////////////////////////////////
//
//    ミニゲームリザルトクラスの処理[mini_result.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "cloud.h"
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
#define MAX_SIZE  D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define SIZE_RATE 0.05f
#define CLOUD_COLOR D3DXCOLOR(0.95f, 0.95f, 1.0f, m_fAlpha)
#define LIFE 200

//=============================
// コンストラクタ
//=============================
CCloud::CCloud() :CModel(OBJTYPE_MAP)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAction = 0;
	m_fAlpha = 0.0f;
}

//=============================
// デストラクタ
//=============================
CCloud::~CCloud()
{
}

//=============================
// クリエイト
//=============================
CCloud * CCloud::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CCloud *pCloud = new CCloud;
	
	// 初期化
	pCloud->Init();

	// 座標の設定
	pCloud->SetPos(pos);

	return pCloud;
}

//=============================
// 初期化処理
//=============================
HRESULT CCloud::Init(void)
{
	// モデルクラスの初期化
	CModel::Init();

	// モデルの割り当て
	BindModel(CResourceModel::GetModel(CResourceModel::MODEL_CLOUD));

	// サイズの初期化
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetSize(m_size);

	// カウントの初期化
	m_nCntAction = 0;

	m_fAlpha = 0.0f;
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CCloud::Uninit(void)
{
	CModel::Uninit();
}


//=============================
// 更新処理
//=============================
void CCloud::Update(void)
{
	m_nCntAction++;
	if (m_nCntAction >= LIFE)
	{
		// サイズの変更
		m_size += (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_size)*SIZE_RATE;
		m_fAlpha += (-0.1f - m_fAlpha)*SIZE_RATE;
		
	}
	else
	{
		// サイズの変更
		m_size += (MAX_SIZE - m_size)*SIZE_RATE;
		m_fAlpha += (1.0f - m_fAlpha)*SIZE_RATE;
	}

	// サイズのセット
	SetSize(m_size);

	// 寿命処理
	if (m_fAlpha <= 0.0f)
	{
		Uninit();
	}
}

//=============================
// 描画処理
//=============================
void CCloud::Draw(void)
{
	CModel::Draw();
}

//=============================
// モデル描画
//=============================
void CCloud::DrawModel(void)
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
	CResourceShader::Shader shader = CResourceShader::GetShader(CResourceShader::SHADER_CLOUD);

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
					shader.pEffect->SetTexture("ToonTex", CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TOONSHADOW_CLOUD));
					// 色
					shader.pEffect->SetFloatArray("DiffuseColor", (float*)&CLOUD_COLOR, 4);
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
void CCloud::SetWorldmtx(void)
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
void CCloud::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
{
	if (pEffect != NULL)
	{
		// シェーダーに情報を渡す
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		mat = pModelData->mtxWorld * (*CGame::GetCamera()->GetViewMtx())* (*CGame::GetCamera()->GetProjectionMtx());
		// ワールドプロジェクション
		pEffect->SetMatrix("WorldViewProj", &mat);
		// ワールド座標
		pEffect->SetMatrix("World", &pModelData->mtxWorld);
		// ライトディレクション
		D3DXVECTOR3 lightDir = CGame::GetLight()->GetDir();
		pEffect->SetFloatArray("LightDirection", (float*)&D3DXVECTOR3(lightDir.x, -lightDir.y, -lightDir.z), 3);
		// 視点位置
		D3DXVECTOR3 eye = CGame::GetCamera()->GetPos();
		pEffect->SetFloatArray("Eye", (float*)&eye, 3);
	}
}
