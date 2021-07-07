//=============================================================================
//
// cloud�w�b�_ [cloud.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _CLOUD_H_
#define _CLOUD_H_

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

//�_�N���X
class CCloud : public CModel
{
public:
	//============
	// �����o�֐�
	//============
	CCloud();
	~CCloud();

	static CCloud *Create(D3DXVECTOR3 pos); // �N���X����
	
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
	D3DXVECTOR3 m_size; // �T�C�Y
	int m_nCntAction;   // �A�N�V�����J�E���g
	float m_fAlpha;
};

#endif