

//=============================
// �C���N���[�h
//=============================
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "game.h"
#include "scene.h"
#include "input.h"
#include "keyboard.h"
#include "joypad.h"
#include "mouse.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "game.h"
#include "bg.h"
#include "number.h"
#include "score.h" 
#include "mouse.h"
#include "fade.h"
#include "particle.h"
#include "tutorial.h"
#include "pause.h"
#include "debug_log.h"
#include "model.h"
#include "resource_texture.h"
#include "resource_model.h"
#include "player.h"
#include "Captain.h"

//=============================
// �ÓI�����o�ϐ��錾
//=============================
CManager::MODE   CManager::m_mode = MODE_TITLE;      // �Q�[�����[�h
CRenderer       *CManager::m_pRenderer = NULL;       // �����_���[�|�C���^
CInputKeyboard  *CManager::m_pInputKeyboard = NULL;  // �L�[�{�[�h
CInputJoypad    *CManager::m_pJoypad = NULL;         // �W���C�p�b�h
CInputMouse     *CManager::m_pInputMouse = NULL;     //�@�}�E�X
CSound          *CManager::m_pSound = NULL;          // �T�E���h
CGame           *CManager::m_pGame = NULL;           // �Q�[��
CTitle          *CManager::m_pTitle = NULL;          // �^�C�g��
CResult         *CManager::m_pResult = NULL;         // ���U���g
CFade           *CManager::m_pFade = NULL;           // �t�F�[�h
CTutorial       *CManager::m_pTutorial = NULL;       // �`���[�g���A��
CPause          *CManager::m_pPause = NULL;            // �|�[�Y�|�C���^
bool             CManager::m_bPause = false;         // �|�[�Y�t���O

//=============================
// �R���X�g���N�^
//=============================
CManager::CManager()
{
	
}

//=============================
// �f�X�g���N�^
//=============================
CManager::~CManager()
{
}

//=============================
// ����������
//=============================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	
	// �������̊m�ہE������

	// �L�[�{�[�h
	m_pInputKeyboard = new CInputKeyboard;
	// �L�[�{�[�h������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �W���C�p�b�h
	m_pJoypad = new CInputJoypad;
	// �W���C�p�b�h�̏�����
	if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �}�E�X
	m_pInputMouse = new CInputMouse;
	// �}�E�X������
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �����_���[
	m_pRenderer = new CRenderer;
	// �����_���[�N���X�̏�����
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return E_FAIL;
	}

	// �T�E���h
	m_pSound = new CSound;
	// �T�E���h�N���X�̏�����
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
	}

	// �f�o�b�O���O
	CDebugLog::Init();
	
	// �t�F�[�h�̐���
	m_pFade = CFade::Create();
	m_pFade->SetFade(m_mode);

	// �e�N�X�`���N���X�̐���
	CResourceTexture::Create();
	// ���f�����\�[�X�N���X�̐���
	CResourceModel::Create();

	// �e�N�X�`���E���f���̓ǂݍ���
	CPause::Load();    // �|�[�Y
	CPlayer::Load();   // �v���C���[
	CCaptain::Load();  // �L���v�e��

	// �|�[�Y��Ԃ̎�
	return S_OK;
}

//=============================
// �I������
//=============================
void CManager::Uninit(void)
{
	// �J������
	CScene::ReleaseAll();

	// �e�N�X�`���N���X�̐���
	CResourceTexture::Release();
	// ���f�����\�[�X�N���X�̐���
	CResourceModel::Release();

	// �e�N�X�`���̃A�����[�h
	CPause::Unload();    // �|�[�Y
	CPlayer::Unload();   // �v���C���[
	CCaptain::Unload();  // �L���v�e��

	if (m_pSound != NULL)
	{
		// �I������
		m_pSound->Uninit();
		// �������̉��
		delete m_pSound;
		m_pSound = NULL;
	}

	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();
		// �������̉��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{
		// �I������
		m_pInputKeyboard->Uninit();
		// �������̉��
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	if (m_pJoypad != NULL)
	{
		// �I������
		m_pJoypad->Uninit();
		// �������̉��
		delete m_pJoypad;
		m_pJoypad = NULL;
	}

	if (m_pInputMouse != NULL)
	{
		// �I������
		m_pInputMouse->Uninit();
		// �������̉��
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	if (m_pFade != NULL)
	{
		// �I������
		m_pFade->Uninit();
		// �������̉��
		delete m_pFade;
		m_pFade = NULL;
	}
}


//=============================
// �X�V����
//=============================
void CManager::Update(void)
{
	// �W���C�p�b�h�N���X�̍X�V����
	if (m_pJoypad != NULL)
	{
		m_pJoypad->Update();
	}
	// �L�[�{�[�h�N���X�̍X�V����
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// �}�E�X�N���X�̍X�V����
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Update();
	}

	// �����_���[�N���X�̍X�V����
	if (m_pRenderer != NULL)
	{
		if (m_mode == MODE_GAME)
		{// ���[�h�Q�[���̂Ƃ��|�[�Y��ʂ̏���

			if (m_pInputKeyboard->GetKeyTrigger(DIK_TAB) || m_pJoypad->GetJoystickTrigger(11, 0))
			{// TAB

				if (m_pPause == NULL)
				{
					// ����
					m_pPause = CPause::Create();
				}
				// �|�[�Y�̐؂�ւ�
				m_bPause ^= true;
			}
			if (!m_bPause)
			{// �|�[�Y����Ȃ��Ƃ�

				if (m_pPause != NULL)
				{
					m_pPause->Uninit();
					delete m_pPause;
					m_pPause = NULL;
				}
				m_pRenderer->Update();
			}
			else
			{// �|�[�Y���
				if (m_pPause != NULL)
				{
					// �|�[�Y�̍X�V����
					m_pPause->Update();
				}
			}
		}
		else
		{
			m_pRenderer->Update();
		}
		
	}

	// �t�F�[�h�N���X�̍X�V����
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

}

//=============================
// �`�揈��
//=============================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================
// �Z�b�g���[�h
//=============================
void CManager::SetMode(MODE mode)
{

	switch (m_mode)
	{
	case MODE_TITLE:
		// NULL�N���A
		m_pTitle = NULL;
		break;
	case MODE_TUTORIAL:
		// NULL�N���A
		m_pTutorial = NULL;
		// �^�C�g��BGM��~
		m_pSound->Stop(CSound::LABEL_BGM_TITLE);
		break;
	case MODE_GAME:
		// NULL�N���A
		m_pGame = NULL;
		// �Q�[��BGM��~
		m_pSound->Stop(CSound::LABEL_BGM_GAME);
		break;

	case MODE_RESULT:
		// NULL�N���A
		m_pResult = NULL;
		// ���U���gBGM��~
		//m_pSound->Stop(CSound::LABEL_BGM_RESULT);
		break;

	default:
		break;
	}

	m_mode = mode;
	// �J������
	CScene::ReleaseAll();

	switch (m_mode)
	{
	case MODE_TITLE:
		// �^�C�g������
		m_pTitle = CTitle::Create();
		// �^�C�g��BGM�Đ�
		//m_pSound->Play(CSound::LABEL_BGM_TITLE);
		break;
	case MODE_TUTORIAL:
		// �`���[�g���A������
		m_pTutorial = CTutorial::Create();
		break;
	case MODE_GAME:
		// �Q�[������
		m_pGame = CGame::Create();
		//// �Q�[��BGM�Đ�
		//m_pSound->Play(CSound::LABEL_BGM_GAME);
		break;

	case MODE_RESULT:
		// ���U���g����
		m_pResult = CResult::Create();
		// ���U���gBGM�Đ�
		//m_pSound->Play(CSound::LABEL_BGM_RESULT);
		break;

	default:
		break;
	}
}
