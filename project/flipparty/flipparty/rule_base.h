//=============================================================================
//
// rule_baseヘッダ[rule_base.h]
// Author :増澤 未来
//
//=============================================================================
#ifndef _RULE_BASE_H_
#define _RULE_BASE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"

//*****************************
// マクロ定義
//*****************************
#define MAX_PLAYER_NUM 4    // プレイヤーの人数

//*****************************
// 前方宣言
//*****************************

//*****************************
// クラス定義
//*****************************
// ルール基礎クラス
class CRuleBase
{
public:
	//============
	//ゲームルールの状態の列挙
	//============
	typedef enum
	{
		RULE_STATE_STRAT = 0,	//スタート状態
		RULE_STATE_GAME,		//ゲーム中
		RULE_STATE_END,			//終了状態
		RULE_STATE_MINI_RESULT,	//ミニリザルト状態
		RULE_STATE_MAX,
	}RULE_STATE;

	//============
	//メンバ関数
	//============
	CRuleBase();
	virtual ~CRuleBase() {};

	virtual HRESULT Init(void) = 0; // 初期化
	virtual void Uninit(void) = 0;  // 終了
	virtual void Update(void) = 0;  // 更新
    virtual void Draw(void) = 0;    // 描画

	void EndProcess(void);
	virtual void GameProcess(void);
	virtual void MiniResultProcess(void);

	RULE_STATE GetRuleState(void) { return m_ruleState; }
	void SetRuleState(RULE_STATE ruleState);

private:
	//============
	// メンバ変数
	//============
	RULE_STATE m_ruleState;	//ルールの状態
};

#endif