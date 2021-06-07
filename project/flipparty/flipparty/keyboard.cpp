////////////////////////////////////////////////////
//
//    �L�[�{�[�h�N���X�̏���[keyboard.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "keyboard.h"

//******************************
// �R���X�g���N�^
//******************************
CInputKeyboard::CInputKeyboard()
{
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}

//******************************
// �f�X�g���N�^
//******************************
CInputKeyboard::~CInputKeyboard()
{
}

//******************************
// ����������
//******************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//******************************
// �I������
//******************************
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//******************************
// �X�V����
//******************************
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX] = {};
	int nCntKey;

	//�f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//�L�[�g���K�[
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			//�L�[�����[�X
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];

			//�L�[�v���X����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//******************************
// �v���X���̎擾
//******************************
bool CInputKeyboard::GetKeyPress(int nKey)
{
	return m_aKeyState[nKey] & 0x80 ? true : false;
}

//******************************
// �g���K�[���̎擾
//******************************
bool CInputKeyboard::GetKeyTrigger(int nKey)
{
	return m_aKeyStateTrigger[nKey] & 0x80 ? true : false;
}

//******************************
// �����[�X���̎擾
//******************************
bool CInputKeyboard::GetKeyRelease(int nKey)
{
	return m_aKeyStateRelease[nKey] & 0x80 ? true : false;
}
