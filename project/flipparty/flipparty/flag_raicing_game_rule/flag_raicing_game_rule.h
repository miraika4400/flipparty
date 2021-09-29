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
class CPlayerFlagRaicing;
class CCaptain;
class CCamera;
class CTimeLimit;
class CBlind;
class CPassingPenguin;
class CNumber;

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

	CFlagRaicingGame_rule();
	~CFlagRaicingGame_rule();

	static CFlagRaicingGame_rule* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void GameProcess(void);
	void MiniResultProcess(void);
	void JudgeRank(void);					// 順位の判定

	static TRUN GetGameTrun(void) { return m_eTrun; }		// ターン情報の取得
	static void SetGameTrun(TRUN Trun) { m_eTrun = Trun; }	// ターン情報の設定
	static CBlind *GetBlind(void) { return m_pBlind; }
	static CPlayerFlagRaicing *GetPlayer(int playerNum) { return m_pPlayer[playerNum]; }

	static void SetCaptainData(CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state);
	static void SetPlayerData(int nPlayerNum, CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state);
private:
	
	static CPlayerFlagRaicing *m_pPlayer[MAX_PLAYER_NUM];	// プレイヤーへのポインタ
	CCamera *m_pCamera;				// カメラへのポインタ
	CCaptain *m_pCaptain;			// キャプテンのポインタ
	static CBlind *m_pBlind;					//ブラインドクラスのポインタ

	int m_nRandTime;				// フラッグを上げる間隔
	int m_nCntTime;					// 時間計算

	bool m_bPlay;					// プレイヤーが動くか動かないかの判別
	static TRUN m_eTrun;			// 上げるか上げないかの判別
	CTimeLimit * m_pTimeLimit;		// 制限時間クラス
	CPassingPenguin *m_pPassingPenguin;	//通過ペンギンクラス
	static FLIPPER_DATA m_CaptainData;	//キャプテンの行動データの保存変数
	static std::vector<int> m_vecPlayerNumber;	//行動済みプレイヤー番号の保存変数
};


#endif