//======================================================
//
//	旗上げゲームの処理[flag_raicing_game_rule.h]
//	Author : 筒井 俊稀
//
//======================================================

//二重インクルード防止
#ifndef _FLAG_RAICING_GAME_RULE_H_
#define _FLAG_RAICING_GAME_RULE_H_

//======================================================
//	インクルードファイル
//======================================================
#include "rule_base.h"
#include "flipper.h"

//======================================================
//	マクロ定義
//======================================================


//======================================================
//	前方前言
//======================================================
class CPolygon;
class CPlayer;
class CCaptain;
class CCamera;
class CTimeLimit;

//======================================================
//	クラス定義
//======================================================
class CFlagRaicingGame_rule : public CRuleBase
{
public:
	typedef enum
	{
		PLAYER_TRUN = 0,
		CAPTAIN_TRUN,
		TRUN_END
	}TRUN;

	CFlagRaicingGame_rule();
	~CFlagRaicingGame_rule();

	static CFlagRaicingGame_rule* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void FlagJudge(void);	// プレイヤーとキャプテンの旗上げ判別関数
	void FlagPoint(void);	// プレイヤーとキャプテンの旗が上がっているか下がっているかの判定処理関数
	bool PlayerFlagJudge(CPlayer *player);
	void JudgeRank(void);			// 順位の判定

	static TRUN GetGameLoop(void) { return m_eLoop; }
	static void SetGameLoop(TRUN loop) { m_eLoop = loop; }
private:
	// CPlayerの動的配列
	std::vector<CPlayer*> m_playerVector;

	CPlayer *m_pPlayer[MAX_PLAYER_NUM];		// プレイヤーへのポインタ
	CCamera *m_pCamera;						// カメラへのポインタ
	CCaptain *m_pCaptain;

	int m_nRandTime;
	int m_nCntTime;
	int m_nPoint;
	int m_nTarn;
	int m_nCntInputPlayer;		// 行動済みのプレイヤー数カウント

	bool m_bPlay;
	static TRUN m_eLoop;			// 上げるか上げないかの判別
	CTimeLimit * m_pTimeLimit;		// 制限時間クラス

};


#endif