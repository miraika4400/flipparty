//=============================================================================
//
// captain�w�b�_ [captain.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _CAPTAIN_H_
#define _CAPTAIN_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "model_hierarchy.h"
#include "game.h"

//*****************************
// �}�N����`
//*****************************
#define MAX_FLAG_TEXTURRE 2

//*****************************
// �O���錾
//*****************************
class CFlipper;
class CMotion;
class CBillboard;
class COrderPolygon;

//*****************************
// �N���X��`
//*****************************

// �L���v�e��(���{�y���M��)�N���X
class CCaptain : public CModelHierarchy
{
public:
	// �\��p�^�[��
	typedef enum
	{
		FACE_PATTERN_NORMAL = 0,
		FACE_PATTERN_GOOD,
		FACE_PATTERN_NO_GOOD,
		FACE_PATTERN_MAX
	}FACE_PATTERN;

	//�����o�֐�
	CCaptain();
	~CCaptain();
	static CCaptain *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void ManageFlipperAngle(void); // �H�̊p�x�Ǘ�

	CFlipper*GetFlipper(void) { return m_pFlipper; }
	CFlipper*GetFlipperMoveState(void) { return m_pFlipperMoveState; }

	// �\��̃Z�b�g
	void SetFacePattern(FACE_PATTERN pattern) { m_facePattern = pattern; }

private:
	void DrawModel(void);// ���f���̕`��
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model *pModelData); // �V�F�[�_�[�v���O�����ɒl�𑗂�
	void ChangeFlipper(void);	//�H�̏�ԕύX
	
	// �����o�ϐ�
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // ���f���\����
	static int m_nPartsNum;	//�p�[�c��

	int m_facePattern;	//��e�N�X�`���p�^�[��

	CFlipper * m_pFlipper;          // �t���b�p�[�N���X
	CFlipper * m_pFlipperMoveState;
	float m_fFlipperDist[2];       // �t���b�p�[�̊p�x�ڕW�l
	COrderPolygon *m_pOrder;
	// ���[�V�����p�ϐ�
	static char m_achAnimPath[64];   // ���[�V�����e�L�X�g�̃p�X�i�[�p
	CMotion *m_pMotion;              // ���[�V�����|�C���^
};

#endif
