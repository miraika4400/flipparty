//======================================================
//
//	旗上げゲームの処理[flag_raicing_game_rule.cpp]
//	Author : 筒井 俊稀
//
//======================================================
//======================================================
//	インクルードファイル
//======================================================
#include "flag_raicing_game_rule.h"
#include "manager.h"
#include "count_selection.h"
#include "player.h"
#include "captain.h"
#include "flipper.h"
#include "camera_tps.h"
#include "mini_result.h"

//======================================================
//	静的メンバ変数宣言初期化
//======================================================
CFlagRaicingGame_rule::TRUN CFlagRaicingGame_rule::m_eLoop
	= CFlagRaicingGame_rule::CAPTAIN_TRUN;	// キャプテンのターンかプレイヤーのターンかを判別する変数

//======================================================
//	マクロ定義
//======================================================
#define PLAYER_SPACE (150.0f)	// プレイヤー位置の間隔
#define TIME_SET (180)			// 制限時間の設定
#define TRUN_SET (20)			// ターン数の設定
#define ADD_POINT_NUM (1)		// ポイント合計値の設定

//======================================================
//	コンストラクタ
//======================================================
CFlagRaicingGame_rule::CFlagRaicingGame_rule()
{
	// 変数の初期化
	ZeroMemory(&m_pPlayer, sizeof(m_pPlayer));
	m_pCaptain = NULL;
	m_nCntInputPlayer = 0;
	m_nCntTime = 0;
	m_nPoint = 0;
	m_nTarn = 0;
	m_bPlay = true;
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
	m_bPlay = true;

	//カメラの生成
	CGame::SetCamera(CTpsCamera::Create());

	// プレイヤーの人数取得
	int nPlayerNum = CCountSelect::GetPlayerNum();
	// プレイヤーの人数分プレイヤー生成
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		float posX = 0 + ((float)(nCntPlayer)*PLAYER_SPACE) / 2;// 位置の調整
		// プレイヤーの生成
		m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(posX, -50.0f, 30.0f), nCntPlayer);
	}
	// キャプテンの生成
	m_pCaptain = CCaptain::Create(D3DXVECTOR3(0.0f, -35.0f, -30.0f));

	return S_OK;
}

//======================================================
//	終了処理
//======================================================
void CFlagRaicingGame_rule::Uninit(void)
{

}

//======================================================
//	更新処理
//======================================================
void CFlagRaicingGame_rule::Update(void)
{
	// プレイヤーを必要時以外動けなくするようにする処理
	if (m_bPlay)
	{
		// 時間計算処理
		m_nCntTime++;
		// 判別処理
		FlagJudge();

		// 時間経過で次の動作に入る
		if (m_nCntTime == TIME_SET)
		{
			m_nTarn++;					//ターンを進める
			SetGameLoop(CAPTAIN_TRUN);	//キャプテンのターンに変更
			m_nCntTime = 0;				//タイムの初期化
			FlagPoint();				//ポイント追加
		}
		// 上限のターン数を上回ったらゲームを終了させる
		if (m_nTarn == TRUN_SET)
		{
			JudgeRank();
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
		if (pPlayerFlipper->GetState(CFlipper::FLIPPER_TYPE_LEFT) == pCaptainFlipper->GetState(CFlipper::FLIPPER_TYPE_LEFT)
			&& pPlayerFlipper->GetState(CFlipper::FLIPPER_TYPE_RIGHT) == pCaptainFlipper->GetState(CFlipper::FLIPPER_TYPE_RIGHT))
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
	}
	// 仮のリザルト表示
	CMiniResult::Create();
	// プレイヤーを動けなくする
	m_bPlay = false;
}