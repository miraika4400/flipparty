//=============================================================================
//
// resultboard�w�b�_ [resultboard.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _RESULT_BOARD_H_
#define _RESULT_BOARD_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"
#include "rule_manager.h"

//=============================
// �O���錾
//=============================
class CPolygon;
class CNumber;

//=============================
// �}�N����`
//=============================
#define POINT_MAX_DIGIT 2 // �X�R�A�ő包��

//=============================
//�N���X��`
//=============================

//���U���g�{�[�h�N���X
class CResultBoard : public CScene
{
public:
	//============
	// �����o�֐�
	//============
	CResultBoard();
	~CResultBoard();

	static CResultBoard *Create(int nPlayerNum, D3DXVECTOR3 pos); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:
	D3DXCOLOR ReturnBackColor(void); // �v���C���[�ԍ��ɉ������J���[��Ԃ�
	void CreatePlayerNumber(void);   // �v���C���[�ԍ��̐���
	void CreateGameIcon(void);       // �Q�[���A�C�R���̐���
	void CreateGameRank(void);       // �Q�[�����ʃ|���S���̐���
	void CreateScore(void);          // �X�R�A�|���S���̐���

	//============
	// �����o�ϐ�
	//============
	D3DXVECTOR3 m_pos;  // ���W
	int m_nPlayerNum;
	CNumber *m_apScoreNumber[POINT_MAX_DIGIT];           // �X�R�A�̐����|���S��
	CPolygon * m_pBack;                                  // �w�i
	CPolygon * m_pPlayerNumPolygon;                      // �v���C���[�ԍ��|���S��
	CPolygon * m_apMinigameIcon[CRuleManager::RULE_MAX]; // �~�j�Q�[���̃A�C�R��
	CPolygon * m_apMinigameRank[CRuleManager::RULE_MAX]; // �~�j�Q�[���̏���
};

#endif