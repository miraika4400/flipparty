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

//*****************************
// �O���錾
//*****************************

//*****************************
// �N���X��`
//*****************************

// �L���v�e��(���{�y���M��)�N���X
class CCaptain : public CModelHierarchy
{
public:

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

private:

	// �����o�ϐ�
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // ���f���\����
	static int m_nPartsNum;

};

#endif#pragma once
