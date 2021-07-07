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
#define PLAYER_CENTER_HEIGHT 35.0f
#define FLIPPER_NUM 2 // ��̐�
#define RIGHT_FLIPPER_PARTS_NUM 5 // �E�H�̃p�[�c�ԍ�
#define LEFT_FLIPPER_PARTS_NUM  4 // ���H�̃p�[�c�ԍ�

//*****************************
// �O���錾
//*****************************
class CFlipper;
class CBillboard;
class CMotion;
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

	// ��
	//���[�V����
	typedef enum
	{
		MOTION_IDOL = 0,     // �A�C�h��
		MOTION_MINIRESULT_1, // �~�j���U���g1��
		MOTION_MINIRESULT_2, // �~�j���U���g2��
		MOTION_MINIRESULT_3, // �~�j���U���g3��
		MOTION_MINIRESULT_4, // �~�j���U���g�ŉ���
		MOTION_FLY,          // �A�C�h��
		MOTION_MAX
	}MOTION_TYPE;

	// �\��p�^�[��
	typedef enum
	{
		FACE_PATTERN_NORMAL = 0,
		FACE_PATTERN_GOOD,
		FACE_PATTERN_NO_GOOD,
		FACE_PATTERN_MAX
	}FACE_PATTERN;

	// �����o�֐�
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
	void SetMoveFlag(bool bMove) { m_bMove = bMove; }
	bool GetMoveFlag(void) { return m_bMove; }
	// ���ʂ̃Z�b�g�E�擾
	void SetRank(int nRank) { m_nRank = nRank; }
	int GetRank(void) { return m_nRank; }
	// �v���C���[�ԍ��̃Z�b�g�E�擾
	void SetPlayerNumber(int nNum) { m_nPlayerNum = nNum; }
	int GetPlayerNumber(void) { return m_nPlayerNum; }

	CFlipper*GetFlipper(void) { return m_pFlipper; }
	CFlipper*GetFlipperMoveState(void) { return m_pFlipperMoveState; }
	
	// ���[�V�����̃Z�b�g
	void SetMotion(MOTION_TYPE type);
	// �\��̃Z�b�g
	void SetFacePattern(FACE_PATTERN pattern) { m_facePattern = pattern; }

	void SetPoint(int point) { m_nPoint = point; }
	void AddPoint(int point) { m_nPoint += point; }
	int GetPoint(void) { return m_nPoint; }

private:
	void DrawModel(void); // ���f���̕`��
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model *pModelData); // �V�F�[�_�[�v���O�����ɒl�𑗂�

	void ControllFlipper(void);    // �H�̑���
	void ManageFlipperAngle(void); // �H�̊p�x�Ǘ�

	

	// �����o�ϐ�
	static CResourceModel::Model m_model[MAX_PARTS_NUM];  // ���f���\����
	static int m_nPartsNum;             // ���f���p�[�c��
	int m_nPlayerNum;                   // �v���C���[�ԍ�
	CFlipper * m_pFlipper;              // �t���b�p�[�N���X
	CFlipper * m_pFlipperMoveState;     // �t���b�p�[�̈ړ����
	float m_fFlipperDist[FLIPPER_NUM];  // �t���b�p�[�̊p�x�ڕW�l
	CBillboard * m_pPlayerNumIcon;      // �v���C���[�ԍ��̃A�C�R��
	bool m_bMove;                       // �����邩�ǂ����̃t���O
	int m_nRank;                        // ����
	FACE_PATTERN  m_facePattern;               // �\��؂�ւ��p
	int m_nPoint;

	// ���[�V�����p�ϐ�
	static char m_achAnimPath[MOTION_MAX][64];   // �A�j���[�V�����e�L�X�g�̃p�X�i�[�p
	CMotion *m_apMotion[MOTION_MAX];  // �A�j���[�V�����|�C���^
	CMotion *m_pActiveMotion;         // ���ݍĐ����̃��[�V����
#ifdef _DEBUG
	// �f�o�b�O�p�ϐ�
	CPolygon * m_pPolygon[FLIPPER_NUM];// �|���S���N���X�̃|�C���^
#endif // _DEBUG

};

#endif#pragma once
