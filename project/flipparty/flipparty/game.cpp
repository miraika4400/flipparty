////////////////////////////////////////////////////
//
//    �Q�[���N���X�̏���[game.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "game.h"
#include "number.h"
#include "score.h" 
#include "mouse.h"
#include "camera_tps.h"
#include "camera_flygame.h"
#include "light.h"
#include "fade.h"
#include "keyboard.h"
#include "particle.h"
#include "time.h"
#include "joypad.h"
#include "player.h"
#include "captain.h"
#include "rule_base.h"
#include "rule_flygame.h"
#include "remember_rule.h"
#include "flag_raicing_game_rule.h"
#include "rule_manager.h"
#include "result.h"

//=============================
// �}�N����`
//=============================
#define RESULT_COUNT 250 // ���U���g�ւ̑J�ڃJ�E���g
#define INIT_POS_X 400   // �L�����N�^�[�z�u����X�ʒu
#define INIT_POS_Z 0     // �L�����N�^�[�z�u����Y�ʒu
#define SPACE_X 280      // �L�����N�^�[�z�uX�̊Ԋu
#define SPACE_Z 140      // �L�����N�^�[�z�uY�̊Ԋu
#define X_RESET_NUM 4    // �L�����N�^�[�z�uX�����Z�b�g����Ԋu

//=============================
// �ÓI�����o�ϐ��錾
//=============================
CLight  *CGame::m_pLight = NULL;      // ���C�g�N���X�|�C���^
CRuleManager* CGame::m_pRuleManager = NULL; // ���[���}�l�[�W���[�N���X

//=============================
// �R���X�g���N�^
//=============================
CGame::CGame()
{
	// �ϐ��̃N���A
}

//=============================
// �f�X�g���N�^
//=============================
CGame::~CGame()
{
}

//=============================
// �N���G�C�g
//=============================
CGame * CGame::Create(void)
{
	// �������̊m��
	CGame *pGame = new CGame;
	// ������
	pGame->Init();
	return pGame;
}

//=============================
// ����������
//=============================
HRESULT CGame::Init(void)
{
	// �W�v�|�C���g�����������Ă���
	CResult::ResetResultPoint();

	// �|�[�Y�̏�����
	CManager::SetActivePause(false);

	// ���C�g�N���X�̐���
	m_pLight = new CLight;
	// ���C�g�N���X�̏�����
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

#ifdef _DEBUG
	
	//
	//// �J�����N���X�̐���
	//SetCamera(CTpsCamera::Create());
	//
	//// �v���C���[�̐���
	//CPlayer::Create(D3DXVECTOR3(0.0f, -PLAYER_CENTER_HEIGHT, 0.0f), 0);
	//
	////
	/////////////////////////////////////////////////////////////////
#endif
	
	return S_OK;
}

//=============================
// �I������
//=============================
void CGame::Uninit(void)
{
	// �J�����N���X�̉������
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		CManager::SetCamera(NULL);
		pCamera = NULL;
	}
	
	// ���C�g
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// ���[���}�l�[�W���[
	if (m_pRuleManager != NULL)
	{
		m_pRuleManager->Uninit();
		m_pRuleManager = NULL;
	}

	// �J������
	Release();
}

//=============================
// �X�V����
//=============================
void CGame::Update(void)
{
	// ���[���N���X�̐���
	if (m_pRuleManager == NULL)
	{
		m_pRuleManager = CRuleManager::Create();
		m_pRuleManager->SetRule(CRuleManager::RULE_REMENBER);
	}

	// �J�����N���X�X�V����
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Update();
	}

#ifdef _DEBUG
	// �f�o�b�O�p��ʑJ�ڃR�}���h
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F1))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}

	// �f�o�b�O�p���[���J�ڃR�}���h

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_1))
	{
		m_pRuleManager->SetRule(CRuleManager::RULE_FLAG_RACING);
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_2))
	{
		m_pRuleManager->SetRule(CRuleManager::RULE_FLY);
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_3))
	{
		m_pRuleManager->SetRule(CRuleManager::RULE_REMENBER);
	}

#endif // _DEBUG

}

//=============================
// �`�揈��
//=============================
void CGame::Draw(void)
{
	CCamera * pCamera = CManager::GetCamera();
    // �J�����̃Z�b�g
    if (pCamera != NULL)
    {
		pCamera->SetCamera();
    }
}