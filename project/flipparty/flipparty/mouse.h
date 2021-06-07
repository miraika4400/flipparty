//===============================
//
// �}�E�X�w�b�_ [mouse.h]
// Author:���V ����
//
//===============================

// ��d�C���N���[�h�h�~
#ifndef _MOUSE_H_
#define _MOUSE_H_

//===============================
// �C���N���[�h
//===============================
#include "main.h"
#include "input.h"

//===============================
// �}�N����`
//===============================
#define MAX_MOUSE_BOTTON 3           // �}�E�X�{�^���̍ő吔

//===============================
// �N���X��`
//===============================

//�}�E�X�N���X
class CInputMouse : public CInput
{
public:
	//============
	// �����o�֐�
	//============
	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd); // ������
	void Uninit(void);                            // �I��
	void Update(void);                            // �X�V

	bool GetMousePress(int nKey);      // �v���X���̎擾
	bool GetMouseTrigger(int nKey);    // �g���K�[���̎擾
	bool GetMouseRelease(int nKey);    // �����[�X���̎擾
	D3DXVECTOR3 GetMousePos(void);     // �}�E�X�J�[�\�����W�̎擾
	void SetMousePos(D3DXVECTOR3 pos); // �}�E�X�J�[�\�����W�̃Z�b�g
	D3DXVECTOR3 GetMouseMove(void);    // �}�E�X�̈ړ��ʂ̎擾
private:
	// �����o�ϐ�
	BYTE m_aMouseState[MAX_MOUSE_BOTTON];          // �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aMouseStateTrigger[MAX_MOUSE_BOTTON];   // �L�[�{�[�h�̃g���K�[���
	BYTE m_aMouseStateRelease[MAX_MOUSE_BOTTON];   // �L�[�{�[�h�̃����[�X���
	DIMOUSESTATE m_mousState;                      // �}�E�X���
};

#endif