//=============================================================================
//
// rule_fly�w�b�_[rule_fly.h]
// Author :���V ����
//
//=============================================================================
#ifndef _RULE_FLY_GAME_H_
#define _RULE_FLY_GAME_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "rule_base.h"

//*****************************
// �}�N����`
//*****************************

//*****************************
// �O���錾
//*****************************
class CTimeLimit;
//*****************************
// �N���X��`
//*****************************
// �t���C�Q�[�����[���N���X
class CRuleFly :public CRuleBase
{
public:
	//============
	//�����o�֐�
	//============
	CRuleFly();
	~CRuleFly();

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

	static CRuleFly *Create(void); // �N���X����

private:
	void JudgeRank(void); // ���ʔ���
	//============
	// �����o�ϐ�
	//============
	CTimeLimit * m_pTimeLimit; // �������ԃN���X
	bool m_bPlay; // �v���C���t���O
};


#endif