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
#include "cloud.h"
#include "thunder.h"
#include "iceberg.h"
#include "manager.h"
#include "result.h"
#include "rule_manager.h"
#include "sea.h"
#include "stage.h"

//******************************
// �}�N����`
//******************************
#define PLAYER_SPACE 150.0f //�@�v���C���[�ʒu�̊Ԋu
#define PLAY_TIME 30        // ��������

//******************************
// �ÓI�����o�ϐ��錾
//******************************
CFlyGamePlayer * CRuleFly::m_pPlayer[4] = {};
bool CRuleFly::m_bPlay = true;
//******************************
// �R���X�g���N�^
//******************************
CRuleFly::CRuleFly()
{
	// �ϐ��̃N���A
	m_pTimeLimit = NULL;
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
	// �X�R�̐���
	CIceberg::Create(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), CIceberg::ICEBERG_TYPE(rand() % CIceberg::ICEBERG_MAX));

	// �C�̐���
	CSea::Create(D3DXVECTOR3(0.0f, -14.0f, 0.0f), 0.001f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -12.0f, 0.0f), 0.0025f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -10.0f, 0.0f), 0.004f, CSea::TYPE_NORMAL);

	// �w�i�̐���
	CBg::Create();

	// �J�����N���X�̐���
	CManager::SetCamera(CFlyGameCamera::Create());

	// �v���C���[���̎擾
	int nPlayNum = CCountSelect::GetPlayerNum();
	
	// �v���C���[�̐���
	// �����ʒuX���̒���
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		m_pPlayer[nCntPlayer] = CFlyGamePlayer::Create(D3DXVECTOR3(posX, 0.0f, 0.0f), nCntPlayer);
		m_pPlayer[nCntPlayer]->SetRot(D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f));

		// �X�e�[�W�̐���
		CStage::Create(D3DXVECTOR3(posX, 0.0f, 0.0f), CStage::STAGE_TYPE_NORMAL);

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

	////////////////////////////////////////
	// ���u��

	// ���_�̐���
	if (m_pTimeLimit->GetTimeLimit() == 20 && m_pTimeLimit->GetTimeCount() == 0 || m_pTimeLimit->GetTimeLimit() == 10 && m_pTimeLimit->GetTimeCount() == 0)
	{
		for (int nCntPlayer = 0; nCntPlayer < CCountSelect::GetPlayerNum(); nCntPlayer++)
		{
			CCloud::Create(nCntPlayer);
		}
	}

	/////////////////////////////////////////

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
			//CManager::SetCamera(CFlyGameCamera::Create());
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

	// Y���W�̍������Ƀ\�[�g
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

		// �~�j�Q�[���ɏ��ʂ𑗂�
		CResult::SetMiniGameRank(CRuleManager::RULE_FLY, vectorPlayer[nCntPlayer]->GetPlayerNumber(), vectorPlayer[nCntPlayer]->GetRank());
	}

	// ���U���g����
	CMiniResult::Create();
}
