//======================================================
//
//	���グ�Q�[���̏���[flag_raicing_game_rule.cpp]
//	Author : ���� �r�H
//
//======================================================
//======================================================
//	�C���N���[�h�t�@�C��
//======================================================
#include <time.h>
#include "flag_raicing_game_rule.h"
#include "flag_raicing_game_camera.h"
#include "manager.h"
#include "count_selection.h"
#include "player.h"
#include "captain.h"
#include "flipper.h"
#include "camera_tps.h"
#include "mini_result.h"
#include "timelimit.h"
#include "blind.h"
#include "bg.h"
#include "billboard.h"
#include "iceberg.h"
#include "passingpenguin.h"
#include "stage.h"
#include "sea.h"
#include "result.h"
#include "polygon.h"
#include "flag_raicing_game_polygon.h"

//======================================================
//	�ÓI�����o�ϐ��錾������
//======================================================
CFlagRaicingGame_rule::TRUN CFlagRaicingGame_rule::m_eLoop
	= CFlagRaicingGame_rule::CAPTAIN_TRUN;	// �L���v�e���̃^�[�����v���C���[�̃^�[�����𔻕ʂ���ϐ�
CBlind *CFlagRaicingGame_rule::m_pBlind = NULL;	//�u���C���h�N���X�̃|�C���^�ϐ�
CPlayer *CFlagRaicingGame_rule::m_pPlayer[MAX_PLAYER_NUM] = {};

//======================================================
//	�}�N����`
//======================================================
#define PLAYER_SPACE 110.0f				// �v���C���[�ʒu�̊Ԋu
#define POINT_UI_SPACE 310.0f			// �_���̈ʒu�Ԋu
#define TIME_SET 180					// �������Ԃ̐ݒ�
#define TRUN_SET 40						// �^�[���̐������Ԃ̐ݒ�
#define ADD_POINT_NUM 1					// �|�C���g���v�l�̐ݒ�

#define FLAG_PLAYER_POS_Y_NUM -100.0f	// �v���C���[��Y���W
#define FLAG_PLAYER_POS_Z_NUM -50.0f	// �v���C���[��Z���W

#define POINT_UI_POS_Y_NUM 630.0f		// �_����Y���W
#define POINT_UI_POS_Z_NUM 5.0f			// �_����Z���W
#define POINT_UI_SIZE_X_NUM 60.0f		// �_��UI�����̑傫��
#define POINT_UI_SIZE_Y_NUM 30.0f		// �_��UI�c���̑傫��

#define FLAG_CAPTAIN_POS_X_NUM 0.0f		// �L���v�e����X���W
#define FLAG_CAPTAIN_POS_Y_NUM -98.0f	// �L���v�e����Y���W
#define FLAG_CAPTAIN_POS_Z_NUM -220.0f	// �L���v�e����Z���W
#define PASSING_PENGUIN_POS D3DXVECTOR3(400.0f, -90.0f, -100.0f)
#define RAND_FLAG rand() % 180 + 50		// �t���b�O�̏グ��Ԋu�̐ݒ�

//======================================================
//	�R���X�g���N�^
//======================================================
CFlagRaicingGame_rule::CFlagRaicingGame_rule()
{
	// �ϐ��̏�����
	ZeroMemory(&m_PlayerPoint, sizeof(m_PlayerPoint));
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_pCaptain = NULL;
	m_nCntInputPlayer = 0;
	m_nCntTime = 0;
	m_nTarn = 0;
	m_nRandTime = 0;
	m_pTimeLimit = NULL;
	m_bPlay = true;
	m_pBlind = NULL;
	m_pPassingPenguin = NULL;
}

//======================================================
//	�f�X�g���N�^
//======================================================
CFlagRaicingGame_rule::~CFlagRaicingGame_rule()
{

}

//======================================================
//	��������
//======================================================
CFlagRaicingGame_rule * CFlagRaicingGame_rule::Create(void)
{
	CFlagRaicingGame_rule *pFlagRaicingGameRule
		= new CFlagRaicingGame_rule;

	if (pFlagRaicingGameRule)
	{
		pFlagRaicingGameRule->Init();
	}

	return pFlagRaicingGameRule;
}

//======================================================
//	����������
//======================================================
HRESULT CFlagRaicingGame_rule::Init(void)
{
	CIceberg::Create(D3DXVECTOR3(0.0f, -100.0f, -1200.0f), CIceberg::ICEBERG_TYPE(rand() % CIceberg::ICEBERG_MAX));
	// �w�i�̐���
	CBg::Create();

	m_bPlay = true;
	m_nRandTime = TIME_SET;
	//�J�����̐���
	CManager::SetCamera(CFlagRaicingGameCamera::Create());

	// �v���C���[�̐l���擾
	int nPlayerNum = CCountSelect::GetPlayerNum();
	float posX = 0 + ((float)(nPlayerNum - 1) * PLAYER_SPACE) / 2;// �v���C���[�ʒu�̒���
	float posXUI = SCREEN_WIDTH / 2 + ((float)(nPlayerNum - 1) * POINT_UI_SPACE) / 2;// �_���̈ʒu����

	// �v���C���[�̐l�����v���C���[����
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		// �v���C���[�̐���
		m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(posX, FLAG_PLAYER_POS_Y_NUM, FLAG_PLAYER_POS_Z_NUM), nCntPlayer);
		// �|�C���gUI�̐���
		m_PlayerPoint.bPoint[nCntPlayer] = CFlagRaicingGamePolygon::Create(
			nCntPlayer,D3DXVECTOR3(posXUI, POINT_UI_POS_Y_NUM, 0.0f));

		posX -= PLAYER_SPACE;
		posXUI -= POINT_UI_SPACE;
	}
	// �L���v�e���̐���
	m_pCaptain = CCaptain::Create(D3DXVECTOR3(FLAG_CAPTAIN_POS_X_NUM, FLAG_CAPTAIN_POS_Y_NUM, FLAG_CAPTAIN_POS_Z_NUM));
	
	// �������Ԃ̐���
	m_pTimeLimit = CTimeLimit::Create(TRUN_SET);
	
	//�u���C���h�̐���
	m_pBlind = CBlind::Create(m_pTimeLimit->GetTimeLimit(), (TRUN_SET / 2));

	//�ʉ߃y���M���̐���
	m_pPassingPenguin = CPassingPenguin::Create(PASSING_PENGUIN_POS);

	// �X�e�[�W�̐���
	CStage::Create(D3DXVECTOR3(FLAG_CAPTAIN_POS_X_NUM, FLAG_PLAYER_POS_Y_NUM, FLAG_CAPTAIN_POS_Z_NUM), CStage::STAGE_TYPE_LARGE);

	// �C�̐���
	CSea::Create(D3DXVECTOR3(0.0f, FLAG_PLAYER_POS_Y_NUM -14.0f, 0.0f), 0.001f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, FLAG_PLAYER_POS_Y_NUM -12.0f, 0.0f), 0.0025f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, FLAG_PLAYER_POS_Y_NUM -10.0f, 0.0f), 0.004f, CSea::TYPE_NORMAL);

	return S_OK;
}

//======================================================
//	�I������
//======================================================
void CFlagRaicingGame_rule::Uninit(void)
{
	int nPlayerNum = CCountSelect::GetPlayerNum();

	for (int nCnt = 0; nCnt < nPlayerNum; nCnt++)
	{
		// �e�N�X�`���N���X�̏I������
		if (m_PlayerPoint.bPoint[nCnt] != NULL)
		{
			//�r���{�[�h�̏I��
			m_PlayerPoint.bPoint[nCnt]->Uninit();

			//�������̍폜
			delete m_PlayerPoint.bPoint[nCnt];

			//�������̃N���A
			m_PlayerPoint.bPoint[nCnt] = NULL;
		}
	}
}

//======================================================
//	�X�V����
//======================================================
void CFlagRaicingGame_rule::Update(void)
{
	// �v���C���[�̐l���擾
	int nPlayerNum = CCountSelect::GetPlayerNum();
	bool btest = true;
	if (btest == true)
	{
		// �v���C���[��K�v���ȊO�����Ȃ�����悤�ɂ��鏈��
		if (m_bPlay)
		{
			// �����̏�����
			srand((unsigned int)time(NULL));
			for (int nCnt = 0; nCnt < nPlayerNum; nCnt++)
			{
				// �|�C���g�ǉ�����
				m_PlayerPoint.bPoint[nCnt]->Update();
			}
			// ���Ԍv�Z����
			++m_nCntTime;
			// ���ʏ���
			FlagJudge();

			// ���Ԍo�߂Ŏ��̓���ɓ���
			if (m_nCntTime == m_nRandTime)
			{
				m_nRandTime = RAND_FLAG;	// �����_���Ŋ��̏グ��^�C�~���O��ݒ�
				m_nTarn++;					// �^�[����i�߂�
				SetGameLoop(CAPTAIN_TRUN);	// �L���v�e���̃^�[���ɕύX
				m_nCntTime = 0;				// �^�C���̏�����
				FlagPoint();				// �|�C���g�ǉ�
			}

			//�������Ԃ��擾
			int nTimeLimit = m_pTimeLimit->GetTimeLimit();

			// ����̃^�[��������������Q�[�����I��������
			// �������Ԃ�0�ȉ��̎�
			if (nTimeLimit <= 0)
			{
				JudgeRank();
			}

			//�u���C���h�Ɍ��݃^�C����^����
			if (m_pBlind)
			{
				m_pBlind->SetTime(nTimeLimit);
			}

			if (nTimeLimit > (TRUN_SET / 2))
			{
				if (nTimeLimit == 35)
				{
					//���֒ʉ߂���悤�ݒ�
					m_pPassingPenguin->SetMoveDirection(CPassingPenguin::MOVE_DIRECTION_LEFT);
				}
				else if (nTimeLimit == 25)
				{
					//�E�֒ʉ߂���悤�ɐݒ�
					m_pPassingPenguin->SetMoveDirection(CPassingPenguin::MOVE_DIRECTION_RIGHT);
				}
			}
		}

	}
}

//======================================================
//	�`�揈��
//======================================================
void CFlagRaicingGame_rule::Draw(void)
{
	int nPlayerNum = CCountSelect::GetPlayerNum();

	for (int nCnt = 0; nCnt < nPlayerNum; nCnt++)
	{
		m_PlayerPoint.bPoint[nCnt]->Draw();
	}
}

//======================================================
//	�E�������̔��ʏ���
//======================================================
void CFlagRaicingGame_rule::FlagJudge(void)
{
	// �v���C���[��
	int nPlayerNum = CCountSelect::GetPlayerNum();
	CFlipper*pCaptainFlipper;
	CFlipper*pPlayerFlipper;

	// �L���v�e���̊�����
	pCaptainFlipper = m_pCaptain->GetFlipper();

	// �v���C���[�̐�����������
	for (int nCount = 0; nCount < nPlayerNum; nCount++)
	{
		// �v���C���[�̊��̔���
		pPlayerFlipper = m_pPlayer[nCount]->GetFlipper();

		// �����������������ꍇ
		if (pPlayerFlipper->GetState(CFlipper::FLIPPER_TYPE_LEFT) == pCaptainFlipper->GetState(CFlipper::FLIPPER_TYPE_LEFT)
			&& pPlayerFlipper->GetState(CFlipper::FLIPPER_TYPE_RIGHT) == pCaptainFlipper->GetState(CFlipper::FLIPPER_TYPE_RIGHT))
		{
			// �ŏ��ɓ��������ɂȂ����v���C���[��T��
			if(PlayerFlagJudge(m_pPlayer[nCount]))
			{
				m_playerVector.push_back(m_pPlayer[nCount]);
			}
		}
	}
}

//======================================================
//	�|�C���g���Z����
//======================================================
void CFlagRaicingGame_rule::FlagPoint(void)
{
	if (m_playerVector.size() != 0)
	{
		m_playerVector[0]->AddPoint(ADD_POINT_NUM);		// �|�C���g�ǉ�����
		m_playerVector.clear();							// �v���C���[���̏�����
	}
}

//======================================================
//	vector�̒��g�̔�r
//======================================================
bool CFlagRaicingGame_rule::PlayerFlagJudge(CPlayer *player)
{
	for (int nCount = 0; nCount < (signed)m_playerVector.size(); nCount++)
	{
		if (m_playerVector[nCount] == player)
		{
			return false;
		}
	}
	return true;
}

//======================================================
//	���ʂ̔���
//======================================================
void CFlagRaicingGame_rule::JudgeRank(void)
{
	/* ���l�������Ƀ\�[�g */
	for (int nCnt = 0; nCnt < CCountSelect::GetPlayerNum(); ++nCnt)
	{
		for (int nCntSort = nCnt + 1; nCntSort<CCountSelect::GetPlayerNum(); ++nCntSort)
		{
			if (m_pPlayer[nCnt]->GetPoint() < m_pPlayer[nCntSort]->GetPoint())
			{
				CPlayer*pPlayer;
				pPlayer = m_pPlayer[nCnt];
				m_pPlayer[nCnt] = m_pPlayer[nCntSort];
				m_pPlayer[nCntSort] = pPlayer;
			}
		}
	}
	// �v���C���[����������
	for (int nCnt = 0; nCnt < CCountSelect::GetPlayerNum(); ++nCnt)
	{
		// ���Ԃ����ւ��ă��U���g�ɕ\��������
		m_pPlayer[nCnt]->SetRank(nCnt);
		m_pPlayer[nCnt]->SetMoveFlag(false);

		// �~�j�Q�[���ɏ��ʂ𑗂�
		CResult::SetMiniGameRank(CRuleManager::RULE_FLAG_RACING, m_pPlayer[nCnt]->GetPlayerNumber(), m_pPlayer[nCnt]->GetRank());
	}
	// ���̃��U���g�\��
	CMiniResult::Create();
	// �v���C���[�𓮂��Ȃ�����
	m_bPlay = false;
}