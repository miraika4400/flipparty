//=============================================================================
//
// rule_base����[rule_base.cpp]
// Author :�R�c�@�ˑ�
//
//=============================================================================
#include "rule_base.h"
#include "startcount.h"
#include "enddisplay.h"


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CRuleBase::CRuleBase()
{
	m_ruleState = RULE_STATE_STRAT;
	CStratCount::Create();
	
}

void CRuleBase::EndProcess(void)
{
	CEndDisplay::Create();
}

void CRuleBase::GameProcess(void)
{
}

void CRuleBase::MiniResultProcess(void)
{
}

void CRuleBase::SetRuleState(RULE_STATE ruleState)
{
	m_ruleState = ruleState;

	switch (m_ruleState)
	{
	case RULE_STATE_STRAT:
		break;

	case RULE_STATE_GAME:
		GameProcess();
		break;

	//�Q�[���I����Ԃ̏���
	case RULE_STATE_END:
		EndProcess();
		break;

	//�~�j���U���g��Ԃ̏���
	case RULE_STATE_MINI_RESULT:
		MiniResultProcess();
		break;

	default:
		break;
	}
	
}
