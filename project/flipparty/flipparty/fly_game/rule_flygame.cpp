////////////////////////////////////////////////////
//
//    カメラクラスの処理[camera.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "rule_flygame.h"
#include "count_selection.h"
#include "player_flygame.h"
#include "game.h"
#include "camera_flygame.h"
#include "light.h"
#include "timelimit.h"
#include "camera_tps.h"
#include "mini_result.h"
#include "bg.h"
#include "cloud.h"
#include "thunder.h"
#include "iceberg.h"
#include "manager.h"
#include "result.h"
#include "rule_manager.h"
#include "sea.h"
#include "stage.h"
#include "warning.h"
#include "sound.h"

//******************************
// マクロ定義
//******************************
#define PLAYER_SPACE 150.0f //　プレイヤー位置の間隔
#define PLAY_TIME 30        // 制限時間

//******************************
// 静的メンバ変数宣言
//******************************
CFlyGamePlayer * CRuleFly::m_pPlayer[MAX_PLAYER_NUM] = {};
bool CRuleFly::m_bPlay = true;

//******************************
// コンストラクタ
//******************************
CRuleFly::CRuleFly()
{
	// 変数のクリア
	m_pTimeLimit = NULL;
}

//******************************
// デストラクタ
//******************************
CRuleFly::~CRuleFly()
{
}

//******************************
// クリエイト
//******************************
CRuleFly * CRuleFly::Create(void)
{
	CRuleFly * pRuleFly = new CRuleFly;
	pRuleFly->Init();

	return pRuleFly;
}

//******************************
// 初期化処理
//******************************
HRESULT CRuleFly::Init(void)
{
	// 氷山の生成
	CIceberg::Create(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), CIceberg::ICEBERG_TYPE(rand() % CIceberg::ICEBERG_MAX));

	// 海の生成
	CSea::Create(D3DXVECTOR3(0.0f, -14.0f, 0.0f), 0.001f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -12.0f, 0.0f), 0.0025f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -10.0f, 0.0f), 0.004f, CSea::TYPE_NORMAL);

	// 背景の生成
	CBg::Create();

	// カメラクラスの生成
	CManager::SetCamera(CFlyGameCamera::Create());

	// プレイヤー数の取得
	int nPlayNum = CCountSelect::GetPlayerNum();
	
	// プレイヤーの生成
	// 生成位置X軸の調整
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		m_pPlayer[nCntPlayer] = CFlyGamePlayer::Create(D3DXVECTOR3(posX, 0.0f, 0.0f), nCntPlayer);
		m_pPlayer[nCntPlayer]->SetRot(D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f));

		// ステージの生成
		CStage::Create(D3DXVECTOR3(posX, 0.0f, 0.0f), CStage::STAGE_TYPE_NORMAL);

		posX -= PLAYER_SPACE;
	}

	// 制限時間の生成
	m_pTimeLimit = CTimeLimit::Create(PLAY_TIME);

	// プレイ中フラグの初期化
	m_bPlay = false;

	return S_OK;
}

//******************************
// 初期化処理
//******************************
void CRuleFly::Uninit(void)
{
	// BGM停止
	CManager::GetSound() ->Stop(CSound::LABEL_BGM_FLY_GAME);
}

//******************************
// 更新処理
//******************************
void CRuleFly::Update(void)
{
	if (GetRuleState() == RULE_STATE_GAME)
	{
		////////////////////////////////////////
		// 仮置き

		// 雷雲の生成
		if (m_pTimeLimit->GetTimeLimit() == 20 && m_pTimeLimit->GetTimeCount() == 0 || m_pTimeLimit->GetTimeLimit() == 10 && m_pTimeLimit->GetTimeCount() == 0)
		{
			for (int nCntPlayer = 0; nCntPlayer < CCountSelect::GetPlayerNum(); nCntPlayer++)
			{
				//CCloud::Create(nCntPlayer);

				CWarningUI::Create(nCntPlayer);
			}
		}

		/////////////////////////////////////////

		if (m_pTimeLimit->GetTimeLimit() <= 0)
		{
			//ゲーム終了状態へ移行
			SetRuleState(CRuleBase::RULE_STATE_END);


			if (m_bPlay)
			{
				// ゲーム中フラグをfalse
				m_bPlay = false;

				
			}
			else
			{
				// カメラクラス
				//CManager::SetCamera(CFlyGameCamera::Create());
			}
		}
	}
}

//******************************
// 描画処理
//******************************
void CRuleFly::Draw(void)
{
}

//======================================================
//	ゲーム用の処理
//======================================================
void CRuleFly::GameProcess(void)
{
	// プレイ中フラグを有効化
	m_bPlay = true;

	// プレイヤーオブジェクトの取得
	CPlayer *pPlayer = (CPlayer *)CScene::GetTop(CScene::OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		// 操作を可能にする
		pPlayer->SetMoveFlag(true);

		// 次のプレイヤー情報に更新
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}

	// BGM再生
	CManager::GetSound()->Play(CSound::LABEL_BGM_FLY_GAME);
}

//======================================================
//	ミニリザルト用の処理
//======================================================
void CRuleFly::MiniResultProcess(void)
{
	// 順位判定
	JudgeRank();
}

//******************************
// 順位判定処理
//******************************
void CRuleFly::JudgeRank(void)
{
	std::vector<CPlayer*> vectorPlayer; // 順位付け用にプレイヤー情報を格納する変数 
	int nPlayerIndex = 0;  // ↑の変数のポインタをずらす用変数

	// プレイヤーオブジェクトの取得
	CPlayer *pPlayer = (CPlayer *)CScene::GetTop(CScene::OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		// 順位判定用変数に情報を保存
		vectorPlayer.push_back(pPlayer);
		nPlayerIndex++;

		if (pPlayer->GetMoveFlag())
		{
			// 操作を不可にする
			pPlayer->SetMoveFlag(false);
		}

		// 次のプレイヤー情報に更新
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}

	// Y座標の高い順にソート
	for (int nCntPlayer = 0; nCntPlayer < nPlayerIndex; nCntPlayer++)
	{
		for (int nCntSort = nCntPlayer + 1; nCntSort < nPlayerIndex; nCntSort++)
		{
			if (vectorPlayer[nCntPlayer]->GetPos().y < vectorPlayer[nCntSort]->GetPos().y)
			{
				CPlayer * pSave = vectorPlayer[nCntPlayer];
				vectorPlayer[nCntPlayer] = vectorPlayer[nCntSort];
				vectorPlayer[nCntSort] = pSave;
			}
		}
	}

	// 順位付け
	for (int nCntPlayer = 0; nCntPlayer < nPlayerIndex; nCntPlayer++)
	{
		// 配列の順番がそのまま順位に
		vectorPlayer[nCntPlayer]->SetRank(nCntPlayer);

		// Y軸の座標が同じなら同じ順位にする
		if (nCntPlayer != 0)
		{
			if (vectorPlayer[nCntPlayer]->GetPos().y == vectorPlayer[nCntPlayer - 1]->GetPos().y)
			{
				vectorPlayer[nCntPlayer]->SetRank(vectorPlayer[nCntPlayer - 1]->GetRank());
			}
		}

		// ミニゲームに順位を送る
		CResult::SetMiniGameRank(CRuleManager::RULE_FLY, vectorPlayer[nCntPlayer]->GetPlayerNumber(), vectorPlayer[nCntPlayer]->GetRank());
	}

	// リザルト生成
	CMiniResult::Create();
}
