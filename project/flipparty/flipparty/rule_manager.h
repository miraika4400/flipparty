//=============================================================================
//
// rule_manager�w�b�_ [rule_manager.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _RULE_MANAGER_H_
#define _RULE_MANAGER_H_

//*****************************
//�C���N���[�h
//*****************************
#include "scene.h"

//=============================
// �O���錾
//=============================

//*****************************
//�}�N����`
//*****************************
class CRuleBase;
class CPolygon;
//*****************************
//�N���X��`
//*****************************

// ���[���Ǘ��N���X
class CRuleManager : public CScene
{
public:
	//*****************************
	// �񋓒�`
	//*****************************
	// ���[����
	typedef enum
	{
		RULE_FLAG_RACING = 0, // ���g��
		RULE_FLY,             // �t���C
		RULE_REMENBER,        // �L��
		RULE_MAX
	}RULE_TYPE;

	// �t�F�[�h���
	typedef enum
	{
		FADE_NONE = 0, // ���ł��Ȃ����
		FADE_IN,       // �t�F�[�h�C��
		FADE_OUT,      // �t�F�[�h�A�E�g
		FADE_MAX,      // ��Ԃ̍ő吔
	}FADE_STATE;

	//*****************************
	// �����o�֐�
	//*****************************
	CRuleManager();
	~CRuleManager();

	static CRuleManager *Create(void); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

	void SetRule(RULE_TYPE ruleNext); //���[���̃Z�b�g
	void TransitionRule(void);        // ���[���J��
private:

	//*****************************
	// �����o�ϐ�
	//*****************************
	CRuleBase* m_pGameRule;     // ���[��
	CPolygon*  m_pFadePolygon;  // �t�F�[�h�p�|���S��
	RULE_TYPE  m_ruleNext;      // �l�N�X�g���[��
	FADE_STATE m_fadeState;     // �t�F�[�h���
	D3DXCOLOR  m_polygonCol;    // �J���[

};

#endif