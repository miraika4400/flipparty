//=============================================================================
//
// �}�l�[�W���[�w�b�_ [manager.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================
// �C���N���[�h
//=============================
#include "main.h"

//=============================
// �O���錾
//=============================1
class CRenderer;
class CInputKeyboard;
class CInputJoypad;
class CInputMouse;
class CSound;
class CGame;
class CTitle;
class CResult;
class CFade;
class CTutorial;
class CPause;
class CCamera;

//=============================
// �N���X��`
//=============================

// �}�l�[�W���[�N���X
class CManager
{
public:
	//============
	// ��ԗ�
	//============
	// ��ʑJ�ڃ��[�h
	typedef enum
	{
		MODE_TITLE = 0, // �^�C�g��
		MODE_TUTORIAL,  // �`���[�g���A��
		MODE_GAME,      // �Q�[��
		MODE_RESULT,    // ���U���g
		MODE_MAX,       // ���[�h�̍ő吔
	}MODE;


	//============
	// �����o�֐�
	//============
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow) ;// ������
	void Uninit(void);                                          // �I��
	void Update(void);                                          // �X�V
	void Draw(void);                                            // �`��

	static void SetMode(MODE mode);              // ���[�h�̃Z�b�g
	static MODE GetMode(void) { return m_mode; } // ���[�h�擾

	// �e�|�C���^�̎擾����
	static CRenderer *GetRenderer(void) { return m_pRenderer; }            // �����_���[�̎擾����
	static CInputKeyboard *GetKeyboard(void) { return m_pInputKeyboard; }  // �L�[�{�[�h�̎擾����
	static CInputJoypad *GetJoypad(void) { return m_pJoypad; }             // �W���C�p�b�h�̎擾����
	static CInputMouse *GetMouse(void) { return m_pInputMouse; }           // �}�E�X�̎擾����
	static CSound *GetSound(void) { return m_pSound; }                     // �W���C�p�b�h�̎擾����
	static CGame *GetGame(void) { return m_pGame; }                        // �Q�[���̎擾����
	static CFade * GetFade(void) { return m_pFade; }                       // �t�F�[�h�̎擾����
	static CPause * GetPause(void) { return m_pPause; }                    // �|�[�Y�̎擾����
	static void SetActivePause(bool bPause) { m_bPause = bPause; }         // �|�[�Y�̃Z�b�g
	static bool GetActivePause(void) { return m_bPause; }                  // �t�F�[�h�̎擾����

	static CCamera *GetCamera(void) { return m_pCamera; }                // �J�����|�C���^
	static void SetCamera(CCamera * pCamera);             // �J�����N���X�̃Z�b�g����
private:
	//============
	// �����o�ϐ�
	//============
	static MODE m_mode;                      // ���[�h

	static CRenderer *m_pRenderer;           // �����_���[�|�C���^
	static CInputKeyboard *m_pInputKeyboard; // �L�[�{�[�h�|�C���^
	static CInputJoypad*m_pJoypad;           // �W���C�p�b�h�|�C���^
	static CInputMouse *m_pInputMouse;       // �}�E�X�|�C���^
	static CSound*m_pSound;                  // �T�E���h�|�C���^
	static CGame*m_pGame;                    // �Q�[���N���X�̃|�C���^
	static CTitle*m_pTitle;                  // �^�C�g���N���X�̃|�C���^
	static CResult*m_pResult;                // �^�C�g���N���X�̃|�C���^
	static CFade*m_pFade;                    // �t�F�[�h�|�C���^
	static CTutorial*m_pTutorial;            // �`���[�g���A��
	static CPause*m_pPause;                  // �|�[�Y�|�C���^
	static CCamera*m_pCamera;                // �J����
	static bool m_bPause;                    // �|�[�Y�t���O
	
};

#endif