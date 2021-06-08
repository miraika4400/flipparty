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
#include "bg.h"
#include "number.h"
#include "score.h" 
#include "mouse.h"
#include "camera.h"
#include "light.h"
#include "fade.h"
#include "keyboard.h"
#include "particle.h"
#include "time.h"
#include "joypad.h"
#include "player.h"

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
CCamera *CGame::m_pCamera = {};           // �J�����N���X�|�C���^
CLight  *CGame::m_pLight = NULL;                           // ���C�g�N���X�|�C���^

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
	// �J�[�\��������
	ShowCursor(FALSE);

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

	// �J�����N���X�̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = CCamera::Create();
	}

	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	return S_OK;
}

//=============================
// �I������
//=============================
void CGame::Uninit(void)
{
	// �J�����N���X�̉������
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
	}
	
	// ���C�g
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// �J������
	Release();
}


//=============================
// �X�V����
//=============================
void CGame::Update(void)
{

	// �J�����N���X�X�V����
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

#ifdef _DEBUG
	// �f�o�b�O�p��ʑJ�ڃR�}���h
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F1))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}

#endif // _DEBUG

}

//=============================
// �`�揈��
//=============================
void CGame::Draw(void)
{
	// �J�����̃Z�b�g
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

