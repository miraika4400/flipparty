////////////////////////////////////////////////////
//
//    captainクラスの処理[captain.cpp]
//    Author:増澤 未来(筒井俊稀)
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
#include "game.h"
#include "flipper.h"


//*****************************
// マクロ定義
//*****************************
#define HIERARCHY_TEXT_PATH "./data/Texts/hierarchy/pengin00.txt"    //階層構造テキストのパス
#define RIGHT_FLIPPER_PARTS_NUM 5                                    // 右羽のパーツ番号
#define LEFT_FLIPPER_PARTS_NUM  4                                    // 左羽のパーツ番号
#define RIGHT_FLIPPER_DIST_ANGLE_UP   D3DXToRadian(-60.0f)           // 右羽を上げたときの角度
#define RIGHT_FLIPPER_DIST_ANGLE_DOWN D3DXToRadian(30.0f)            // 右羽を下げたときの角度
#define LEFT_FLIPPER_DIST_ANGLE_UP    -RIGHT_FLIPPER_DIST_ANGLE_UP   // 左羽を上げたときの角度
#define LEFT_FLIPPER_DIST_ANGLE_DOWN  -RIGHT_FLIPPER_DIST_ANGLE_DOWN // 左羽を下げたときの角度
#define FLIPPER_RATE 0.07f                                           // 羽を動かすときの係数
#define FLIPPER_JUDGE D3DXToRadian(20.0f)                            // 上がっているか下がっているか判定の基準値

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
	m_pFlieer = NULL;
	ZeroMemory(&m_fFlipperDist, sizeof(m_fFlipperDist)); // 羽の角度 目標値
	m_nColor = 0;
	m_nCount = 0;
	m_nChoice = 0;

	m_bLoop = true;
	m_bJudgRed = false;
	m_bJudgWhite = false;

	m_eColorRed = RED_FLAG_DOWN;
	m_eColorWhite = WHITE_FLAG_DOWN;
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
	// フリッパークラスの生成
	m_pFlieer = CFlipper::Create();

	// 羽の目標角度の初期化
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = 0.0f;
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = 0.0f;

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
	while (m_bLoop)
	{
		// 全部下げている状態
		Judge(RED_FLAG_DOWN, WHITE_FLAG_DOWN, WHITE_DOWN, RED_DOWN);
		// 白だけ上げている状態
		Judge(RED_FLAG_DOWN, WHITE_FLAG_UP, WHITE_UP, RED_DOWN);
		// 赤だけ上げている状態
		Judge(RED_FLAG_UP, WHITE_FLAG_DOWN, WHITE_DOWN, RED_UP);
		// どちらも上がっている状態
		Judge(RED_FLAG_UP, WHITE_FLAG_UP, WHITE_UP, RED_UP);

		// 旗上げ判定処理
		FlagJudge();
	}
	// 羽の角度の管理
	ManageFlipperAngle();
}

//******************************
// 描画処理
//******************************
void CCaptain::Draw(void)
{
	CModelHierarchy::Draw();
}

//******************************
// 色判別処理
//******************************
void CCaptain::Judge(FLAG ColorFlagRed, FLAG ColorFlagWhite, COLOR ColorRed, COLOR ColorWhite)
{
	// 全部下げている状態
	if (m_eColorRed == ColorFlagRed && m_eColorWhite == ColorFlagWhite)
	{
		while (true)
		{
			// 色判定
			m_nColor = rand() % 4 + 1;
			if (m_nColor != ColorRed && m_nColor != ColorWhite)
			{
				break;
			}
		}
	}
}

//******************************
// 下げているか上げているかの確認
//******************************
void CCaptain::JudgeColor(FLAG ColorFlagRed, FLAG ColorFlagWhite, COLOR ColorRed, COLOR ColorWhite)
{

}

//******************************
// 旗上げ判定処理
//******************************
void CCaptain::FlagJudge()
{
	// 旗上げ判定処理
	switch (m_nColor)
	{
		// 青上げ
	case WHITE_UP:
		if (!m_bJudgWhite)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;

			if (m_nChoice != 1)
			{
				m_bLoop = false;
			}
			else
			{
				m_eColorWhite = WHITE_FLAG_UP;
				m_bJudgWhite = true;
				m_nCount++;
			}
		}
		break;
		// 青下げ
	case WHITE_DOWN:
		if (m_bJudgWhite)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;

			if (m_nChoice != 1)
			{
				m_bLoop = false;
			}
			else
			{
				m_eColorWhite = WHITE_FLAG_DOWN;
				m_bJudgWhite = false;
				m_nCount++;
			}
		}
		break;
		// 赤上げ
	case RED_UP:
		if (!m_bJudgRed)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;

			if (m_nChoice != 2)
			{
				m_bLoop = false;
			}
			else
			{
				m_eColorRed = RED_FLAG_UP;
				m_bJudgRed = true;
				m_nCount++;
			}
		}
		break;
		// 赤下げ
	case RED_DOWN:
		if (m_bJudgRed)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;

			if (m_nChoice != 2)
			{
				m_bLoop = false;
			}
			else
			{
				m_eColorRed = RED_FLAG_DOWN;
				m_bJudgRed = false;
				m_nCount++;
			}
		}
		break;
	}
}
//******************************
// 羽の角度の管理
//******************************
void CCaptain::ManageFlipperAngle(void)
{
	// モデルデータの取得
	CResourceModel::Model * pModelData = GetModelData();
	// 右羽を動かす
	pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z += (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] - pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z)*FLIPPER_RATE;
	// 左羽を動かす
	pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z += (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] - pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z)*FLIPPER_RATE;

	// 右羽の上がっているか下がっているかの判定
	if (pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z <= RIGHT_FLIPPER_DIST_ANGLE_UP + FLIPPER_JUDGE)
	{// 上がっているとき
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z >= RIGHT_FLIPPER_DIST_ANGLE_DOWN - FLIPPER_JUDGE)
	{// 下がっているとき
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
	}
	else
	{// 中間
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPER_STATE_NONE);
	}

	// 右羽の上がっているか下がっているかの判定
	if (pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z >= LEFT_FLIPPER_DIST_ANGLE_UP - FLIPPER_JUDGE)
	{// 上がっているとき
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z <= LEFT_FLIPPER_DIST_ANGLE_DOWN + FLIPPER_JUDGE)
	{// 下がっているとき
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
	}
	else
	{// 中間
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPER_STATE_NONE);
	}
}

