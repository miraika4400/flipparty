//=============================================================================
//
// rule_base処理[rule_base.cpp]
// Author :山田　陵太
//
//=============================================================================
#include "rule_base.h"
#include "startcount.h"
#include "enddisplay.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CRuleBase::CRuleBase()
{
	m_ruleState = RULE_STATE_STRAT;
	CStratCount::Create();
}

//=============================================================================
//ルール状態の設定処理
//=============================================================================
void CRuleBase::SetRuleState(RULE_STATE ruleState)
{
	//状態の保存
	m_ruleState = ruleState;

	switch (m_ruleState)
	{
	case RULE_STATE_STRAT:
		break;

	//ゲーム中の状態処理
	case RULE_STATE_GAME:
		GameProcess();
		break;

	//ゲーム終了状態の処理
	case RULE_STATE_END:
		//終了表示のクリエイト
		CEndDisplay::Create();
		break;

	//ミニリザルト状態の処理
	case RULE_STATE_MINI_RESULT:
		MiniResultProcess();
		break;

	default:
		break;
	}
}
