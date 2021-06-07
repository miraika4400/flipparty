//===============================
//
// �W���C�p�b�h�w�b�_ [joypad.h]
// Author:���V ����
//
//===============================

// ��d�C���N���[�h�h�~
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

//===============================
// �C���N���[�h�t�@�C��
//===============================
#include "main.h"
#include "input.h"

//===============================
//�}�N����`
//===============================
#define MAX_JOYSTICK_NUM 4    // JOYPAD�ڑ����
#define	NUM_JOY_MAX 31        // �{�^���̍ő吔
#define JOYSTICK_TIP_MAX 1000 // �X���̒l�̍ő�l
#define JOYPAD_SENSI_RATE 45000.0f // �R���g���[���[�̃X�e�B�b�N�̊��x

//�W���C�p�b�h�N���X
class CInputJoypad : public CInput
{
public:
	//============
	// �����o�֐�
	//============
	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd); // ������
	void Uninit(void);                            // �I��
	void Update(void);                            // �X�V

	bool GetJoystickPress(int nKey, int nId);     // �v���X���̎擾
	bool GetJoystickTrigger(int nKey, int nId);   // �g���K�[���̎擾
	bool GetJoystickRelease(int nKey, int nId);   // �����[�X���̎擾

	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext); // �W���C�p�b�h�̗�
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);      // �W���C�p�b�h�̒l�̐ݒ�
	static DIJOYSTATE CInputJoypad::GetStick(const int nID);                                          // �X�e�B�b�N�̎擾
private:
	//============
	// �����o�ϐ�
	//============
	BYTE m_aJoyState[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};          // �W���C�p�b�h�̓��͏�񃏁[�N
	BYTE m_aJoyStateTrigger[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // �W���C�p�b�h�̃g���K�[���
	BYTE m_aJoyStateRelease[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // �W���C�p�b�h�̃����[�X���

	static LPDIRECTINPUTDEVICE8 m_apDevice[MAX_JOYSTICK_NUM]; // �f�o�C�X
	static int m_nJoyStickCont;                               // �ڑ��䐔
	DIDEVCAPS   m_diDevCaps;


};

#endif