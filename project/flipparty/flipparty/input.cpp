//===============================
//
//�@���͂̏��� [input.cpp]
//	Author:���V�@����
//
//===============================

//===============================
//�C���N���[�h
//===============================
#include "input.h"
#include "keyboard.h"

//===============================
// �ÓI�����o�ϐ��錾
//===============================
LPDIRECTINPUT8 CInput::m_pInput = NULL;    // DirectInput�|�C���^
//CInputKeyboard *CInput::m_pKeybord; // �L�[�{�[�h�N���X

//===============================
// �R���X�g���N�^
//===============================
CInput::CInput()
{
	m_pDevice = NULL;
}

//===============================
// �f�X�g���N�^
//===============================
CInput::~CInput()
{
}

HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

void CInput::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}
