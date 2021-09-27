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

//=============================================================================
//���[����Ԃ̐ݒ菈��
//=============================================================================
void CRuleBase::SetRuleState(RULE_STATE ruleState)
{
	//��Ԃ̕ۑ�
	m_ruleState = ruleState;

	switch (m_ruleState)
	{
	case RULE_STATE_STRAT:
		break;

	//�Q�[�����̏�ԏ���
	case RULE_STATE_GAME:
		GameProcess();
		break;

	//�Q�[���I����Ԃ̏���
	case RULE_STATE_END:
		//�I���\���̃N���G�C�g
		CEndDisplay::Create();
		break;

	//�~�j���U���g��Ԃ̏���
	case RULE_STATE_MINI_RESULT:
		MiniResultProcess();
		break;

	default:
		break;
	}
}
