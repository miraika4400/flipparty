//=============================================================================
//
// model_shaderヘッダ [model_shader.cpp]
// Author : 増澤 未来
//
//=============================================================================


//******************************
// インクルード
//******************************
#include "model_shader.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "camera.h"
#include "light.h"
#include "resource_model.h"

//*****************************
// マクロ定義
//*****************************

//*****************************
// 静的メンバ変数宣言
//*****************************

//******************************
// コンストラクタ
//******************************
CModelShader::CModelShader(int nPliority) :CModel(nPliority)
{
	// 変数のクリア
	memset(&m_shader, 0, sizeof(m_shader)); // シェーダー
}

//******************************
// デストラクタ
//******************************
CModelShader::~CModelShader()
{
}

//******************************
// 初期化処理
//******************************
HRESULT CModelShader::Init(void)
{
	// モデルクラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CModelShader::Uninit(void)
{
	CModel::Uninit();
}

//******************************
// 更新処理
//******************************
void CModelShader::Update(void)
{
	// モデルクラスの更新処理
	CModel::Update();
}

//******************************
// 描画処理
//******************************
void CModelShader::Draw(void)
{

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// シェーダー光源計算をするためライトを消す
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIX mtxRot, mtxTrans, mtxScail;
	D3DMATERIAL9 matDef;	//現在のマテリアル保持用
	D3DXMATERIAL*pMat;	//マテリアルデータへのポインタ

	// モデルデータの取得
	CResourceModel::Model model = *GetModelData();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&model.mtxWorld);

	//サイズを反映
	D3DXMatrixScaling(&mtxScail, model.size.x, model.size.y, model.size.z);
	D3DXMatrixMultiply(&model.mtxWorld, &model.mtxWorld, &mtxScail);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, model.rot.y, model.rot.x, model.rot.z);
	D3DXMatrixMultiply(&model.mtxWorld, &model.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, model.pos.x, model.pos.y, model.pos.z);
	D3DXMatrixMultiply(&model.mtxWorld, &model.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &model.mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	if (m_shader.pEffect != NULL)
	{
		if (model.pBuffMat != NULL)
		{
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)model.pBuffMat->GetBufferPointer();

			// テクニック
			m_shader.pEffect->SetTechnique("TexShader");

			// パス数の取得
			UINT numPass = 0;
			m_shader.pEffect->Begin(&numPass, 0);

			for (int nCntMat = 0; nCntMat < (int)model.nNumMat; nCntMat++)
			{
				if (model.apTexture[nCntMat] != NULL)
				{
					// シェーダの終了
					m_shader.pEffect->End();
					// テクニック
					m_shader.pEffect->SetTechnique("TexShader");

					// パス数の取得
					numPass = 0;
					m_shader.pEffect->Begin(&numPass, 0);
				}
				else
				{
					// シェーダの終了
					m_shader.pEffect->End();
					// テクニック
					m_shader.pEffect->SetTechnique("NotTexShader");

					// パス数の取得
					numPass = 0;
					m_shader.pEffect->Begin(&numPass, 0);
				}

				// 視点位置
				m_shader.pEffect->SetFloatArray("Eye", (float*)&D3DXVECTOR3(-0.0f, 2000.0f, -3000.0f), 3);

				// シェーダに情報
				D3DXMATRIX mat;
				D3DXMatrixIdentity(&mat);

				int nDrawCnt = CManager::GetRenderer()->GetDrawCount();
				mat = model.mtxWorld * (*CGame::GetCamera()->GetViewMtx())* (*CGame::GetCamera()->GetProjectionMtx());
				m_shader.pEffect->SetMatrix("WorldViewProj", &mat);                                                // プロジェクション
				m_shader.pEffect->SetMatrix("World", &model.mtxWorld);                                                    // ワールド
				m_shader.pEffect->SetFloatArray("SpecularColor", (float*)&D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 4); // スペキュラカラー
				m_shader.pEffect->SetFloatArray("LightDirection", LIGHT_DIR, 3);                                   // ライトディレクション
				m_shader.pEffect->SetTexture("CubeTex", m_shader.pCubeTex);                                        // キューブテクスチャ

				// パス数分描画処理のループ
				for (int nCntEffect = 0; nCntEffect < (int)numPass; nCntEffect++)
				{
					//マテリアルのアンビエントにディフューズカラーを設定
					pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// テクスチャ
					pDevice->SetTexture(0, model.apTexture[nCntMat]);
					// テクスチャ
					m_shader.pEffect->SetTexture("Tex", model.apTexture[nCntMat]);

					// 色
					m_shader.pEffect->SetFloatArray("DiffuseColor", (float*)&pMat[nCntMat].MatD3D.Diffuse, 4);
					
					// シェーダパスの描画開始
					m_shader.pEffect->BeginPass(nCntEffect);

					// モデルパーツの描画
					model.pMesh->DrawSubset(nCntMat);
					
					// シェーダパスの終了
					m_shader.pEffect->EndPass();

					pMat[nCntMat] = model.defMat[nCntMat];
				}
			}
		}
		// シェーダの終了
		m_shader.pEffect->End();
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
	// ライトをつける
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}