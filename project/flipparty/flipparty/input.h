//===============================
//
// �C���v�b�g�w�b�_ [input.h]
// Author:���V ����
//
//===============================

//��d�C���N���[�h�h�~
#ifndef _INPUT_H_
#define _INPUT_H_

//===============================
//�}�N����`
//===============================
#define	NUM_KEY_MAX (256)

//===============================
// �C���N���[�h�t�@�C��
//===============================
#include "main.h"

//===============================
//�O���錾
//===============================
class CInputKeyboard;

//===============================
//�N���X��`
//===============================

// �C���v�b�g�N���X
class CInput
{
public:
	//============
	// �����o�֐�
	//============
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd); // ������
	virtual void Uninit(void);                            // �I��
	virtual void Update(void) = 0;                        // �X�V

protected:
	static LPDIRECTINPUT8 m_pInput; // DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice; // ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
private:
	CInputKeyboard *m_pKeybord;     // �L�[�{�[�h�N���X
};



#endif