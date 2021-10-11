//=============================================================================
//
// result�w�b�_ [result.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"
#include "rule_base.h"
#include "rule_manager.h"

//*****************************
// �O���錾
//*****************************
class CPolygon;
class CPlayer;
class CRankUI;

//*****************************
//�}�N����`
//*****************************
#define POINT_1ST 30
#define POINT_2ND 20
#define POINT_3RD 10
#define POINT_4TH 0

//*****************************
//�N���X��`
//*****************************

//���U���g�N���X
class CResult : public CScene
{
public:
	//============
	// �\����
	//============
	// ���U���g�|�C���g�W�v�p
	typedef struct
	{
		int nMiniGameRank[CRuleManager::RULE_MAX];
		int nPoint;
	}ResultPoint;

	//============
	// �����o�֐�
	//============
	CResult();
	~CResult();

	static CResult *Create(void); //�N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

	// �W�v�|�C���g�̏�����
	static void ResetResultPoint(void) { ZeroMemory(&m_resultPoint, sizeof(m_resultPoint)); }
	// �~�j�Q�[���̏��ʂ̃Z�b�g ����:�~�j�Q�[���̔ԍ�,�v���C���[�ԍ�,����
	static void SetMiniGameRank(int nMiniGameNum, int nPlayerNum, int nRank) { m_resultPoint[nPlayerNum].nMiniGameRank[nMiniGameNum] = nRank; }
	
	static ResultPoint GetResultPoint(int nPlayerNum) { return m_resultPoint[nPlayerNum]; }
    static int GetRank(int nRank);// ���ʂ̃Q�b�^(�H���쐬)

private:
	// �v���C���[�̃��[�V������ς���
	void ChagePlayerMotion(void);
	// ���ʂ̌v�Z
	void CalculationRank(void);
	// ���ʂ̔��� ����:�����_���̎�true�Ȃ瓯�������N�ɂ���
	void JudgePlayerRank(bool bSamePointRank);
	// �v���C���[�̈ʒu�̒���
	void AdjustPlayerPos(void);
	
	//============
	// �����o�ϐ�
	//============
	static ResultPoint m_resultPoint[MAX_PLAYER_NUM]; // ���U���g�|�C���g�W�v�p

	CPlayer * m_apPlayer[MAX_PLAYER_NUM];  // �v���C���[�|�C���^
	int m_nCntFallTime;                    // �v���C���[��������^�C�~���O�̃J�E���g�p
	int m_nActionRank;                     // �R�P�铙�̃A�N�V�������N��������
	bool m_bShow;                          // ���ʔ��\�t���O
	bool m_bBoard;                         // ���U���g�{�[�h�t���O
	CRankUI * m_apRankUI[MAX_PLAYER_NUM];  // ����UI
};

#endif