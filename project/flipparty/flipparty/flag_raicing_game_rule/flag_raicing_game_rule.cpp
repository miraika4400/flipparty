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
#include "orderPolygon.h"
#include "player_flag_raicing.h"
#include "add_point_display.h"

//======================================================
//	マクロ定義
//======================================================
#define PLAYER_SPACE 110.0f				// プレイヤー位置の間隔
#define POINT_UI_SPACE 325.0f			// 点数の位置間隔
#define TIME_SET 180					// 制限時間の設定
#define TRUN_SET 40						// ターンの制限時間の設定
#define ADD_POINT_NUM_RANK1 3			// 一番目のポイント加算値
#define ADD_POINT_NUM_RANK2 2			// 二番目のポイント加算値
#define ADD_POINT_NUM_RANK3 1			// 三番目のポイント加算値
#define ADD_POINT_NUM_RANK4 0			// 四番目のポイント加算値

#define FLAG_PLAYER_POS_Y_NUM -100.0f	// プレイヤーのY座標
#define FLAG_PLAYER_POS_Z_NUM -50.0f	// プレイヤーのZ座標

#define POINT_UI_POS_Y_NUM 640.0f		// 点数のY座標
#define POINT_UI_POS_Z_NUM 5.0f			// 点数のZ座標
#define POINT_UI_SIZE_X_NUM 60.0f		// 点数UI横幅の大きさ
#define POINT_UI_SIZE_Y_NUM 30.0f		// 点数UI縦幅の大きさ

#define FLAG_CAPTAIN_POS_X_NUM 0.0f		// キャプテンのX座標
#define FLAG_CAPTAIN_POS_Y_NUM -98.0f	// キャプテンのY座標
#define FLAG_CAPTAIN_POS_Z_NUM -220.0f	// キャプテンのZ座標
#define PASSING_PENGUIN_POS D3DXVECTOR3(400.0f, -90.0f, -100.0f)
#define RAND_FLAG rand() % 180 + 50		// フラッグの上げる間隔の設定

//======================================================
//	静的メンバ変数宣言初期化
//======================================================
CFlagRaicingGame_rule::TRUN CFlagRaicingGame_rule::m_eTrun
	= CFlagRaicingGame_rule::CAPTAIN_TRUN;	// キャプテンのターンかプレイヤーのターンかを判別する変数
CBlind *CFlagRaicingGame_rule::m_pBlind = NULL;	//ブラインドクラスのポインタ変数
CPlayerFlagRaicing *CFlagRaicingGame_rule::m_apPlayer[MAX_PLAYER_NUM] = {};
CFlagRaicingGame_rule::FLIPPER_DATA CFlagRaicingGame_rule::m_CaptainData = {};
CFlagRaicingGame_rule::ANSWER_DATA CFlagRaicingGame_rule::m_answerData = {};
int nAddPoint[MAX_PLAYER_NUM]=
{
	ADD_POINT_NUM_RANK1,ADD_POINT_NUM_RANK2,ADD_POINT_NUM_RANK3,ADD_POINT_NUM_RANK4
};

//======================================================
//	コンストラクタ
//======================================================
CFlagRaicingGame_rule::CFlagRaicingGame_rule()
{
	// 変数の初期化
	m_pCaptain = NULL;
	m_nCntTime = 0;
	m_nRandTime = 0;
	m_pTimeLimit = NULL;
	m_bPlay = true;
	m_pBlind = NULL;
	m_pPassingPenguin = NULL;
	m_CaptainData.type = CFlipper::FLIPPER_TYPE_LEFT;
	m_CaptainData.state = CFlipper::FLIPPER_STATE_NONE;
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

	m_nRandTime = 30;

	//カメラの生成
	CManager::SetCamera(CFlagRaicingGameCamera::Create());

	// プレイヤーの人数取得
	int nPlayerNum = CCountSelect::GetPlayerNum();
	float posX = 0 + ((float)(nPlayerNum - 1) * PLAYER_SPACE) / 2;// プレイヤー位置の調整
	float posXUI = SCREEN_WIDTH / 2 - ((float)(nPlayerNum - 1) * POINT_UI_SPACE) / 2;// 点数の位置調整

	// プレイヤーの人数分プレイヤー生成
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		// プレイヤーの生成
		m_apPlayer[nCntPlayer] = CPlayerFlagRaicing::Create(D3DXVECTOR3(posX, FLAG_PLAYER_POS_Y_NUM, FLAG_PLAYER_POS_Z_NUM), nCntPlayer);
		
		// ポイントUIの生成
		CFlagRaicingGamePolygon::Create(
			nCntPlayer,D3DXVECTOR3(posXUI, POINT_UI_POS_Y_NUM, 0.0f));

		//点数加算UIの位置設定
		m_apPlayer[nCntPlayer]->GetAddPoitDisplay()->SetPos(D3DXVECTOR3(posXUI, 550.0f, 0.0f));
		
		posX -= PLAYER_SPACE;
		posXUI += POINT_UI_SPACE;
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
	CStage::Create(D3DXVECTOR3(FLAG_CAPTAIN_POS_X_NUM, FLAG_PLAYER_POS_Y_NUM, FLAG_CAPTAIN_POS_Z_NUM), CStage::STAGE_TYPE_LARGE)->SetSize(D3DXVECTOR3(3.0f, 1.0f, 1.0f));

	// 海の生成
	CSea::Create(D3DXVECTOR3(0.0f, FLAG_PLAYER_POS_Y_NUM -14.0f, 0.0f), 0.001f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, FLAG_PLAYER_POS_Y_NUM -12.0f, 0.0f), 0.0025f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, FLAG_PLAYER_POS_Y_NUM -10.0f, 0.0f), 0.004f, CSea::TYPE_NORMAL);

	//キャプテンデータの初期化
	m_CaptainData.type = CFlipper::FLIPPER_TYPE_LEFT;
	m_CaptainData.state = CFlipper::FLIPPER_STATE_NONE;

	m_answerData.nAnswerNum = 0;
	m_answerData.vecPlayerNumber.clear();

	//ターンの初期化
	m_eTrun = CFlagRaicingGame_rule::PLAYER_TRUN;

	return S_OK;
}

//======================================================
//	終了処理
//======================================================
void CFlagRaicingGame_rule::Uninit(void)
{
	// BGM停止
	CManager::GetSound()->Stop(CSound::LABEL_BGM_FLAG_GAME);
}

//======================================================
//	更新処理
//======================================================
void CFlagRaicingGame_rule::Update(void)
{
	// プレイヤーの人数取得
	int nPlayerNum = CCountSelect::GetPlayerNum();

	if (GetRuleState() == RULE_STATE_GAME)
	{
		// プレイヤーを必要時以外動けなくするようにする処理
		if (m_bPlay)
		{
			// 乱数の初期化
			srand((unsigned int)time(NULL));
			
			// 時間経過で次の動作に入る
			if (m_nCntTime == m_nRandTime)
			{
				m_nRandTime = RAND_FLAG;	// ランダムで次に旗の変更するタイミングを設定

				SetGameTrun(CAPTAIN_TRUN);	// キャプテンのターンに変更
				m_nCntTime = 0;				// タイムの初期化

				//行動済みデータを削除
				m_answerData.nAnswerNum = 0;
				m_answerData.vecPlayerNumber.clear();
			}
			// 時間計算処理
			++m_nCntTime;

			//残りの制限時間を取得
			int nTimeLimit = m_pTimeLimit->GetTimeLimit();

			// 制限時間が0以下の時
			if (nTimeLimit <= 0)
			{
				//ゲーム終了状態へ移行
				SetRuleState(CRuleBase::RULE_STATE_END);
				
				// プレイヤーを動けなくする
				m_bPlay = false;
			}

			//ブラインドに現在タイムを与える
			if (m_pBlind)
			{
				m_pBlind->SetTime(nTimeLimit);
			}

			if (m_pPassingPenguin)
			{
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
			if (nTimeLimit == (TRUN_SET / 2))
			{
				//指示ポリゴンを使用しなくする
				COrderPolygon::SetUse(false);
			}
		}
	}
}

//======================================================
//	描画処理
//======================================================
void CFlagRaicingGame_rule::Draw(void)
{
}

//======================================================
//	ゲーム用の処理
//======================================================
void CFlagRaicingGame_rule::GameProcess(void)
{
	// BGM再生
	CManager::GetSound()->Play(CSound::LABEL_BGM_FLAG_GAME);
}

//======================================================
//	ミニリザルト用の処理
//======================================================
void CFlagRaicingGame_rule::MiniResultProcess(void)
{
	//順位を設定
	JudgeRank();
}

//======================================================
//	順位の判定
//======================================================
void CFlagRaicingGame_rule::JudgeRank(void)
{
	std::vector<CPlayerFlagRaicing *> vecPlayer;

	for (int nCnt = 0; nCnt < CCountSelect::GetPlayerNum(); ++nCnt)
	{
		vecPlayer.push_back(m_apPlayer[nCnt]);
	}

	/* 数値を昇順にソート */
	for (int nCnt = 0; nCnt < CCountSelect::GetPlayerNum(); ++nCnt)
	{
		for (int nCntSort = nCnt + 1; nCntSort<CCountSelect::GetPlayerNum(); ++nCntSort)
		{
			if (vecPlayer[nCnt]->GetPoint() < vecPlayer[nCntSort]->GetPoint())
			{
				CPlayerFlagRaicing*pPlayer;
				pPlayer = vecPlayer[nCnt];
				vecPlayer[nCnt] = vecPlayer[nCntSort];
				vecPlayer[nCntSort] = pPlayer;
			}
		}
	}
	// プレイヤー数処理を回す
	for (int nCnt = 0; nCnt < CCountSelect::GetPlayerNum(); ++nCnt)
	{
		// 順番を入れ替えてリザルトに表示させる
		vecPlayer[nCnt]->SetRank(nCnt);

		if (nCnt != 0)
		{
			//ひとつ前のプレイヤーとポイント数が同じ時
			if (vecPlayer[nCnt]->GetPoint() == vecPlayer[nCnt - 1]->GetPoint())
			{
				// 同順位として設定
				vecPlayer[nCnt]->SetRank(vecPlayer[nCnt - 1]->GetRank());
			}
		}

		vecPlayer[nCnt]->SetMoveFlag(false);

		// ミニゲームに順位を送る
		CResult::SetMiniGameRank(CRuleManager::RULE_FLAG_RACING, vecPlayer[nCnt]->GetPlayerNumber(), vecPlayer[nCnt]->GetRank());
	}

	// 仮のリザルト表示
	CMiniResult::Create();
}

//======================================================
//	キャプテンの羽状態の情報保存
//======================================================
void CFlagRaicingGame_rule::SetCaptainData(CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state)
{
	m_CaptainData.type = type;
	m_CaptainData.state = state;
}

//======================================================
//	プレイヤーの回答判定
//======================================================
void CFlagRaicingGame_rule::SetPlayerData(int nPlayerNum, CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state)
{
	//プレイヤーの行動ターン時のみ処理をする
	if (m_eTrun == CFlagRaicingGame_rule::PLAYER_TRUN)
	{
		//参加プレイヤー数を取得
		int nEntryNum = CCountSelect::GetPlayerNum();

		//現在のサイズ（個数）を取得
		int nVecNum = m_answerData.vecPlayerNumber.size();

		// 現在のサイズ（個数）が参加プレイヤー数より小さい間
		if (nVecNum < nEntryNum)
		{
			//すでに情報が存在する場合、重複設定をしないように確認する
			if (nVecNum != 0)
			{
				for (int nCntCheck = 0; nCntCheck < nVecNum; nCntCheck++)
				{
					//行動済みのプレイヤーだった場合
					if (m_answerData.vecPlayerNumber[nCntCheck] == nPlayerNum)
					{
						//処理終了
						return;
					}
				}
			}

			//キャプテンが変更した羽とプレイヤーが変更した羽が一緒だった場合
			if (m_CaptainData.type == type &&
				m_CaptainData.state == state)
			{
				//参加人数によって加算するポイントを変更するための基数を生成
				int nIndex = MAX_PLAYER_NUM - CCountSelect::GetPlayerNum();

				//ポイント加算
				m_apPlayer[nPlayerNum]->AddPoint(nAddPoint[m_answerData.nAnswerNum + nIndex]);

				//加算されたポイント数表示を行う
				m_apPlayer[nPlayerNum]->GetAddPoitDisplay()->SetDisplay((CAddPointDisplay::POINT_DISPLAY_TYPE)(m_answerData.nAnswerNum + nIndex));

				//正答数を加算
				m_answerData.nAnswerNum++;
			}
			//ミスした場合
			else
			{
				//ミス表示を行う
				m_apPlayer[nPlayerNum]->GetAddPoitDisplay()->SetDisplay(CAddPointDisplay::POINT_DISPLAY_TYPE_MISS);
			}

			//行動したプレイヤーの番号を登録
			m_answerData.vecPlayerNumber.push_back(nPlayerNum);
		}
	}
}