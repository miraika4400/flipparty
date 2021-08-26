//=============================================================================
//
// stage�w�b�_ [stage.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _STAGE_H_
#define _STAGE_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "model.h"

//=============================
// �O���錾
//=============================

//*****************************
//�N���X��`
//*****************************

//�X�R�N���X
class CStage : public CModel
{
public:
	//============
	// ��
	//============

	//============
	// �����o�֐�
	//============
	CStage();
	~CStage();

	static CStage *Create(D3DXVECTOR3 pos); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:
	void DrawModel(void);   // ���f���`�揈��
	void SetWorldmtx(void); // ���[���h�}�g���b�N�X�̐ݒ�
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData);// �V�F�[�_�ɒl�𑗂�

	//============
	// �����o�ϐ�
	//============

};

#endif