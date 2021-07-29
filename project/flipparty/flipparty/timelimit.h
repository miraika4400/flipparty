//=============================================================================
//
// time_limit�w�b�_ [time_limit.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TIME_H_
#define _TIME_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//�O���錾
//*****************************
class CNumber;

//*****************************
//�}�N����`
//*****************************
#define MAX_TIME_NUM 2 // �^�C���ɕK�v�ȃi���o�[�̐�

//*****************************
//�N���X��`
//*****************************

//�^�C���N���X
class CTimeLimit : public CScene
{
public:
	//============
	// �����o�֐�
	//============
	CTimeLimit();
	~CTimeLimit();

	//static
	static CTimeLimit *Create(int nLimitTime); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

	// �������Ԃ̎擾
	int GetTimeLimit(void) { return m_nLimitTime; }
	int GetTimeCount(void) { return m_nCntTime; }

	void SetTimeFlag(bool bIsTimeCount) { m_bIsTimeCount = bIsTimeCount; }	//�J�E���g�̍X�V���邩�ǂ����̐ݒ�
private:
	//============
	// �����o�ϐ�
	//============
	int m_nLimitTime;                  // ��������
	CNumber* m_apNumber[MAX_TIME_NUM]; // �^�C���`��p�̃|���S��
	int m_nCntTime;                    // ���ԃJ�E���g�p
	bool m_bIsTimeCount;				//���Ԃ��J�E���g���邩�ǂ���
};

#endif