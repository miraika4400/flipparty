////////////////////////////////////////////////////
//
//    particleクラスの処理[particle.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"


//*****************************
// マクロ定義
//*****************************
#define HIERARCHY_TEXT_PATH1 "./data/Texts/hierarchy/Player1.txt"    //階層構造テキストのパス

//*****************************
// 静的メンバ変数宣言
//*****************************
CResourceModel::Model CPlayer::m_model[MAX_PARTS_NUM] = {};
int CPlayer::m_nPartsNum = 0;

//******************************
// コンストラクタ
//******************************
CPlayer::CPlayer() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// 変数のクリア
	m_nPlayerNum = 0;                  // プレイヤー番号
}

//******************************
// デストラクタ
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// クリエイト
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
	// メモリの確保
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->m_nPlayerNum = nPlayerNum;
	
	// 初期化
	pPlayer->Init();

	// 各値の代入・セット
	pPlayer->SetPos(pos);
	pPlayer->SetPriority(OBJTYPE_PLAYER); // オブジェクトタイプ

	return pPlayer;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CPlayer::Load(void)
{

	// モデルの読み込み
	LoadModels(HIERARCHY_TEXT_PATH1, &m_model[0], &m_nPartsNum);

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CPlayer::Unload(void)
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
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nPartsNum, &m_model[0], HIERARCHY_TEXT_PATH1)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CPlayer::Uninit(void)
{
	CModelHierarchy::Uninit();
}

//******************************
// 更新処理
//******************************
void CPlayer::Update(void)
{
}

//******************************
// 描画処理
//******************************
void CPlayer::Draw(void)
{
	CModelHierarchy::Draw();
}
