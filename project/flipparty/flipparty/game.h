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
class CCamera;
class CLight;
class CRuleBase;
class CRuleManager;
//*****************************
//�}�N����`
//*****************************

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
	static CLight*GetLight(void) { return m_pLight; }     // ���C�g�N���X�̃|�C���^
	static CCamera *GetCamera(void) { return m_pCamera; } // �J�����|�C���^
	static void SetCamera(CCamera * pCamera);             // �J�����N���X�̃Z�b�g����

private:

	//*****************************
	// �����o�ϐ�
	//*****************************
	static CCamera*m_pCamera;            // �J����
	static CLight*m_pLight;              // ���C�g�|�C���^
	static CRuleBase *m_pGameRule;       // ���[���N���X
	static CRuleManager* m_pRuleManager; // ���[���}�l�[�W���[
};

#endif