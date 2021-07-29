//=============================================================================
//
// iceberg�w�b�_ [iceberg.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _ICEBERG_H_
#define _ICEBERG_H_

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
class CIceberg : public CModel
{
public:
	//============
	// ��
	//============

	// �X�R�^�C�v
	typedef enum
	{
		ICEBERG_Y = 0, // �R�c
		ICEBERG_M,     // ���V
		ICEBERG_K,     // �H��
		ICEBERG_MAX
	}ICEBERG_TYPE;
	//============
	// �����o�֐�
	//============
	CIceberg();
	~CIceberg();

	static CIceberg *Create(D3DXVECTOR3 pos, ICEBERG_TYPE type); // �N���X����

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
	ICEBERG_TYPE m_type;
};

#endif