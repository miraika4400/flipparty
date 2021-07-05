//=============================================================================
//
// ���f������ [model.h]
// Author : ���V ����
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "resource_model.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_MATERIAL 64 // �e�N�X�`���ő吔

//=============================================================================
//���f���N���X
//=============================================================================
class CModel : public CScene
{
public:
	//============
	//��
	//============
	
	//============
	//�\����
	//============


	//============
	// �����o�֐�
	//============
	CModel(int nPliority = OBJTYPE_NONE);
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos , CResourceModel::MODEL_TYPE modelType  ,D3DXVECTOR3 size = D3DXVECTOR3(1.0f, 1.0f, 1.0f)); // �N���X����*���W,�ėp���f���^�C�v,�T�C�Y

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��
	LPD3DXMESH GetMesh(void)const; // ���b�V���̎擾����

	void BindModel(CResourceModel::Model* modelData); // ���f���̊��蓖��

	// �Q�b�^�[�E�Z�b�^�[
	// ���W
	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)const;
	// �T�C�Y
	void SetSize(const D3DXVECTOR3 size);
	D3DXVECTOR3 GetSize(void)const;
	// ��]
	void SetRot(const D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRot(void)const;
	// ���[���h�}�g���b�N�X
	void SetxWorldMatrix(D3DXMATRIX mtxWorld);
	CResourceModel::Model *GetModelData(void);

private:
	virtual void SetWorldmtx(void); // ���[���h�}�g���b�N�X�̐ݒ�
	virtual void DrawModel(void);   // ���f���`�揈��

	//============
	// �����o�ϐ�
	//============
	CResourceModel::Model m_model;                                   // ���f���f�[�^

	D3DXMATRIX  m_mtxRot;   // ��]�s��
	D3DXMATRIX	m_mtxTrans; // �ʒu�s��
	D3DXMATRIX	m_mtxScail; // �T�C�Y�s��
};
#endif 