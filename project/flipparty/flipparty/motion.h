//=============================================================================
//
// motion�w�b�_ [motion.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _MOTION_H_
#define _MOTION_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "model_hierarchy.h"

//*****************************
// �O���錾
//*****************************
class CCollision;

//*****************************
// �}�N����`
//*****************************
#define MAX_KEYFRAME 10       // �L�[�t���[���̍ő吔

//*****************************
// �N���X��`
//*****************************

// �p�[�e�B�N���N���X
class CMotion :CScene
{
public:

	//============
	// �����o�֐�
	//============
	CMotion();
	~CMotion();

	static CMotion *Create(int nNumParts, const char *pPath, CResourceModel::Model*pModel); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

	// ���f���f�[�^�̃Z�b�g
	void SetModel(CResourceModel::Model*pModel) { m_pModel = pModel; }
	// ���݃L�[�̎擾
	int GetKey(void) { return m_nCntKey; }
	// ���݃t���[���̎擾
	int GetFrame(void) { return m_nCntFrame; }

	// �A�j���[�V������Ԃ̃Z�b�g�E�擾
	void SetActiveMotion(bool bActive);
	bool GetActiveMotion(void) { return m_bMotion; }
private:
	void Load(const char *pPath); // ���[�V�����e�L�X�g�̓ǂݍ���

	//============
	// �����o�ϐ�
	//============
	CResourceModel::Model *m_pModel; // ���f�����
	D3DXVECTOR3 m_pos[MAX_KEYFRAME][MAX_PARTS_NUM];// ���W�̖ڕW�l
	D3DXVECTOR3 m_rot[MAX_KEYFRAME][MAX_PARTS_NUM];// ��]�̖ڕW�l
	D3DXVECTOR3 m_addPos[MAX_PARTS_NUM];     // ���W�̉��Z�l
	D3DXVECTOR3 m_addRot[MAX_PARTS_NUM];     // ��]�̉��Z�l

	int m_nNumKey;                   // �L�[�t���[���̐�
	int m_nNumParts;                 // �p�[�c��
	int m_nNumFrame[MAX_KEYFRAME];   // �t���[����
	int m_nCntKey;                   // �L�[�J�E���g
	int m_nCntFrame;                 // �t���[���J�E���g
	bool m_bMotion;                  // ���[�V�������Ă��邩
	bool m_bLoop;                    // ���[�v���邩
};

#endif