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

//*****************************
//�}�N����`
//*****************************
#define MAX_PLAYER_NUM 1                               // �v���C���[�̍ő吔
#define MAX_NPC_NUM 7                                  // NPC�̍ő吔
#define MAX_CHARACTER_NUM MAX_PLAYER_NUM + MAX_NPC_NUM // �L�����N�^�[�̍ő吔(�v���C���[�ő吔 + NPC�ő吔)

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
	static CCamera     *GetCamera(void) { return m_pCamera; }       // �J�����|�C���^

private:

	//*****************************
	// �����o�ϐ�
	//*****************************
	static CCamera*m_pCamera;            // �J����
	static CLight*m_pLight;                               // ���C�g�|�C���^

};

#endif