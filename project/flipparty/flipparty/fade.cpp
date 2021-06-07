//===================================================
//
//    �t�F�[�h�N���X�̏���[fade.cpp]
//    Author:���V ����
//
//====================================================

//**********************************
//�C���N���[�h
//**********************************
#include "fade.h"
#include "polygon.h"

//**********************************
//�}�N����`
//**********************************
#define FADE_RATE 0.06f


//==================================
// �R���X�g���N�^
//==================================
CFade::CFade()
{
	m_col = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_pPolygon = NULL;
	m_modeNext = CManager::MODE_GAME;
	m_fade = FADE_NONE;
}

//==================================
// �f�X�g���N�^
//==================================
CFade::~CFade()
{
}

//==================================
// �N���G�C�g
//==================================
CFade * CFade::Create(void)
{
	// �������̊m��
	CFade *pFade = new CFade;
	// ������
	pFade->Init();

	return pFade;
}

//==================================
// ����������
//==================================
HRESULT CFade::Init(void)
{
	// �|���S���̐���
	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		m_col);

	return S_OK;
}


//==================================
// �I������
//==================================
void CFade::Uninit(void)
{
	// �|���S���̏I������
	m_pPolygon->Uninit();
	// �������̉��
	delete m_pPolygon;
	m_pPolygon = NULL;
}

//==================================
// �X�V����
//==================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		//�t�F�[�h�C��
		if (m_fade == FADE_IN)
		{
			m_col.a -= FADE_RATE;

			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}

		//�t�F�[�h�A�E�g
		else if (m_fade == FADE_OUT)
		{
			m_col.a += FADE_RATE;
			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				m_fade = FADE_IN;

				// ���[�h�̐؂�ւ�
				CManager::SetMode(m_modeNext);
			}
		}

		// �J���[�̃Z�b�g
		m_pPolygon->SetColor(m_col);
	}
}

//==================================
// �`�揈��
//==================================
void CFade::Draw(void)
{
	// �|���S���̕`��
	m_pPolygon->Draw();
}


//==================================
// �t�F�[�h�̃Z�b�g
//==================================
void CFade::SetFade(CManager::MODE mode)
{
	m_fade = FADE_OUT;
	m_modeNext = mode;
}
