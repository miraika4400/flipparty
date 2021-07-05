////////////////////////////////////////////////////
//
//    �J�����N���X�̏���[camera.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "rule_flygame.h"
#include "count_selection.h"
#include "player_flygame.h"
#include "game.h"
#include "camera_flygame.h"
#include "light.h"
#include "timelimit.h"
#include "camera_tps.h"
#include "mini_result.h"
#include "bg.h"

//******************************
// �}�N����`
//******************************
#define PLAYER_SPACE 150.0f //�@�v���C���[�ʒu�̊Ԋu
#define PLAY_TIME 5         // ��������

//******************************
// �ÓI�����o�ϐ��錾
//******************************

//******************************
// �R���X�g���N�^
//******************************
CRuleFly::CRuleFly()
{
	// �ϐ��̃N���A
	m_pTimeLimit = NULL;
	m_bPlay = true;
}

//******************************
// �f�X�g���N�^
//******************************
CRuleFly::~CRuleFly()
{
}

//******************************
// �N���G�C�g
//******************************
CRuleFly * CRuleFly::Create(void)
{
	CRuleFly * pRuleFly = new CRuleFly;
	pRuleFly->Init();

	return pRuleFly;
}

//******************************
// ����������
//******************************
HRESULT CRuleFly::Init(void)
{
	// �w�i�̐���
	CBg::Create();

	// �J�����N���X�̐���
	CGame::SetCamera(CFlyGameCamera::Create());

	// �v���C���[���̎擾
	int nPlayNum = CCountSelect::GetPlayerNum();
	
	// �v���C���[�̐���
	// �����ʒuX���̒���
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		CFlyGamePlayer::Create(D3DXVECTOR3(posX, 0.0f, 0.0f), nCntPlayer);
		posX -= PLAYER_SPACE;
	}

	// �������Ԃ̐���
	m_pTimeLimit = CTimeLimit::Create(PLAY_TIME);

	// �v���C���t���O�̏�����
	m_bPlay = true;

	return S_OK;
}

//******************************
// ����������
//******************************
void CRuleFly::Uninit(void)
{
}

//******************************
// �X�V����
//******************************
void CRuleFly::Update(void)
{

	// �������Ԃ�0�ȉ��̎�
	if (m_pTimeLimit->GetTimeLimit() <= 0)
	{
		if (m_bPlay)
		{
			// �Q�[�����t���O��false
			m_bPlay = false;

			// ���ʔ���
			JudgeRank();
		}
		else
		{
			// �J�����N���X
			CGame::SetCamera(CFlyGameCamera::Create());
		}
	}
}

//******************************
// �`�揈��
//******************************
void CRuleFly::Draw(void)
{
}

//******************************
// ���ʔ��菈��
//******************************
void CRuleFly::JudgeRank(void)
{
	std::vector<CPlayer*> vectorPlayer; // ���ʕt���p�Ƀv���C���[�����i�[����ϐ� 
	int nPlayerIndex = 0;  // ���̕ϐ��̃|�C���^�����炷�p�ϐ�

	// �v���C���[�I�u�W�F�N�g�̎擾
	CPlayer *pPlayer = (CPlayer *)CScene::GetTop(CScene::OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		// ���ʔ���p�ϐ��ɏ���ۑ�
		vectorPlayer.push_back(pPlayer);
		nPlayerIndex++;

		if (pPlayer->GetMoveFlag())
		{
			// �����s�ɂ���
			pPlayer->SetMoveFlag(false);
		}

		// ���̃v���C���[���ɍX�V
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}

	// �_�u���|�C���^��Y���W�̍������Ƀ\�[�g
	for (int nCntPlayer = 0; nCntPlayer < nPlayerIndex; nCntPlayer++)
	{
		for (int nCntSort = nCntPlayer + 1; nCntSort < nPlayerIndex; nCntSort++)
		{
			if (vectorPlayer[nCntPlayer]->GetPos().y < vectorPlayer[nCntSort]->GetPos().y)
			{
				CPlayer * pSave = vectorPlayer[nCntPlayer];
				vectorPlayer[nCntPlayer] = vectorPlayer[nCntSort];
				vectorPlayer[nCntSort] = pSave;
			}
		}
	}

	// ���ʕt��
	for (int nCntPlayer = 0; nCntPlayer < nPlayerIndex; nCntPlayer++)
	{
		// �z��̏��Ԃ����̂܂܏��ʂ�
		vectorPlayer[nCntPlayer]->SetRank(nCntPlayer);

		// Y���̍��W�������Ȃ瓯�����ʂɂ���
		if (nCntPlayer != 0)
		{
			if (vectorPlayer[nCntPlayer]->GetPos().y == vectorPlayer[nCntPlayer - 1]->GetPos().y)
			{
				vectorPlayer[nCntPlayer]->SetRank(vectorPlayer[nCntPlayer - 1]->GetRank());
			}
		}
	}

	// ���U���g����
	CMiniResult::Create();
}
