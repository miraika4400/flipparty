//=============================================================================
//
// resource_model�w�b�_ [resource_model.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _RESOURCEMODEL_H_
#define _RESOURCEMODEL_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_MATERIAL 64 // �e�N�X�`���ő吔

//*****************************
//�N���X��`
//*****************************

// ���f�����\�[�X�N���X
class CResourceModel
{
public:

	//============
	//�\����
	//============
	// ���f���f�[�^
	typedef struct
	{
		LPDIRECT3DTEXTURE9 apTexture[MAX_MATERIAL]; // �e�N�X�`��
		LPD3DXMESH pMesh;                           // ���b�V�����ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;                      // �}�e���A�����ւ̃|�C���^
		DWORD nNumMat;                              // �}�e���A�����̐�
		D3DXVECTOR3 pos;                            // �ʒu
		D3DXVECTOR3 size;                           // �傫��
		D3DXVECTOR3 rot;                            // ����
		D3DXMATRIX mtxWorld;                        // ���[���h�}�g���b�N�X
		D3DXMATERIAL defMat[MAX_MATERIAL];          // �}�e���A���ۊǗp
		D3DXCOLOR diffuseCol[MAX_MATERIAL];         // �J���[*�g�U
		int nParent;                                // �e�̃C���f�b�N�X
	}Model;

	// ��
	// ���f�����
	typedef enum
	{
		MODEL_GENERAL_SPHERE = 0, // �ėp���f����
		MODEL_GENERAL_BOX,        // �ėp���f���{�b�N�X
		MODEL_TEST,               // �e�X�g���f��
		MODEL_MAX        // ���f����
	}MODEL_TYPE;

	// �����o�֐�
	static CResourceModel * Create(void);                  // �N���X����
	static void Release(void);                               // �N���X�j��
	static Model* GetModel(MODEL_TYPE type); // ���f���̎擾����*�����F�擾���������f��

private:
	CResourceModel();//�B���R���X�g���N�^
public:
	~CResourceModel();

private:
	void Load(void); // ���f���ǂݍ���
	void Unload(void); // ���f���j��

	// �����o�ϐ�
	static const std::string m_aModelPath[MODEL_MAX]; // ���f���̃p�X
	static CResourceModel *m_pSingle;              // ���f���N���X�̃|�C���^*�V���O���g���p
	Model m_apModel[MODEL_MAX];               // ���f���̃|�C���^
};

#endif