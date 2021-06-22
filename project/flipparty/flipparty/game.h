//=============================================================================
//
// game�w�b�_ [game.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _GAME_H_
#define _GAME_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// �O���錾
//=============================
class CRenderer;
class CInputKeyboard;
class CInputJoypad;
class CInputMouse;
class CSound;
class CCamera;
class CLight;
class CCharacter;
class CCpuPoint;
class CCheckPoint;
class CItemPoint;
class CCourse;
class CRuleBase;

//*****************************
//�}�N����`
//*****************************
#define MAX_PLAYER_NUM 1                               // �v���C���[�̍ő吔

//*****************************
//�N���X��`
//*****************************

//2d�|���S���N���X
class CGame : public CScene
{
public:
	//*****************************
	// �񋓒�`
	//*****************************

	//*****************************
	// �����o�֐�
	//*****************************
	CGame();
	~CGame();

	static CGame *Create(void); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

	// �擾����
	static CCamera *GetCamera(void) { return m_pCamera; } // �J�����|�C���^
	static void SetCamera(CCamera * pCamera);             // �J�����N���X�̃Z�b�g����
private:

	//*****************************
	// �����o�ϐ�
	//*****************************
	static CCamera*m_pCamera;            // �J����
	static CLight*m_pLight;                               // ���C�g�|�C���^
	static CRuleBase *m_pGameRule;   // ���[���N���X
};

#endif