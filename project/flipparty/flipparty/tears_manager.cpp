////////////////////////////////////////////////////
//
//    タイトルクラスの処理[title.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "tears_manager.h"
#include "tears_particle.h"

//**********************************
// 静的メンバ変数宣言
//**********************************

//**********************************
// マクロ定義
//**********************************
#define TEARS_INTERVAL 10 // 涙を生成するインターバル

//=============================
// コンストラクタ
//=============================
CTearsManager::CTearsManager(): CScene(OBJTYPE_SYSTEM)
{
	m_nCntTesrsInterval = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================
// デストラクタ
//=============================
CTearsManager::~CTearsManager()
{
}

//=============================
// クリエイト
//=============================
CTearsManager * CTearsManager::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CTearsManager *pTearsManager = new CTearsManager;
	// 初期化
	pTearsManager->Init();
	// 座標
	pTearsManager->m_pos = pos;

	return pTearsManager;
}

//=============================
// 初期化処理
//=============================
HRESULT CTearsManager::Init(void)
{
	// カウント初期化
	m_nCntTesrsInterval = 0;

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CTearsManager::Uninit(void)
{
	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CTearsManager::Update(void)
{
	// 涙の生成
	m_nCntTesrsInterval++;
	if ((m_nCntTesrsInterval%TEARS_INTERVAL) == 0)
	{
		CTearsParticle::Create(m_pos);
	}
}


//=============================
// 描画処理
//=============================
void CTearsManager::Draw(void)
{
}
