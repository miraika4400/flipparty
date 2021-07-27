//=============================================================================
//
// passingpenguin�w�b�_ [passingpenguin.h]
// Author : �R�c�ˑ�
//
//=============================================================================
#ifndef _PASSING_PENGUIN_H_
#define _PASSING_PENGUIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "model_hierarchy.h"

//*****************************
// �O���錾
//*****************************
class CMotion;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPassingPenguin :public CModelHierarchy
{
public:
	static CPassingPenguin *Create();
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�ϐ�
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // ���f���\����
	static int m_nPartsNum;	//���f���p�[�c��
	static char m_achAnimPath[64];   // ���[�V�����e�L�X�g�̃p�X�i�[�p
	CMotion *m_pMotion;              // ���[�V�����|�C���^

};
#endif 