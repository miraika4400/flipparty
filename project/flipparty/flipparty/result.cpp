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

//**********************************
// �}�N����`
//**********************************
#define PLAYER_SPACE 150.0f //�@�v���C���[�ʒu�̊Ԋu
#define PLAYER_POS_Z 100.0f // �v���C���[��Z�ʒu
#define PLAYER_FALL_COUNT 300 // �v���C���[��������J�E���g��
#define RANK_UI_HEGHT -50  // �����L���O��UI�v���C���[����̈ʒu
#define RESULT_BOARD_SPACE 320.0f

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
	//m_pCamera = CGame::GetCamera();

	// �w�i�̐���
	CBg::Create();

	// �v���C���[���̎擾
	int nPlayNum = CCountSelect::GetPlayerNum();

	// �v���C���[�̐���
	// �����ʒuX���̒���
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		m_apPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(posX, 2000.0f - PLAYER_CENTER_HEIGHT, PLAYER_POS_Z), nCntPlayer);

		// �J�����̕����ɑ̂�������
		D3DXVECTOR3 cemeraPos = CManager::GetCamera()->GetPos();
		float fRotY = atan2f(posX - cemeraPos.x, PLAYER_POS_Z - cemeraPos.z);

		// �p�x�̒���
		m_apPlayer[nCntPlayer]->SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));
		
		// ����t���Ofalse
		m_apPlayer[nCntPlayer]->SetMoveFlag(false);

		posX -= PLAYER_SPACE;
	}

	// �J�E���g�̏�����
	m_nCntFallTime = 0;

	// �A�N�V�������N�������ʂ̏�����(�ŉ���)
	m_nActionRank = nPlayNum - 1;

	// �_���v�Z
	CalculationRank();

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
					CResultBoard::Create(nCntPlayer, boardPos);
					boardPos.x += RESULT_BOARD_SPACE;
				}
				m_bBoard = true;
			}
			else
			{// ��ʑJ��
				CManager::GetFade()->SetFade(CManager::MODE_TITLE);
			}

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
	// �J�E���g��i�߂�
	m_nCntFallTime++;
	if (PLAYER_FALL_COUNT <= m_nCntFallTime)
	{// ���̃J�E���g��
	 // �J�E���g�̃��Z�b�g
		m_nCntFallTime = 0;
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
					//// �܂̐���
					//D3DXVECTOR3 headPos;
					//headPos.x = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._41;
					//headPos.y = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._42;
					//headPos.z = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._43 - 10;
					//CTearsManager::Create(headPos);
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
					//// �܂̐���
					//D3DXVECTOR3 headPos;
					//headPos.x = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._41;
					//headPos.y = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._42;
					//headPos.z = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._43 - 10;
					//CTearsManager::Create(headPos);
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
			CRankUI::Create(D3DXVECTOR3(playerPos.x, playerPos.y + RANK_UI_HEGHT, playerPos.z), m_apPlayer[nCntPlayer]->GetRank());
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
			playerPos.y += ((-PLAYER_CENTER_HEIGHT - 20) - playerPos.y)*0.05f;

			m_apPlayer[nCntPlayer]->SetPos(playerPos);
		}
	}

}
