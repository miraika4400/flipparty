////////////////////////////////////////////////////
//
//    ���U���g�N���X�̏���[result.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//=============================
// �C���N���[�h
//=============================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "camera_base.h"
#include "player.h"
#include "bg.h"
#include "count_selection.h"
#include "tears_manager.h"
#include "rank_ui.h"
#include "resultboard.h"
#include "sound.h"
#include "resource_texture.h"
#include "stage.h"
#include "sea.h"
#include "iceberg.h"

//**********************************
// �}�N����`
//**********************************
#define PLAYER_SPACE 150.0f //�@�v���C���[�ʒu�̊Ԋu
#define PLAYER_POS_Z 100.0f // �v���C���[��Z�ʒu
#define PLAYER_FALL_COUNT 300 // �v���C���[��������J�E���g��
#define RANK_UI_HEGHT -50  // �����L���O��UI�v���C���[����̈ʒu
#define RESULT_BOARD_SPACE 320.0f

#define LOGO_POS D3DXVECTOR3(SCREEN_WIDTH/2, 100.0f, 0.0f)
#define LOGO_SIZE D3DXVECTOR3(300.0f,75.0f,0.0f)
#define OBJ_BASE_POS_Y 2000.0f

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
CResult::ResultPoint CResult::m_resultPoint[MAX_PLAYER_NUM] = {};

//=============================
// �R���X�g���N�^
//=============================
CResult::CResult()
{
	ZeroMemory(&m_apPlayer, sizeof(m_apPlayer));
	m_nCntFallTime = 0;
	m_nActionRank = 0;
	m_bShow = true;
	m_bBoard = false;
	ZeroMemory(&m_apRankUI, sizeof(m_apRankUI));
}

//=============================
// �f�X�g���N�^
//=============================
CResult::~CResult()
{
}

//=============================
// �N���G�C�g
//=============================
CResult * CResult::Create(void)
{
	// �������̊m��
	CResult *pResult = new CResult;
	// ������
	pResult->Init();
	return pResult;
}

//=============================
// ����������
//=============================
HRESULT CResult::Init(void)
{
	//// �J�����N���X�̐���
	CManager::SetCamera(CCamera::Create());
	D3DXVECTOR3 cameraPos = CManager::GetCamera()->GetPos();
	cameraPos.y = OBJ_BASE_POS_Y + 100.0f;
	CManager::GetCamera()->SetPosV(cameraPos);

	// �w�i�̐���
	CBg::Create();

	// �C�̐���
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 24.0f, 0.0f), 0.001f , CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 22.0f, 0.0f), 0.0025f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 20.0f, 0.0f), 0.004f , CSea::TYPE_NORMAL);

	// �X�R�̐���
	CIceberg::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 50.0f, -900.0f), CIceberg::ICEBERG_TYPE(rand() % CIceberg::ICEBERG_MAX));

	// �v���C���[���̎擾
	int nPlayNum = CCountSelect::GetPlayerNum();

	// �v���C���[�̐���
	// �����ʒuX���̒���
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		m_apPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(posX, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT, PLAYER_POS_Z), nCntPlayer);

		// �J�����̕����ɑ̂�������
		D3DXVECTOR3 cemeraPos = CManager::GetCamera()->GetPos();
		float fRotY = atan2f(posX - cemeraPos.x, PLAYER_POS_Z - cemeraPos.z);

		// �p�x�̒���
		m_apPlayer[nCntPlayer]->SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));
		
		// ����t���Ofalse
		m_apPlayer[nCntPlayer]->SetMoveFlag(false);

		CStage::Create(D3DXVECTOR3(posX, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT, PLAYER_POS_Z), CStage::STAGE_TYPE_NORMAL);
		posX -= PLAYER_SPACE;
	}

	// �J�E���g�̏�����
	m_nCntFallTime = 0;

	// �A�N�V�������N�������ʂ̏�����(�ŉ���)
	m_nActionRank = nPlayNum - 1;

	// �_���v�Z
	CalculationRank();

	// ���S�̐���
	CScene2d*pLogo = CScene2d::Create();
	pLogo->SetPriority(OBJTYPE_UI);// �v���C�I���e�B
	pLogo->SetPos(LOGO_POS);       // ���W
	pLogo->SetSize(LOGO_SIZE);     // �T�C�Y
	pLogo->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_RESULT_LOGO));// �e�N�X�`��

	// �{�[�h�t���O
	m_bBoard = false;
	return S_OK;
}

//=============================
// �I������
//=============================
void CResult::Uninit(void)
{
	// �J�����N���X�̉������
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		CManager::SetCamera(NULL);
		pCamera = NULL;
	}

	// �W�v�|�C���g�����������Ă���
	ResetResultPoint();

	// �J������
	Release();
}


//=============================
// �X�V����
//=============================
void CResult::Update(void)
{
	// �J�����N���X�̍X�Vv����
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Update();
	}

	if (m_bShow)
	{// ���ʔ��\��
		
		// ���ʔ��\���Ƀv���C���[�̃��[�V������ς���
		ChagePlayerMotion();
	}
	else
	{// ���ʔ��\�I����
		if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
			CManager::GetMouse()->GetMouseTrigger(0) ||
			CManager::GetJoypad()->GetJoystickTrigger(3, 0))
		{
			if (!m_bBoard)
			{// ���U���g�{�[�h�̐���
				
				// �v���C���[���̎擾
				int nPlayerNum = CCountSelect::GetPlayerNum();

				D3DXVECTOR3 boardPos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
				boardPos.x = boardPos.x - (RESULT_BOARD_SPACE*(nPlayerNum - 1)) / 2;

				for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
				{
					// ���U���g�{�[�h�̐���
					CResultBoard::Create(nCntPlayer, boardPos);

					boardPos.x += RESULT_BOARD_SPACE;

					if (m_apRankUI[nCntPlayer] != NULL)
					{
						m_apRankUI[nCntPlayer]->Uninit();
						m_apRankUI[nCntPlayer] = NULL;
					}
				}
				m_bBoard = true;
			}
			else
			{// ��ʑJ��
				CManager::GetFade()->SetFade(CManager::MODE_TITLE);
			}
			
			// SE�̍Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_ENTER);

			return;
		}
	}

	// �v���C���[�̈ʒu�̒���
	AdjustPlayerPos();
}

//=============================
// �`�揈��
//=============================
void CResult::Draw(void)
{
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->SetCamera();
	}
}

//=============================
// �v���C���[�̃��[�V������ς���
//=============================
void CResult::ChagePlayerMotion(void)
{

	if (m_nCntFallTime == 0 && m_nActionRank == 1)
	{
		// ��ʔ��\����SE�Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_RESULT_WIN);
	}

	// �J�E���g��i�߂�
	m_nCntFallTime++;

	if (PLAYER_FALL_COUNT <= m_nCntFallTime)
	{// ���̃J�E���g��
	 // �J�E���g�̃��Z�b�g
		
		// �v���C���[���̎擾
		int nPlayNum = CCountSelect::GetPlayerNum();

		for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
		{
			if (m_nActionRank != 1)
			{//3�ʈȉ�
				if (m_apPlayer[nCntPlayer]->GetRank() == m_nActionRank)
				{
					// �R�P�郂�[�V�����̍Đ�
					m_apPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_FALL);
					// �\��̕ύX
					m_apPlayer[nCntPlayer]->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);

					// SE
					CManager::GetSound()->Play(CSound::LABEL_SE_MISS);

					m_nCntFallTime = 0;
				}
			}
			else
			{// 2�ʔ��\���Ɠ����Ɉ�ʂ����\
				if (m_apPlayer[nCntPlayer]->GetRank() == m_nActionRank)
				{
					// �R�P�郂�[�V�����̍Đ�
					m_apPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_FALL);
					// �\��̕ύX
					m_apPlayer[nCntPlayer]->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);

					// SE
					CManager::GetSound()->Play(CSound::LABEL_SE_MISS);
				}
				else if (m_apPlayer[nCntPlayer]->GetRank() == 0)
				{
					// ��ʃ��[�V�����̍Đ�
					m_apPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_MINIRESULT_1);
				}
			}
		}

		m_nActionRank--;
		if (m_nActionRank <= 0)
		{
			m_bShow = false;

			// ���|�C���g���l�����ď��ʂ����Ȃ���
			JudgePlayerRank(true);
		}
		else if (m_nActionRank == 1)
		{
			m_nCntFallTime = 0;
		}
	}
}

//=============================
// �_���E���ʂ̌v�Z
//=============================
void CResult::CalculationRank(void)
{
	// �v���C���[���̎擾
	int nPlayerNum = CCountSelect::GetPlayerNum();

	//////////////////////
	// �����_���̌v�Z

	// �v���C���[���Ń��[�v
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		// ���[�����Ń��[�v
		for (int nCntRule = 0; nCntRule < CRuleManager::RULE_MAX; nCntRule++)
		{

			// �|�C���g�̉��Z
			switch (m_resultPoint[nCntPlayer].nMiniGameRank[nCntRule])
			{
			case 0:
				// ���
				m_resultPoint[nCntPlayer].nPoint += POINT_1ST;
				break;

			case 1:
				// ���
				m_resultPoint[nCntPlayer].nPoint += POINT_2ND;
				break;

			case 2:
				// �O��
				m_resultPoint[nCntPlayer].nPoint += POINT_3RD;
				break;

			case 3:
				// �l��
				m_resultPoint[nCntPlayer].nPoint += POINT_4TH;
				break;

			default:
				break;
			}
		}
	}

	//////////////////////////////////
	// �|�C���g���v���C���[�ɔ��f
	
	// �v���C���[���Ń��[�v
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		// �|�C���g�̔��f
		m_apPlayer[nCntPlayer]->SetPoint(m_resultPoint[nCntPlayer].nPoint);
	}

	// �����_���ł����ʂ𕪂��ď��ʕt��
	JudgePlayerRank(false);
}

//=============================
// ���ʕt��
//=============================
void CResult::JudgePlayerRank(bool bSamePointRank)
{
	// �v���C���[���̎擾
	int nPlayerNum = CCountSelect::GetPlayerNum();

	////////////////////////////////
	// ���ʕt��

	// �|�C���g�̍������Ƀ\�[�g
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		for (int nCntSort = nCntPlayer + 1; nCntSort < nPlayerNum; nCntSort++)
		{
			if (m_apPlayer[nCntPlayer]->GetPoint() < m_apPlayer[nCntSort]->GetPoint())
			{
				CPlayer * pSave = m_apPlayer[nCntPlayer];
				m_apPlayer[nCntPlayer] = m_apPlayer[nCntSort];
				m_apPlayer[nCntSort] = pSave;
			}
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		// �z��̏��Ԃ����̂܂܏��ʂ�
		m_apPlayer[nCntPlayer]->SetRank(nCntPlayer);

		if (bSamePointRank)
		{
			if (nCntPlayer != 0)
			{
				// �|�C���g�������Ȃ瓯�����ʂɂ���
				if (m_apPlayer[nCntPlayer]->GetPoint() == m_apPlayer[nCntPlayer - 1]->GetPoint())
				{
					m_apPlayer[nCntPlayer]->SetRank(m_apPlayer[nCntPlayer - 1]->GetRank());
				}
			}

			D3DXVECTOR3 playerPos = m_apPlayer[nCntPlayer]->GetPos();
			// �����NUI�̐���
			m_apRankUI[nCntPlayer] = CRankUI::Create(D3DXVECTOR3(playerPos.x, playerPos.y + RANK_UI_HEGHT, playerPos.z), m_apPlayer[nCntPlayer]->GetRank());
		}
		else
		{
			if (nCntPlayer != 0)
			{

				// �|�C���g�������Ȃ瓯�����ʂɂ���
				if (m_apPlayer[nCntPlayer]->GetPoint() == m_apPlayer[0]->GetPoint())
				{
					m_apPlayer[nCntPlayer]->SetRank(m_apPlayer[0]->GetRank());
				}
			}
		}
	}
}

//=============================
// �v���C���[�̈ʒu�̒���
//=============================
void CResult::AdjustPlayerPos(void)
{
	// �v���C���[���̎擾
	int nPlayerNum = CCountSelect::GetPlayerNum();
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		if (m_apPlayer[nCntPlayer]->GetMotionActive(CPlayer::MOTION_FALL))
		{// �R�P�郂�[�V�����̎�
			D3DXVECTOR3 playerPos = m_apPlayer[nCntPlayer]->GetPos();
			playerPos.y += ((2000.0f -PLAYER_CENTER_HEIGHT - 20) - playerPos.y)*0.05f;

			m_apPlayer[nCntPlayer]->SetPos(playerPos);
		}
	}

}
