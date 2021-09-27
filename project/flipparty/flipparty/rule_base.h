//=============================================================================
//
// rule_base�w�b�_[rule_base.h]
// Author :���V ����
//
//=============================================================================
#ifndef _RULE_BASE_H_
#define _RULE_BASE_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"

//*****************************
// �}�N����`
//*****************************
#define MAX_PLAYER_NUM 4    // �v���C���[�̐l��

//*****************************
// �O���錾
//*****************************

//*****************************
// �N���X��`
//*****************************
// ���[����b�N���X
class CRuleBase
{
public:
	//============
	//�Q�[�����[���̏�Ԃ̗�
	//============
	typedef enum
	{
		RULE_STATE_STRAT = 0,	//�X�^�[�g���
		RULE_STATE_GAME,		//�Q�[����
		RULE_STATE_END,			//�I�����
		RULE_STATE_MINI_RESULT,	//�~�j���U���g���
		RULE_STATE_MAX,
	}RULE_STATE;

	//============
	//�����o�֐�
	//============
	CRuleBase();
	virtual ~CRuleBase() {};

	virtual HRESULT Init(void) = 0; // ������
	virtual void Uninit(void) = 0;  // �I��
	virtual void Update(void) = 0;  // �X�V
    virtual void Draw(void) = 0;    // �`��

	void EndProcess(void);
	virtual void GameProcess(void);
	virtual void MiniResultProcess(void);

	RULE_STATE GetRuleState(void) { return m_ruleState; }
	void SetRuleState(RULE_STATE ruleState);

private:
	//============
	// �����o�ϐ�
	//============
	RULE_STATE m_ruleState;	//���[���̏��
};

#endif