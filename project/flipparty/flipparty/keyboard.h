//===============================
//
// �L�[�{�[�h�w�b�_ [keyborad.h]
// Author:���V ����
//
//===============================

// ��d�C���N���[�h�h�~
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//===============================
// �C���N���[�h�t�@�C��
//===============================
#include "main.h"
#include "input.h"

//�L�[�{�[�h�N���X
class CInputKeyboard : public CInput
{
public:
	//============
	//�����o�֐�
	//============
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd); // ������
	void Uninit(void);                            // �I��
	void Update(void);                            // �X�V
	bool GetKeyPress(int nKey);                   // �v���X���̎擾
	bool GetKeyTrigger(int nKey);                 // �g���K�[���̎擾
	bool GetKeyRelease(int nKey);                 // �����[�X���̎擾

private:
	//============
	// �����o�ϐ�
	//============
	BYTE m_aKeyState[NUM_KEY_MAX];          // �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];   // �L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];   // �L�[�{�[�h�̃����[�X���
};

#endif