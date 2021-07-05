//======================================================
//
//	���グ�Q�[���̏���[flag_raicing_game_rule.cpp]
//	Author : ���� �r�H
//
//======================================================
//======================================================
//	�C���N���[�h�t�@�C��
//======================================================
#include "flag_raicing_game_rule.h"
#include "manager.h"
#include "count_selection.h"
#include "player.h"
#include "captain.h"
#include "flipper.h"
#include "camera_tps.h"
#include "mini_result.h"

//======================================================
//	�ÓI�����o�ϐ��錾������
//======================================================
CFlagRaicingGame_rule::TRUN CFlagRaicingGame_rule::m_eLoop
	= CFlagRaicingGame_rule::CAPTAIN_TRUN;	// �L���v�e���̃^�[�����v���C���[�̃^�[�����𔻕ʂ���ϐ�

//======================================================
//	�}�N����`
//======================================================
#define PLAYER_SPACE (150.0f)	// �v���C���[�ʒu�̊Ԋu
#define TIME_SET (180)			// �������Ԃ̐ݒ�
#define TRUN_SET (20)			// �^�[�����̐ݒ�
#define ADD_POINT_NUM (1)		// �|�C���g���v�l�̐ݒ�

//======================================================
//	�R���X�g���N�^
//======================================================
CFlagRaicingGame_rule::CFlagRaicingGame_rule()
{
	// �ϐ��̏�����
	ZeroMemory(&m_pPlayer, sizeof(m_pPlayer));
	m_pCaptain = NULL;
	m_nCntInputPlayer = 0;
	m_nCntTime = 0;
	m_nPoint = 0;
	m_nTarn = 0;
	m_bPlay = true;
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
	m_bPlay = true;

	//�J�����̐���
	CGame::SetCamera(CTpsCamera::Create());

	// �v���C���[�̐l���擾
	int nPlayerNum = CCountSelect::GetPlayerNum();
	// �v���C���[�̐l�����v���C���[����
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		float posX = 0 + ((float)(nCntPlayer)*PLAYER_SPACE) / 2;// �ʒu�̒���
		// �v���C���[�̐���
		m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(posX, -50.0f, 30.0f), nCntPlayer);
	}
	// �L���v�e���̐���
	m_pCaptain = CCaptain::Create(D3DXVECTOR3(0.0f, -35.0f, -30.0f));

	return S_OK;
}

//======================================================
//	�I������
//======================================================
void CFlagRaicingGame_rule::Uninit(void)
{

}

//======================================================
//	�X�V����
//======================================================
void CFlagRaicingGame_rule::Update(void)
{
	// �v���C���[��K�v���ȊO�����Ȃ�����悤�ɂ��鏈��
	if (m_bPlay)
	{
		// ���Ԍv�Z����
		m_nCntTime++;
		// ���ʏ���
		FlagJudge();

		// ���Ԍo�߂Ŏ��̓���ɓ���
		if (m_nCntTime == TIME_SET)
		{
			m_nTarn++;					//�^�[����i�߂�
			SetGameLoop(CAPTAIN_TRUN);	//�L���v�e���̃^�[���ɕύX
			m_nCntTime = 0;				//�^�C���̏�����
			FlagPoint();				//�|�C���g�ǉ�
		}
		// ����̃^�[��������������Q�[�����I��������
		if (m_nTarn == TRUN_SET)
		{
			JudgeRank();
		}
	}
}

//======================================================
//	�`�揈��
//======================================================
void CFlagRaicingGame_rule::Draw(void)
{

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
	}
	// ���̃��U���g�\��
	CMiniResult::Create();
	// �v���C���[�𓮂��Ȃ�����
	m_bPlay = false;
}