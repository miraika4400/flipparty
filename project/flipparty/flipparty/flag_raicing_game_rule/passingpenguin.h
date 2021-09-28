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
	//�ړ������̗񋓌^
	typedef enum
	{
		MOVE_DIRECTION_LEFT = 0,	//���ֈړ�
		MOVE_DIRECTION_RIGHT,		//�E�ֈړ�
		MOVE_DIRECTION_MAX
	}MOVE_DIRECTION;
	
	//��Ԃ̗񋓌^
	typedef enum
	{
		STATE_WAIT = 0,	//�ҋ@
		STATE_MOVE,		//�ړ�
		STATE_MAX
	}STATE;

	CPassingPenguin();
	~CPassingPenguin();
	static CPassingPenguin *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMoveDirection(MOVE_DIRECTION moveDirection);
private:
	void Move(void);
	void DrawModel(void);// ���f���̕`��
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model *pModelData); // �V�F�[�_�[�v���O�����ɒl�𑗂�

	// �����o�ϐ�
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // ���f���\����
	static int m_nPartsNum;	//���f���p�[�c��
	static char m_achAnimPath[64];   // ���[�V�����e�L�X�g�̃p�X�i�[�p
	CMotion *m_pMotion;              // ���[�V�����|�C���^
	int m_facePattern;
	MOVE_DIRECTION m_moveDirection;	//�ړ�����
	STATE m_state;	//���
	D3DXVECTOR3 m_move;	//�ړ���
	int m_nSoudCounter;

};
#endif 