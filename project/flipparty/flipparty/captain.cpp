////////////////////////////////////////////////////
//
//    captainクラスの処理[captain.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "captain.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"


//*****************************
// マクロ定義
//*****************************
#define HIERARCHY_TEXT_PATH "./data/Texts/hierarchy/Player1.txt"    //階層構造テキストのパス

//*****************************
// 静的メンバ変数宣言
//*****************************
CResourceModel::Model CCaptain::m_model[MAX_PARTS_NUM] = {};
int CCaptain::m_nPartsNum = 0;

//******************************
// コンストラクタ
//******************************
CCaptain::CCaptain() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// 変数のクリア
}

//******************************
// デストラクタ
//******************************
CCaptain::~CCaptain()
{
}

//******************************
// クリエイト
//******************************
CCaptain * CCaptain::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CCaptain *pCaptain;
	pCaptain = new CCaptain;

	// 初期化
	pCaptain->Init();

	// 各値の代入・セット
	pCaptain->SetPos(pos);
	pCaptain->SetPriority(OBJTYPE_PLAYER); // オブジェクトタイプ

	return pCaptain;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CCaptain::Load(void)
{

	// モデルの読み込み
	LoadModels(HIERARCHY_TEXT_PATH, &m_model[0], &m_nPartsNum);

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CCaptain::Unload(void)
{

	for (int nCnt = 0; nCnt < m_nPartsNum; nCnt++)
	{
		//メッシュの破棄
		if (m_model[nCnt].pMesh != NULL)
		{
			m_model[nCnt].pMesh->Release();
			m_model[nCnt].pMesh = NULL;
		}
		//マテリアルの破棄
		if (m_model[nCnt].pBuffMat != NULL)
		{
			m_model[nCnt].pBuffMat->Release();
			m_model[nCnt].pBuffMat = NULL;
		}
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CCaptain::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nPartsNum, &m_model[0], HIERARCHY_TEXT_PATH)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CCaptain::Uninit(void)
{
	CModelHierarchy::Uninit();
}

//******************************
// 更新処理
//******************************
void CCaptain::Update(void)
{
}

//******************************
// 描画処理
//******************************
void CCaptain::Draw(void)
{
	CModelHierarchy::Draw();
}
