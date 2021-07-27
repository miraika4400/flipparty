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

//=============================================================================
//マクロ定義
//=============================================================================
#define HIERARCHY_TEXT_PATH_PASSING "./data/Texts/hierarchy/pengin00.txt"   // 階層構造テキストのパス

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
	return S_OK;
}

//=============================================================================
//passingpenguinクラスの終了処理
//=============================================================================
void CPassingPenguin::Uninit(void)
{
	//階層モデルの終了
	CModelHierarchy::Uninit();
}


//=============================================================================
//passingpenguinクラスの更新処理
//=============================================================================
void CPassingPenguin::Update(void)
{
}

//=============================================================================
//passingpenguinクラスの描画処理
//=============================================================================
void CPassingPenguin::Draw(void)
{
	//描画
	CModelHierarchy::Draw();
}

//=============================================================================
//passingpenguinクラスのモデルの描画処理
//=============================================================================
void CPassingPenguin::DrawModel(void)
{
}

//=============================================================================
//passingpenguinクラスのシェーダーの設定処理
//=============================================================================
void CPassingPenguin::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
{
}
