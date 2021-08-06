//===================================================
//
//    �X�R�A�N���X�̏���[score.cpp]
//    Author:���V ����
//
//====================================================

//**********************************
//�C���N���[�h
//**********************************
#include "score.h"
#include "number.h"

//==============================
//�ÓI�����o�ϐ��錾
//==============================
int CScore::m_nScore = 0;

//==================================
// �R���X�g���N�^
//==================================
CScore::CScore()
{
	// �i���o�[�̃N���A
	memset(m_apNumber, 0, sizeof(m_apNumber));
}

//==================================
// �f�X�g���N�^
//==================================
CScore::~CScore()
{
}

//==================================
// �N���G�C�g
//==================================
CScore * CScore::Create(void)
{
	// �������̊m��
	CScore *pScore = new CScore;

	// ����������
	pScore->Init();

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	pScore->SetPriority(OBJTYPE_UI);

	return pScore;
}

//==================================
// ����������
//==================================
HRESULT CScore::Init(void)
{
	// �ő包�������[�v
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(0,
			D3DXVECTOR3((float)(1000 + nCntDigit * 40), 50.0f, 0.0f),
			D3DXVECTOR3(20, 20, 0),
			D3DXCOLOR(0.8f, 0.3f, 0.8f, 1.0f));
	}
	// �X�R�A�̏�����
	m_nScore = 0;

	return S_OK;
}

//==================================
// �I������
//==================================
void CScore::Uninit(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{
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
void CScore::Update(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Update();

		m_apNumber[nCntDigit]->SetNumber((int)((m_nScore % (int)(powf(10.0f, (MAX_SCORE_DIGIT - nCntDigit)))) / (float)(powf(10, (MAX_SCORE_DIGIT - nCntDigit - 1)))));
	}
}

//==================================
// �`�揈��
//==================================
void CScore::Draw(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Draw();
	}
}
