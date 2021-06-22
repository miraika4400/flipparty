//=============================================================================
//
// player�w�b�_ [player.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _PLAYER_H_
#define _PLAYER_H_

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
class CFlipper;
class CBillboard;
#ifdef _DEBUG
class CPolygon;
#endif // _DEBUG

//*****************************
// �N���X��`
//*****************************

// �v���C���[�N���X
class CPlayer : public CModelHierarchy
{
public:

	//�����o�֐�
	CPlayer();
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, int nPlayerNum);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ���[�u�t���O�̃Z�b�g�E�擾
	void SetMoveFlag(bool bMove) { m_bMove = true; }
	bool GetMoveFlag(void) { return m_bMove; }

private:
	void ControllFlipper(void);    // �H�̑���
	void ManageFlipperAngle(void); // �H�̊p�x�Ǘ�

	// �����o�ϐ�
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // ���f���\����
	static int m_nPartsNum;        // ���f���p�[�c��
	int m_nPlayerNum;              // �v���C���[�ԍ�
	CFlipper * m_pFlieer;          // �t���b�p�[�N���X
	float m_fFlipperDist[2];       // �t���b�p�[�̊p�x�ڕW�l
	CBillboard * m_pPlayerNumIcon; // �v���C���[�ԍ��̃A�C�R��
	bool m_bMove;                  // �����邩�ǂ����̃t���O

#ifdef _DEBUG
	// �f�o�b�O�p�ϐ�
	CPolygon * m_pPolygon[2];// �|���S���N���X�̃|�C���^
#endif // _DEBUG

};

#endif#pragma once
