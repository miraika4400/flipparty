//======================================================
//
//	旗上げゲームの処理[flag_raicing_game_rule.cpp]
//	Author : 筒井 俊稀
//
//======================================================
//======================================================
//	インクルードファイル
//======================================================
#include <time.h>
#include "flag_raicing_game_rule.h"
#include "flag_raicing_game_camera.h"
#include "manager.h"
#include "count_selection.h"
#include "player.h"
#include "captain.h"
#include "flipper.h"
#include "camera_tps.h"
#include "mini_result.h"
#include "timelimit.h"
#include "blind.h"
#include "bg.h"
#include "billboard.h"
#include "iceberg.h"
#include "passingpenguin.h"
#include "stage.h"
#include "sea.h"
#include "result.h"
#include "polygon.h"
#include "sound.h"
#include "flag_raicing_game_polygon.h"

//======================================================
//	静的メンバ変数宣言初期化
//======================================================
CFlagRaicingGame_rule::TRUN CFlagRaicingGame_rule::m_eLoop
	= CFlagRaicingGame_rule::CAPTAIN_TRUN;	// キャプテンのターンかプレイヤーのターンかを判別する変数
CBlind *CFlagRaicingGame_rule::m_pBlind = NULL;	//ブラインドクラスのポインタ変数
CPlayer *CFlagRaicingGame_rule::m_pPlayer[MAX_PLAYER_NUM] = {};

//======================================================
//	マクロ定義
//======================================================
#define PLAYER_SPACE 110.0f				// プレイヤー位置の間隔
#define POINT_UI_SPACE 310.0f			// 点数の位置間隔
#define TIME_SET 180					// 制限時間の設定
#define TRUN_SET 40						// ターンの制限時間の設定
#define ADD_POINT_NUM 1					// ポイント合計値の設定

#define FLAG_PLAYER_POS_Y_NUM -100.0f	// プレイヤーのY座標
#define FLAG_PLAYER_POS_Z_NUM -50.0f	// プレイヤーのZ座標

#define POINT_UI_POS_Y_NUM 630.0f		// 点数のY座標
#define POINT_UI_POS_Z_NUM 5.0f			// 点数のZ座標
#define POINT_UI_SIZE_X_NUM 60.0f		// 点数UI横幅の大きさ
#define POINT_UI_SIZE_Y_NUM 30.0f		// 点数UI縦幅の大きさ

#define FLAG_CAPTAIN_POS_X_NUM 0.0f		// キャプテンのX座標
#define FLAG_CAPTAIN_POS_Y_NUM -98.0f	// キャプテンのY座標
#define FLAG_CAPTAIN_POS_Z_NUM -220.0f	// キャプテンのZ座標
#define PASSING_PENGUIN_POS D3DXVECTOR3(400.0f, -90.0f, -100.0f)
#define RAND_FLAG rand() % 180 + 50		// フラッグの上げる間隔の設定

//======================================================
//	コンストラクタ
//======================================================
CFlagRaicingGame_rule::CFlagRaicingGame_rule()
{
	// 変数の初期化
	ZeroMemory(&m_PlayerPoint, sizeof(m_PlayerPoint));
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_pCaptain = NULL;
	m_nCntInputPlayer = 0;
	m_nCntTime = 0;
	m_nTarn = 0;
	m_nRandTime = 0;
	m_pTimeLimit = NULL;
	m_bPlay = true;
	m_pBlind = NULL;
	m_pPassingPenguin = NULL;
}

//======================================================
//	デストラクタ
//======================================================
CFlagRaicingGame_rule::~CFlagRaicingGame_rule()
{

}

//======================================================
//	生成処理
//======================================================
CFlagRaicingGame_rule * CFlagRaicingGame_rule::Create(void)
{
	CFlagRaicingGame_rule *pFlagRaicingGameRule
		= new CFlagRaicingGame_rule;

	if (pFlagRaicingGameRule)
	{
		pFlagRaicingGameRule->Init();
	}

	return pFlagRaicingGameRule;
}

//======================================================
//	初期化処理
//======================================================
HRESULT CFlagRaicingGame_rule::Init(void)
{
	CIceberg::Create(D3DXVECTOR3(0.0f, -100.0f, -1200.0f), CIceberg::ICEBERG_TYPE(rand() % CIceberg::ICEBERG_MAX));
	// 背景の生成
	CBg::Create();

	m_bPlay = true;
	m_nRandTime = TIME_SET;
	//カメラの生成
	CManager::SetCamera(CFlagRaicingGameCamera::Create());

	// プレイヤーの人数取得
	int nPlayerNum = CCountSelect::GetPlayerNum();
	float posX = 0 + ((float)(nPlayerNum - 1) * PLAYER_SPACE) / 2;// プレイヤー位置の調整
	float posXUI = SCREEN_WIDTH / 2 + ((float)(nPlayerNum - 1) * POINT_UI_SPACE) / 2;// 点数の位置調整

	// プレイヤーの人数分プレイヤー生成
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		// プレイヤーの生成
		m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(posX, FLAG_PLAYER_POS_Y_NUM, FLAG_PLAYER_POS_Z_NUM), nCntPlayer);
		// ポイントUIの生成
		m_PlayerPoint.bPoint[nCntPlayer] = CFlagRaicingGamePolygon::Create(
			nCntPlayer,D3DXVECTOR3(posXUI, POINT_UI_POS_Y_NUM, 0.0f));

		posX -= PLAYER_SPACE;
		posXUI -= POINT_UI_SPACE;
	}
	// キャプテンの生成
	m_pCaptain = CCaptain::Create(D3DXVECTOR3(FLAG_CAPTAIN_POS_X_NUM, FLAG_CAPTAIN_POS_Y_NUM, FLAG_CAPTAIN_POS_Z_NUM));
	
	// 制限時間の生成
	m_pTimeLimit = CTimeLimit::Create(TRUN_SET);
	
	//ブラインドの生成
	m_pBlind = CBlind::Create(m_pTimeLimit->GetTimeLimit(), (TRUN_SET / 2));

	//通過ペンギンの生成
	m_pPassingPenguin = CPassingPenguin::Create(PASSING_PENGUIN_POS);

	// ステージの生成
	CStage::Create(D3DXVECTOR3(FLAG_CAPTAIN_POS_X_NUM, FLAG_PLAYER_POS_Y_NUM, FLAG_CAPTAIN_POS_Z_NUM), CStage::STAGE_TYPE_LARGE);

	// 海の生成
	CSea::Create(D3DXVECTOR3(0.0f, FLAG_PLAYER_POS_Y_NUM -14.0f, 0.0f), 0.001f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, FLAG_PLAYER_POS_Y_NUM -12.0f, 0.0f), 0.0025f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, FLAG_PLAYER_POS_Y_NUM -10.0f, 0.0f), 0.004f, CSea::TYPE_NORMAL);

	// BGM再生
	CManager::GetSound()->Play(CSound::LABEL_BGM_FLAG_GAME);

	return S_OK;
}

//======================================================
//	終了処理
//======================================================
void CFlagRaicingGame_rule::Uninit(void)
{
	// BGM停止
	CManager::GetSound()->Stop(CSound::LABEL_BGM_FLAG_GAME);
	
	// 人数の取得
	int nPlayerNum = CCountSelect::GetPlayerNum();
	for (int nCnt = 0; nCnt < nPlayerNum; nCnt++)
	{
		// テクスチャクラスの終了処理
		if (m_PlayerPoint.bPoint[nCnt] != NULL)
		{
			//ビルボードの終了
			m_PlayerPoint.bPoint[nCnt]->Uninit();

			//メモリの削除
			delete m_PlayerPoint.bPoint[nCnt];

			//メモリのクリア
			m_PlayerPoint.bPoint[nCnt] = NULL;
		}
	}
}

//======================================================
//	更新処理
//======================================================
void CFlagRaicingGame_rule::Update(void)
{
	// プレイヤーの人数取得
	int nPlayerNum = CCountSelect::GetPlayerNum();
	bool btest = true;
	if (btest == true)
	{
		// プレイヤーを必要時以外動けなくするようにする処理
		if (m_bPlay)
		{
			// 乱数の初期化
			srand((unsigned int)time(NULL));
			for (int nCnt = 0; nCnt < nPlayerNum; nCnt++)
			{
				// ポイント追加処理
				m_PlayerPoint.bPoint[nCnt]->Update();
			}
			// 時間計算処理
			++m_nCntTime;
			// 判別処理
			FlagJudge();

			// 時間経過で次の動作に入る
			if (m_nCntTime == m_nRandTime)
			{
				m_nRandTime = RAND_FLAG;	// ランダムで旗の上げるタイミングを設定
				m_nTarn++;					// ターンを進める
				SetGameLoop(CAPTAIN_TRUN);	// キャプテンのターンに変更
				m_nCntTime = 0;				// タイムの初期化
				FlagPoint();				// ポイント追加
			}

			//制限時間を取得
			int nTimeLimit = m_pTimeLimit->GetTimeLimit();

			// 上限のターン数を上回ったらゲームを終了させる
			// 制限時間が0以下の時
			if (nTimeLimit <= 0)
			{
				JudgeRank();
			}

			//ブラインドに現在タイムを与える
			if (m_pBlind)
			{
				m_pBlind->SetTime(nTimeLimit);
			}

			if (nTimeLimit > (TRUN_SET / 2))
			{
				if (nTimeLimit == 35)
				{
					//左へ通過するよう設定
					m_pPassingPenguin->SetMoveDirection(CPassingPenguin::MOVE_DIRECTION_LEFT);
				}
				else if (nTimeLimit == 25)
				{
					//右へ通過するように設定
					m_pPassingPenguin->SetMoveDirection(CPassingPenguin::MOVE_DIRECTION_RIGHT);
				}
			}
		}

	}
}

//======================================================
//	描画処理
//======================================================
void CFlagRaicingGame_rule::Draw(void)
{
	int nPlayerNum = CCountSelect::GetPlayerNum();

	for (int nCnt = 0; nCnt < nPlayerNum; nCnt++)
	{
		m_PlayerPoint.bPoint[nCnt]->Draw();
	}
}

//======================================================
//	右か左かの判別処理
//======================================================
void CFlagRaicingGame_rule::FlagJudge(void)
{
	// プレイヤー数
	int nPlayerNum = CCountSelect::GetPlayerNum();
	CFlipper*pCaptainFlipper;
	CFlipper*pPlayerFlipper;

	// キャプテンの旗判別
	pCaptainFlipper = m_pCaptain->GetFlipper();

	// プレイヤーの数分処理を回す
	for (int nCount = 0; nCount < nPlayerNum; nCount++)
	{
		// プレイヤーの旗の判別
		pPlayerFlipper = m_pPlayer[nCount]->GetFlipper();

		// 動きが同じだった場合
		if (pPlayerFlipper->GetState(CFlipper::FLIPPER_TYPE_LEFT) == pCaptainFlipper->GetState(CFlipper::FLIPPER_TYPE_RIGHT)
			&& pPlayerFlipper->GetState(CFlipper::FLIPPER_TYPE_RIGHT) == pCaptainFlipper->GetState(CFlipper::FLIPPER_TYPE_LEFT))
		{
			// 最初に同じ動きになったプレイヤーを探す
			if(PlayerFlagJudge(m_pPlayer[nCount]))
			{
				m_playerVector.push_back(m_pPlayer[nCount]);
			}
		}
	}
}

//======================================================
//	ポイント加算処理
//======================================================
void CFlagRaicingGame_rule::FlagPoint(void)
{
	if (m_playerVector.size() != 0)
	{
		m_playerVector[0]->AddPoint(ADD_POINT_NUM);		// ポイント追加処理
		m_playerVector.clear();							// プレイヤー情報の初期化
	}
}

//======================================================
//	vectorの中身の比較
//======================================================
bool CFlagRaicingGame_rule::PlayerFlagJudge(CPlayer *player)
{
	for (int nCount = 0; nCount < (signed)m_playerVector.size(); nCount++)
	{
		if (m_playerVector[nCount] == player)
		{
			return false;
		}
	}
	return true;
}

//======================================================
//	順位の判定
//======================================================
void CFlagRaicingGame_rule::JudgeRank(void)
{
	/* 数値を昇順にソート */
	for (int nCnt = 0; nCnt < CCountSelect::GetPlayerNum(); ++nCnt)
	{
		for (int nCntSort = nCnt + 1; nCntSort<CCountSelect::GetPlayerNum(); ++nCntSort)
		{
			if (m_pPlayer[nCnt]->GetPoint() < m_pPlayer[nCntSort]->GetPoint())
			{
				CPlayer*pPlayer;
				pPlayer = m_pPlayer[nCnt];
				m_pPlayer[nCnt] = m_pPlayer[nCntSort];
				m_pPlayer[nCntSort] = pPlayer;
			}
		}
	}
	// プレイヤー数処理を回す
	for (int nCnt = 0; nCnt < CCountSelect::GetPlayerNum(); ++nCnt)
	{
		// 順番を入れ替えてリザルトに表示させる
		m_pPlayer[nCnt]->SetRank(nCnt);
		m_pPlayer[nCnt]->SetMoveFlag(false);

		// ミニゲームに順位を送る
		CResult::SetMiniGameRank(CRuleManager::RULE_FLAG_RACING, m_pPlayer[nCnt]->GetPlayerNumber(), m_pPlayer[nCnt]->GetRank());
	}
	// 仮のリザルト表示
	CMiniResult::Create();
	// プレイヤーを動けなくする
	m_bPlay = false;
}