//===================================================
//
//   �������ԃN���X�̏���[time.cpp]
//    Author:���V ����
//
//====================================================

//**********************************
//�C���N���[�h
//**********************************
#include "timelimit.h"
#include "number.h"
#include "manager.h"

//**********************************
//�}�N����`
//**********************************
#define UI_HEIGHT 80.0f                             // �ʒu*Y��
#define NUMBER_SIZE D3DXVECTOR3(20.0f, 20.0f, 0.0f) // �T�C�Y
#define NUMBER_SPACE 40.0f                          // �����Ԃ̊Ԋu
#define ONE_SECOND_COUNT 60                         // ��b�̃J�E���g(�t���[��)��

//**********************************
//�ÓI�����o�ϐ��錾
//**********************************

//==================================
// �R���X�g���N�^
//==================================
CTimeLimit::CTimeLimit() :CScene(OBJTYPE_UI)
{
	// �i���o�[�̃N���A
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_nLimitTime = 0;
	m_nCntTime = 0;
	m_bIsTimeCount = false;
}

//==================================
// �f�X�g���N�^
//==================================
CTimeLimit::~CTimeLimit()
{
}

//==================================
// �N���G�C�g
//==================================
CTimeLimit * CTimeLimit::Create(int nLimitTime)
{
	// �������̊m��
	CTimeLimit *pTime = new CTimeLimit;

	// ����������
	pTime->Init();
	pTime->m_nLimitTime = nLimitTime;

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	pTime->SetPriority(OBJTYPE_UI);

	return pTime;
}

//==================================
// ����������
//==================================
HRESULT CTimeLimit::Init(void)
{
	float posX = 0 - ((float)(MAX_TIME_NUM - 1) * NUMBER_SPACE) / 2;

	// �ő啪���[�v
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_NUM; nCntDigit++)
	{
		// �i���o�[����
		m_apNumber[nCntDigit] = CNumber::Create(0,
			D3DXVECTOR3((SCREEN_WIDTH/2) + posX, UI_HEIGHT, 0.0f),
			NUMBER_SIZE,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		posX += NUMBER_SPACE;
	}

	// �J�E���g������
	m_nCntTime = 0;

	//�X�V�t���O�̏�����
	m_bIsTimeCount = true;
	return S_OK;
}

//==================================
// �I������
//==================================
void CTimeLimit::Uninit(void)
{
	// �ő啪���[�v
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_NUM; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{
			// �I������
			m_apNumber[nCntDigit]->Uninit();
			delete m_apNumber[nCntDigit];
			m_apNumber[nCntDigit] = NULL;
		}
	}

	// �J������
	Release();
}

//==================================
// �X�V����
//==================================
void CTimeLimit::Update(void)
{
	if (m_nLimitTime > 0)
	{
		//true�̎��̂݃J�E���g��i�߂�
		if (m_bIsTimeCount)
		{
			// �J�E���g��i�߂�
			m_nCntTime++;
			// �J�E���g�����ȏ�̎�
			if (m_nCntTime >= ONE_SECOND_COUNT)
			{
				// �J�E���g�̏�����
				m_nCntTime = 0;
				// �������Ԃ����炷
				m_nLimitTime--;

				if (m_nLimitTime <= 0)
				{
					m_nLimitTime = 0;
				}
			}
		}
		// �ő啪���[�v
		for (int nCntDigit = 0; nCntDigit < MAX_TIME_NUM; nCntDigit++)
		{
			// �i���o�[�̃A�b�v�f�[�g
			m_apNumber[nCntDigit]->Update();

			// �e���̌v�Z
			m_apNumber[nCntDigit]->SetNumber((m_nLimitTime % (int)(powf(10.0f, (MAX_TIME_NUM - nCntDigit)))) / (float)(powf(10.0, (MAX_TIME_NUM - nCntDigit - 1))));
		}
	}

}

//==================================
// �`�揈��
//==================================
void CTimeLimit::Draw(void)
{
	// �ő啪���[�v
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_NUM; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Draw();
	}
}
