////////////////////////////////////////////////////
//
//    ���U���g�N���X�̏���[resultboard.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "flag_raicing_game_polygon.h"
#include "polygon.h"
#include "resource_texture.h"
#include "result.h"
#include "number.h"
#include "flag_raicing_game_rule.h"
#include "player_flag_raicing.h"

//**********************************
// �}�N����`
//**********************************
#define SIZE_BACK D3DXVECTOR3(60.0f,30.0f,0.0f)           // �{�[�h�T�C�Y

#define SIZE_SCORE D3DXVECTOR3 (20.0f ,20.0f ,0.0f ) // �X�R�A�̃T�C�Y
#define SCORE_POS_Y m_pos.y                           // �X�R�AY���W
#define SCORE_SPACE 40.0f                           // �X�R�A�e���̊Ԋu
#define COLOR_1P D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)         // �{�[�h�J���[1p
#define COLOR_2P D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f)         // �{�[�h�J���[2p
#define COLOR_3P D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f)         // �{�[�h�J���[3p
#define COLOR_4P D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f)         // �{�[�h�J���[4p

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//=============================
// �R���X�g���N�^
//=============================
CFlagRaicingGamePolygon::CFlagRaicingGamePolygon()
{
	// �ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ���W
	m_nPlayerNum = 0;                     // �v���C���[�ԍ�
	ZeroMemory(&m_apScoreNumber, sizeof(m_apScoreNumber));   // �X�R�A�̐����|���S��
	m_pBack = NULL;                                          // �w�i
}

//=============================
// �f�X�g���N�^
//=============================
CFlagRaicingGamePolygon::~CFlagRaicingGamePolygon()
{
}

//=============================
// �N���G�C�g
//=============================
CFlagRaicingGamePolygon * CFlagRaicingGamePolygon::Create(int nPlayerNum, D3DXVECTOR3 pos)
{
	// �������̊m��
	CFlagRaicingGamePolygon *pPolygon = new CFlagRaicingGamePolygon;

	// �v���C���|�ԍ�
	pPolygon->m_nPlayerNum = nPlayerNum;
	// ���W
	pPolygon->m_pos = pos;
	// ������
	pPolygon->Init();

	return pPolygon;
}

//=============================
// ����������
//=============================
HRESULT CFlagRaicingGamePolygon::Init(void)
{
	// �w�i�̐���
	m_pBack = CPolygon::Create(m_pos, SIZE_BACK, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�w�i�̃e�N�X�`���ݒ�
	m_pBack->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_POINT_BACK));

	// �X�R�A�̐���
	CreateScore();

	switch (m_nPlayerNum)
	{
	case 0:
		m_pBack->SetColor(COLOR_1P);
		break;
	case 1:
		m_pBack->SetColor(COLOR_2P);
		break;
	case 2:
		m_pBack->SetColor(COLOR_3P);
		break;
	case 3:
		m_pBack->SetColor(COLOR_4P);
		break;
	default:
		break;
	}

	SetPriority(CScene::OBJTYPE_UI);

	return S_OK;
}

//=============================
// �I������
//=============================
void CFlagRaicingGamePolygon::Uninit(void)
{
	// �w�i�̉��
	if (m_pBack != NULL)
	{
		//�I������
		m_pBack->Uninit();

		//�������폜
		delete m_pBack;

		//�������N���A
		m_pBack = NULL;
	}

	// �X�R�A�̉��
	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		if (m_apScoreNumber[nCntDigit] != NULL)
		{
			//�I������
			m_apScoreNumber[nCntDigit]->Uninit();

			//�������폜
			delete m_apScoreNumber[nCntDigit];

			//�������N���A
			m_apScoreNumber[nCntDigit] = NULL;
		}
	}

	Release();
}

//=============================
// �X�V����
//=============================
void CFlagRaicingGamePolygon::Update(void)
{
	//�v���C���[�̃|�C���g���擾
	int nScore = CFlagRaicingGame_rule::GetPlayer(m_nPlayerNum)->GetPoint();

	//�擾�������l���i���o�[�N���X�֐ݒ�
	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		m_apScoreNumber[nCntDigit]->SetNumber((int)((nScore % (int)(powf(10.0f, (POINT_MAX_DIGIT - nCntDigit)))) / (float)(powf(10, (POINT_MAX_DIGIT - nCntDigit - 1)))));
	}
}

//=============================
// �`�揈��
//=============================
void CFlagRaicingGamePolygon::Draw(void)
{
	// �w�i�`��
	if (m_pBack != NULL)
	{
		m_pBack->Draw();
	}

	// �X�R�A�̕`��
	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		if (m_apScoreNumber[nCntDigit] != NULL)
		{
			m_apScoreNumber[nCntDigit]->Draw();
		}
	}
}

//=============================
// �X�R�A�|���S���̐���
//=============================
void CFlagRaicingGamePolygon::CreateScore(void)
{
	float posX = 0 - (SCORE_SPACE * (POINT_MAX_DIGIT - 1)) / 2;
	int nScore = CFlagRaicingGame_rule::GetPlayer(m_nPlayerNum)->GetPoint();

	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		m_apScoreNumber[nCntDigit] = CNumber::Create(
			0, 
			D3DXVECTOR3(m_pos.x + posX, SCORE_POS_Y, 0.0f), 
			SIZE_SCORE, 
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		posX += SCORE_SPACE;

		m_apScoreNumber[nCntDigit]->SetNumber((int)((nScore % (int)(powf(10.0f, (POINT_MAX_DIGIT - nCntDigit)))) / (float)(powf(10, (POINT_MAX_DIGIT - nCntDigit - 1)))));
	}
}
