////////////////////////////////////////////////////
//
//    ���U���g�N���X�̏���[resultboard.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "resultboard.h"
#include "polygon.h"
#include "resource_texture.h"
#include "result.h"
#include "number.h"

//**********************************
// �}�N����`
//**********************************
#define SIZE D3DXVECTOR3(320.0f/2,720.0f/2,0.0f)           // �{�[�h�T�C�Y
#define COLOR_1P D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)         // �{�[�h�J���[1p
#define COLOR_2P D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f)         // �{�[�h�J���[2p
#define COLOR_3P D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f)         // �{�[�h�J���[3p
#define COLOR_4P D3DXCOLOR(1.5f, 1.5f, 0.5f, 1.0f)         // �{�[�h�J���[4p

#define PLAYER_NUMBER_POS_Y 100.0f                       // �v���C���[�i���o�[Y���W
#define SIZE_PLAYER_NUMBER D3DXVECTOR3(80.0f,70.0f,0.0f) // �v���C���[�i���o�[�T�C�Y

#define SIZE_GAME_ICON D3DXVECTOR3(40.0f,40.0f,0.0f) // �~�j�Q�[���A�C�R���̃T�C�Y
#define GAME_ICON_POS_X -78    // �~�j�Q�[���A�C�R����X���W
#define GAME_ICON_POS_Y 230.0f // �~�j�Q�[���A�C�R����Y���W
#define GAME_ICON_SPACE 120.0f  // �~�j�Q�[���A�C�R���̊Ԋu

#define SIZE_GAME_RANK D3DXVECTOR3(60.0f,60.0f,0.0f) // ���ʃ|���S���̃T�C�Y
#define RANK_POS_X 50                                // ���ʃ|���S��X���W
#define RANK_TEX_ANIM_MAX_X 4  // ���ʃe�N�X�`��������*��
#define RANK_TEX_ANIM_MAX_Y 4  // ���ʃe�N�X�`��������*�c

#define SIZE_SCORE D3DXVECTOR3 (45.0f ,45.0f ,0.0f ) // �X�R�A�̃T�C�Y
#define SCORE_POS_Y 620.0f                           // �X�R�AY���W
#define SCORE_SPACE 90.0f                           // �X�R�A�e���̊Ԋu

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//=============================
// �R���X�g���N�^
//=============================
CResultBoard::CResultBoard():CScene(OBJTYPE_UI)
{
	// �ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);  // ���W
	m_nPlayerNum = 0;                     // �v���C���[�ԍ�
	ZeroMemory(&m_apScoreNumber, sizeof(m_apScoreNumber));   // �X�R�A�̐����|���S��
	m_pBack = NULL;                                          // �w�i
	m_pPlayerNumPolygon = NULL;                              // �v���C���[�ԍ��|���S��
	ZeroMemory(&m_apMinigameIcon, sizeof(m_apMinigameIcon)); // �~�j�Q�[���̃A�C�R��
}

//=============================
// �f�X�g���N�^
//=============================
CResultBoard::~CResultBoard()
{
}

//=============================
// �N���G�C�g
//=============================
CResultBoard * CResultBoard::Create(int nPlayerNum, D3DXVECTOR3 pos)
{
	// �������̊m��
	CResultBoard *pResult = new CResultBoard;

	// �v���C���|�ԍ�
	pResult->m_nPlayerNum = nPlayerNum;
	// ���W
	pResult->m_pos = pos;
	// ������
	pResult->Init();

	return pResult;
}

//=============================
// ����������
//=============================
HRESULT CResultBoard::Init(void)
{
	// �w�i�̐���
	m_pBack = CPolygon::Create(m_pos, SIZE, ReturnBackColor());
	m_pBack->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_RESULTBOARD_BACK));

	// �v���C���[�ԍ��̐���
	CreatePlayerNumber();

	// �~�j�Q�[���A�C�R���̐��G�t
	CreateGameIcon();

	// �~�j�Q�[�����ʂ̐���
	CreateGameRank();

	// �X�R�A�̐���
	CreateScore();
	
	return S_OK;
}

//=============================
// �I������
//=============================
void CResultBoard::Uninit(void)
{
	// �w�i�̉��
	if (m_pBack != NULL)
	{
		m_pBack->Uninit();
		delete m_pBack;
		m_pBack = NULL;
	}
	// �v���C���[�i���o�[�̉��
	if (m_pPlayerNumPolygon != NULL)
	{
		m_pPlayerNumPolygon->Uninit();
		delete m_pPlayerNumPolygon;
		m_pPlayerNumPolygon = NULL;
	}

	for (int nCntGame = 0; nCntGame < CRuleManager::RULE_MAX; nCntGame++)
	{
		// �~�j�Q�[���A�C�R���̉��
		if (m_apMinigameIcon[nCntGame] != NULL)
		{
			m_apMinigameIcon[nCntGame]->Uninit();
			delete m_apMinigameIcon[nCntGame];
			m_apMinigameIcon[nCntGame] = NULL;
		}

		// �~�j�Q�[�����ʂ̉��
		if (m_apMinigameRank[nCntGame] != NULL)
		{
			m_apMinigameRank[nCntGame]->Uninit();
			delete m_apMinigameRank[nCntGame];
			m_apMinigameRank[nCntGame] = NULL;
		}
	}

	// �X�R�A�̉��
	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		if (m_apScoreNumber[nCntDigit] != NULL)
		{
			m_apScoreNumber[nCntDigit]->Uninit();
			delete m_apScoreNumber[nCntDigit];
			m_apScoreNumber[nCntDigit] = NULL;
		}
	}

	// �J������
	Release();
}


//=============================
// �X�V����
//=============================
void CResultBoard::Update(void)
{
}

//=============================
// �`�揈��
//=============================
void CResultBoard::Draw(void)
{
	// �w�i�`��
	if (m_pBack != NULL)
	{
		m_pBack->Draw();
	}

	// �v���C���[�i���o�[�̕`��
	if (m_pPlayerNumPolygon != NULL)
	{
		m_pPlayerNumPolygon->Draw();
	}

	for (int nCntGame = 0; nCntGame < CRuleManager::RULE_MAX; nCntGame++)
	{
		// �~�j�Q�[���A�C�R���̕`��
		if (m_apMinigameIcon[nCntGame] != NULL)
		{
			m_apMinigameIcon[nCntGame]->Draw();
		}

		// �~�j�Q�[�����ʂ̕`��
		if (m_apMinigameRank[nCntGame] != NULL)
		{
			m_apMinigameRank[nCntGame]->Draw();
		}
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
// �v���C���[�i���o�[�ɉ������J���[
//=============================
D3DXCOLOR CResultBoard::ReturnBackColor(void)
{
	switch (m_nPlayerNum)
	{
	case 0:

		return COLOR_1P;
		break;
	case 1:
		
		return COLOR_2P;
		break;
	case 2:
		
		return COLOR_3P;
		break;
	case 3:

		return COLOR_4P;
		break;
	default:
		return D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		break;
	}
	
}

//=============================
// �v���C���[�ԍ��̐���
//=============================
void CResultBoard::CreatePlayerNumber(void)
{
	// �v���C���[�i���o�[�̐���
	m_pPlayerNumPolygon = CPolygon::Create(D3DXVECTOR3(m_pos.x, PLAYER_NUMBER_POS_Y, 0.0f), SIZE_PLAYER_NUMBER);
	// �e�N�X�`���̐ݒ�
	switch (m_nPlayerNum)
	{
	case 0:
		m_pPlayerNumPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_1P));
		break;
	case 1:
		m_pPlayerNumPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_2P));
		break;
	case 2:
		m_pPlayerNumPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_3P));
		break;
	case 3:
		m_pPlayerNumPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_4P));
		break;
	default:
		break;
	}
}

//=============================
// �~�j�Q�[���A�C�R���̐���
//=============================
void CResultBoard::CreateGameIcon(void)
{
	// �A�C�R���̐���
	for (int nCntGame = 0; nCntGame < CRuleManager::RULE_MAX; nCntGame++)
	{
		m_apMinigameIcon[nCntGame] = CPolygon::Create(D3DXVECTOR3(m_pos.x + GAME_ICON_POS_X, GAME_ICON_POS_Y + (GAME_ICON_SPACE*nCntGame),0.0f) , SIZE_GAME_ICON);
	}

	// �e�N�X�`���̊��蓖��
	m_apMinigameIcon[CRuleManager::RULE_FLAG_RACING]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_ICON_FLAGRACING));
	m_apMinigameIcon[CRuleManager::RULE_FLY]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_ICON_FLY));
	m_apMinigameIcon[CRuleManager::RULE_REMENBER]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_ICON_REMENBER));
}

//=============================
// �Q�[�����ʃ|���S���̐���
//=============================
void CResultBoard::CreateGameRank(void)
{
	// �A�C�R���̐���
	for (int nCntGame = 0; nCntGame < CRuleManager::RULE_MAX; nCntGame++)
	{
		m_apMinigameRank[nCntGame] = CPolygon::Create(D3DXVECTOR3(m_pos.x + RANK_POS_X, GAME_ICON_POS_Y + (GAME_ICON_SPACE*nCntGame), 0.0f), SIZE_GAME_RANK);
		m_apMinigameRank[nCntGame]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_RANK));
		
		int nRank = CResult::GetResultPoint(m_nPlayerNum).nMiniGameRank[nCntGame];
		// UV�̐ݒ�
		D3DXVECTOR2 uv[NUM_VERTEX];
		float fu = 1.0f / RANK_TEX_ANIM_MAX_X;
		float fv = 1.0f / RANK_TEX_ANIM_MAX_X;

		uv[0] = D3DXVECTOR2(fu*0.0f     , fv*nRank);
		uv[1] = D3DXVECTOR2(fu*0.0f + fu, fv*nRank);
		uv[2] = D3DXVECTOR2(fu*0.0f     , fv*nRank + fv);
		uv[3] = D3DXVECTOR2(fu*0.0f + fu, fv*nRank + fv);

		// UV���W�Z�b�g
		m_apMinigameRank[nCntGame]->SetTextureUV(uv);
	}
}

//=============================
// �X�R�A�|���S���̐���
//=============================
void CResultBoard::CreateScore(void)
{
	float posX = 0 - (SCORE_SPACE*(POINT_MAX_DIGIT - 1)) / 2;
	int nScore = nScore = CResult::GetResultPoint(m_nPlayerNum).nPoint;

	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		m_apScoreNumber[nCntDigit] = CNumber::Create(0, D3DXVECTOR3(m_pos.x + posX, SCORE_POS_Y, 0.0f), SIZE_SCORE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		posX += SCORE_SPACE;

		m_apScoreNumber[nCntDigit]->SetNumber((int)((nScore % (int)(powf(10.0f, (POINT_MAX_DIGIT - nCntDigit)))) / (float)(powf(10, (POINT_MAX_DIGIT - nCntDigit - 1)))));
	}
}
