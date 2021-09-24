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
#define PLAYER_NUM 4
#define MAX_POINT_NUM 2

//======================================================
//	前方前言
//======================================================
class CPolygon;
class CPlayer;
class CCaptain;
class CCamera;
class CTimeLimit;
class CBlind;
class CBillboard;
class CPassingPenguin;
class CNumber;
class CFlagRaicingGamePolygon;
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

	typedef struct
	{
		CFlipper::FLIPPER_TYPE type;
		CFlipper::FLIPPER_STATE state;
	}FLIPPER_DATA;

	typedef struct
	{
		FLIPPER_DATA data;
		int PlayerNum;
	}PLAYER_DATA;

	typedef struct
	{
		CFlagRaicingGamePolygon * bPoint[PLAYER_NUM];
	}PLAYER_POINT_VARIABLE;

	CFlagRaicingGame_rule();
	~CFlagRaicingGame_rule();

	static CFlagRaicingGame_rule* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void FlagJudge(void);					// プレイヤーとキャプテンの旗上げ判別関数
	void JudgeRank(void);					// 順位の判定

	static TRUN GetGameTrun(void) { return m_eTrun; }		// ターン情報の取得
	static void SetGameTrun(TRUN Trun) { m_eTrun = Trun; }	// ターン情報の設定
	static CBlind *GetBlind(void) { return m_pBlind; }
	static CPlayer *GetPlayer(int playerNum) { return m_pPlayer[playerNum]; }

	static void SetCaptainData(CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state);
	static void SetPlayerData(int nPlayerNum, CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state);
private:
	
	static CPlayer *m_pPlayer[MAX_PLAYER_NUM];	// プレイヤーへのポインタ
	CCamera *m_pCamera;				// カメラへのポインタ
	CCaptain *m_pCaptain;			// キャプテンのポインタ
	static CBlind *m_pBlind;					//ブラインドクラスのポインタ
	PLAYER_POINT_VARIABLE m_PlayerPoint;
	CNumber *m_apNumber[MAX_POINT_NUM];

	int m_nRandTime;				// フラッグを上げる間隔
	int m_nCntTime;					// 時間計算
	int m_nCntInputPlayer;			// 行動済みのプレイヤー数カウント

	bool m_bPlay;					// プレイヤーが動くか動かないかの判別
	static TRUN m_eTrun;			// 上げるか上げないかの判別
	CTimeLimit * m_pTimeLimit;		// 制限時間クラス
	CPassingPenguin *m_pPassingPenguin;	//通過ペンギンクラス
	static FLIPPER_DATA m_CaptainData;	//キャプテンの行動データ
	static std::vector<PLAYER_DATA> m_vecPlayerData;	//プレイヤーの行動データ
};


#endif