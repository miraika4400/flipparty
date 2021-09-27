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
class CFlyGamePlayer;
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
	// �v���C���[�擾����
	static CFlyGamePlayer * GetPlayer(int nPlayerNum) { return m_pPlayer[nPlayerNum]; }
	static bool GetPlayFlag(void) { return m_bPlay; }

	void GameProcess(void);
	void MiniResultProcess(void);
private:
	void JudgeRank(void); // ���ʔ���
	//============
	// �����o�ϐ�
	//============
	CTimeLimit * m_pTimeLimit; // �������ԃN���X
	static bool m_bPlay; // �v���C���t���O
	static CFlyGamePlayer * m_pPlayer[4];
};


#endif