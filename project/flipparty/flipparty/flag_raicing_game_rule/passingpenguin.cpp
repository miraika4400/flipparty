//=============================================================================
//
// passingpenguinクラスの処理 [passingpenguin.cpp]
// Author : 山田陵太
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "passingpenguin.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "resource_texture.h"
#include "resource_shader.h"
#include "game.h"
#include "camera_base.h"
#include "light.h"
#include "sound.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define HIERARCHY_TEXT_PATH_PASSING "./data/Texts/hierarchy/pengin00.txt"   // 階層構造テキストのパス
#define FACE_PARTS_NUMBER 3  // 表情パーツのパーツ番号
#define FACE_PATTERN 3       // 表情パターン数
#define FACE_TEX_V (1.0f/(float)FACE_PATTERN) * (float)m_facePattern
#define MOVE_SPEED 3.0f	//移動速度
#define LEFT_START_POS_X -330.0f
#define RIGHT_START_POS_X 330.0f
#define PASSING_SIZE D3DXVECTOR3(1.25f,1.25f,1.25f)

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CResourceModel::Model CPassingPenguin::m_model[MAX_PARTS_NUM] = {};    // モデル構造体
int CPassingPenguin::m_nPartsNum = 0;	//モデルパーツ数
char CPassingPenguin::m_achAnimPath[64] = { "./data/Texts/motion/run.txt" };  // モーションテキストのパス格納用

//=============================================================================
//passingpenguinクラスのコンストラクタ
//=============================================================================
CPassingPenguin::CPassingPenguin()
{
	m_pMotion = NULL;
	m_facePattern = 0;
	m_moveDirection = MOVE_DIRECTION_LEFT;
	m_state = STATE_WAIT;
	m_move = VEC3_ZERO;
	m_nSoudCounter = 0;
}

//=============================================================================
//passingpenguinクラスのデストラクタ
//=============================================================================
CPassingPenguin::~CPassingPenguin()
{
}

//=============================================================================
//passingpenguinクラスのクリエイト処理
//=============================================================================
CPassingPenguin * CPassingPenguin::Create(D3DXVECTOR3 pos)
{
	CPassingPenguin *pPassingPenguin = NULL;

	//インスタンス生成
	pPassingPenguin = new CPassingPenguin;

	if (pPassingPenguin)
	{
		pPassingPenguin->SetPos(pos);
		pPassingPenguin->Init();
		pPassingPenguin->SetPriority(OBJTYPE_CPU); // オブジェクトタイプ
	}

	return pPassingPenguin;
}

//=============================================================================
//passingpenguinクラスの
//=============================================================================
HRESULT CPassingPenguin::Load(void)
{
	//モデルの読み込み
	LoadModels(HIERARCHY_TEXT_PATH_PASSING, m_model, &m_nPartsNum);

	return S_OK;
}

//=============================================================================
//passingpenguinクラスの
//=============================================================================
void CPassingPenguin::Unload(void)
{
	for (int nCntParts = 0; nCntParts < m_nPartsNum; nCntParts++)
	{
		//メッシュの破棄
		if (m_model[nCntParts].pMesh)
		{
			m_model[nCntParts].pMesh->Release();
			m_model[nCntParts].pMesh = NULL;
		}

		//マテリアルの破棄
		if (m_model[nCntParts].pBuffMat)
		{
			m_model[nCntParts].pBuffMat->Release();
			m_model[nCntParts].pBuffMat = NULL;
		}
	}

}

//=============================================================================
//passingpenguinクラスの初期化処理
//=============================================================================
HRESULT CPassingPenguin::Init(void)
{
	//階層構造付きモデルクラスの初期化
	if (FAILED(CModelHierarchy::Init(m_nPartsNum, &m_model[0], HIERARCHY_TEXT_PATH_PASSING)))
	{
		return E_FAIL;
	}

	//モーションの生成
	m_pMotion = CMotion::Create(m_nPartsNum, m_achAnimPath, GetModelData());

	//モーションの再生
	m_pMotion->SetActiveMotion(true);

	//フェイスパターンの初期化
	m_facePattern = 0;

	// サイズ
	SetSize(PASSING_SIZE);

	return S_OK;
}

//=============================================================================
//passingpenguinクラスの終了処理
//=============================================================================
void CPassingPenguin::Uninit(void)
{
	//階層構造付きモデルクラスの終了
	CModelHierarchy::Uninit();
}


//=============================================================================
//passingpenguinクラスの更新処理
//=============================================================================
void CPassingPenguin::Update(void)
{
	if (m_state == STATE_MOVE)
	{
		//移動
		Move();
	}
}

//=============================================================================
//passingpenguinクラスの描画処理
//=============================================================================
void CPassingPenguin::Draw(void)
{
	if (m_state != STATE_WAIT)
	{
		//階層構造付きモデルクラスの描画
		CModelHierarchy::Draw();
	}
	
}

//=============================================================================
//passingpenguinクラスの移動方向の設定処理
//=============================================================================
void CPassingPenguin::SetMoveDirection(MOVE_DIRECTION moveDirection)
{
	m_nSoudCounter = 0;
	//移動方向を設定
	m_moveDirection = moveDirection;

	//現在位置を取得
	D3DXVECTOR3 pos = GetPos();

	//向きを取得
	D3DXVECTOR3 rot = GetRot();

	switch (m_moveDirection)
	{
	case MOVE_DIRECTION_LEFT:
		pos = D3DXVECTOR3(LEFT_START_POS_X, pos.y, pos.z);
		m_move = D3DXVECTOR3(MOVE_SPEED, 0.0f, 0.0f);
		rot = D3DXVECTOR3(rot.x, D3DXToRadian(-90.0f), rot.z);

		break;

	case MOVE_DIRECTION_RIGHT:
		pos = D3DXVECTOR3(RIGHT_START_POS_X, pos.y, pos.z);
		m_move = D3DXVECTOR3(-MOVE_SPEED, 0.0f, 0.0f);
		rot = D3DXVECTOR3(rot.x, D3DXToRadian(90.0f), rot.z);
	
		break;
	default:
		break;
	}
	
	//位置の設定
	SetPos(pos);

	//向きの設定
	SetRot(rot);

	//状態を移動へ設定
	m_state = STATE_MOVE;
}

//=============================================================================
//passingpenguinクラスの移動処理
//=============================================================================
void CPassingPenguin::Move(void)
{
	if (m_nSoudCounter % 20 == 0)
	{
		CManager::GetSound()->Play(CSound::LABEL_SE_PASSING_PENGUIN);
	}

	m_nSoudCounter++;

	//位置の取得
	D3DXVECTOR3 pos = GetPos();

	//移動量を与える
	pos += m_move;

	//位置の設定
	SetPos(pos);

	if (pos.x <= LEFT_START_POS_X || pos.x >= RIGHT_START_POS_X)
	{
		//状態を待機に設定
		m_state = STATE_WAIT;
	}
	
}

//=============================================================================
//passingpenguinクラスのモデルの描画処理
//=============================================================================
void CPassingPenguin::DrawModel(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;	//現在のマテリアル保持用
	D3DXMATERIAL*pMat;	//マテリアルデータへのポインタ

	CResourceModel::Model *pModelData = GetModelData();

	for (int nCntParts = 0; nCntParts < GetPartsNum(); nCntParts++)
	{
		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &pModelData[nCntParts].mtxWorld);

		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);

		// シェーダー情報の取得
		CResourceShader::Shader shader = CResourceShader::GetShader(CResourceShader::SHADER_PLAYER);

		if (shader.pEffect != NULL)
		{
			// シェーダープログラムに値を送る
			SetShaderVariable(shader.pEffect, &pModelData[nCntParts]);

			// フェイスパターン
			if (nCntParts != FACE_PARTS_NUMBER)
			{
				shader.pEffect->SetFloat("fTexV", 0.0f);
			}
			else
			{
				shader.pEffect->SetFloat("fTexV", FACE_TEX_V);
			}

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)pModelData[nCntParts].pBuffMat->GetBufferPointer();

			// パス数の取得
			UINT numPass = 0;
			shader.pEffect->Begin(&numPass, 0);

			// パス数分描画処理のループ
			for (int nCntEffect = 0; nCntEffect < (int)numPass; nCntEffect++)
			{
				for (int nCntMat = 0; nCntMat < (int)pModelData[nCntParts].nNumMat; nCntMat++)
				{
					//マテリアルのアンビエントにディフューズカラーを設定
					pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// テクスチャ
					pDevice->SetTexture(0, pModelData[nCntParts].apTexture[nCntMat]);

					// テクスチャをシェーダーに送る
					shader.pEffect->SetTexture("Tex", pModelData[nCntParts].apTexture[nCntMat]);
					// テクスチャをシェーダーに送る
					shader.pEffect->SetTexture("ToonTex", CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TOONSHADOW));
					// 色
					shader.pEffect->SetFloatArray("DiffuseColor", (float*)&pMat[nCntMat].MatD3D.Diffuse, 4);
					// シェーダパスの描画開始
					shader.pEffect->BeginPass(nCntEffect);
					//モデルパーツの描画
					pModelData[nCntParts].pMesh->DrawSubset(nCntMat);
					// シェーダパスの終了
					shader.pEffect->EndPass();


					pMat[nCntMat] = pModelData[nCntParts].defMat[nCntMat];
				}
			}
			// シェーダー終了
			shader.pEffect->End();
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
		// テクスチャの初期化
		pDevice->SetTexture(0, 0);
	}
}

//=============================================================================
//passingpenguinクラスのシェーダーの設定処理
//=============================================================================
void CPassingPenguin::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
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
		D3DXVECTOR3 lightDir = CGame::GetLight()->GetDir();
		pEffect->SetFloatArray("LightDirection", (float*)&D3DXVECTOR3(lightDir.x, -lightDir.y, -lightDir.z), 3);
		// 視点位置
		D3DXVECTOR3 eye = CManager::GetCamera()->GetPos();
		pEffect->SetFloatArray("Eye", (float*)&eye, 3);
	}
}
