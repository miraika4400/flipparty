//=============================================================================
//
// ���f������ [model.h]
// Author : ���V����
//
//=============================================================================
#ifndef _MODEL_HIERARCHY_H_
#define _MODEL_HIERARCHY_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "model.h"
#include "resource_model.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_PARTS_NUM 15 // �p�[�c�̍ő吔

//=============================================================================
// �K�w�\���t�����f���N���X
//=============================================================================
class CModelHierarchy : public CScene
{
public:
	//============
	// �����o�֐�
	//============
	CModelHierarchy(int nPliority = OBJTYPE_NONE);
	~CModelHierarchy();

	static void LoadModels(char * pPath, CResourceModel::Model *model, int * pNumModel); // ���f���̓ǂݍ���
	void LoadHierarchy(CResourceModel::Model *model, char*pPath);                        // �K�w�\���̓ǂݍ���

	HRESULT Init(void); // ���֐��p
	HRESULT Init(int nNumParts, CResourceModel::Model *model, char*pPath); // ������
	void Uninit(void);                                         // �I��
	void Update(void);                                             // �X�V
	void Draw(void);                                               // �`�� 

	// �e�ϐ��̎擾�E�Z�b�g

	// ���f���f�[�^
	void SetModelData(CResourceModel::Model *pModel);
	CResourceModel::Model * GetModelData(void) { return &m_model[0]; }
	// �p�[�c��
	void SetPartsNum(int nNumParts) { m_nNumParts = nNumParts; }
	int GetPartsNum(void) { return m_nNumParts; }
	// ���W
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void)const { return m_pos; }
	// �T�C�Y
	void SetSize(const D3DXVECTOR3 size) { m_size = size; }
	D3DXVECTOR3 GetSize(void)const { return m_size; }
	// ��]
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void)const { return m_rot; }
private:
	//============
	// �����o�ϐ�
	//============
	CResourceModel::Model m_model[MAX_PARTS_NUM];      // ���f�����
	D3DXVECTOR3 m_pos;                         // ���W
	D3DXVECTOR3 m_rot;                         // ��]
	D3DXVECTOR3 m_size;                        // �T�C�Y
	D3DXMATERIAL m_defMat[MAX_PARTS_NUM][128]; // �}�e���A���ۊǗp
	int m_nNumParts;                           // �p�[�c��
};
#endif 