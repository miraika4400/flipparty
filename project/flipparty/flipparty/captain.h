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
class CFlipper;

//*****************************
// �N���X��`
//*****************************

// �L���v�e��(���{�y���M��)�N���X
class CCaptain : public CModelHierarchy
{
public:
	typedef enum
	{
		RED_FLAG_UP = 0,	// �ԏオ���Ă�����
		WHITE_FLAG_UP,		// ���オ���Ă�����
		RED_FLAG_DOWN,		// �ԉ������Ă�����
		WHITE_FLAG_DOWN,	// ���������Ă�����
		FLAG_END
	}FLAG;

	typedef enum
	{
		COLOR_NORMAL = 0,
		WHITE_UP,			// ���オ���Ă�����
		WHITE_DOWN,			// ���������Ă�����
		RED_UP,				// �ԏオ���Ă�����
		RED_DOWN,			// �ԉ������Ă�����
		COLOR_END
	}COLOR;

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

	void Judge(FLAG ColorFlagRed, FLAG ColorFlagWhite, COLOR ColorRed, COLOR ColorWhite);	// �F���ʏ���
	void JudgeColor(FLAG ColorFlagRed, FLAG ColorFlagWhite, COLOR ColorRed, COLOR ColorWhite);
	void FlagJudge();

	void ManageFlipperAngle(void); // �H�̊p�x�Ǘ�
	void Choice(int choice) { m_nChoice = choice; }

	CFlipper*GetFlipper(void) { return m_pFlipper; }
	CFlipper*GetFlipperMoveState(void) { return m_pFlipperMoveState; }

	// �\��̃Z�b�g
	void SetFacePattern(FACE_PATTERN pattern) { m_facePattern = pattern; }

private:
	void DrawModel(void);// ���f���̕`��
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model *pModelData); // �V�F�[�_�[�v���O�����ɒl�𑗂�

	// �����o�ϐ�
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // ���f���\����
	static int m_nPartsNum;

	int m_nCntTime;
	int m_nColor;
	int m_nCount;
	int m_nChoice;
	int m_facePattern;

	bool m_bJudgRed;				// �ԏグ�Ă邩�����Ă邩�̔���
	bool m_bJudgWhite;				// ���グ�Ă邩�����Ă邩�̔���

	FLAG m_eColorRed;
	FLAG m_eColorWhite;

	CFlipper * m_pFlipper;          // �t���b�p�[�N���X
	CFlipper * m_pFlipperMoveState;
	float m_fFlipperDist[2];       // �t���b�p�[�̊p�x�ڕW�l
};

#endif#pragma once
