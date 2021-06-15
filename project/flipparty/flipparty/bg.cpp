//===================================================
//
//    �w�i�N���X�̏���[bg.cpp]
//    Author:���V ����
//
//====================================================

//**********************************
//�C���N���[�h
//**********************************
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "game.h"
#include "resource_model.h"

//*****************************
// �}�N����`
//*****************************
#define SIZE       D3DXVECTOR3(110.0f,110.0f ,110.0f) // �T�C�Y
#define ADD_ROT D3DXVECTOR3(0.0f,0.0005f,0.0f)         // ��������

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************

//==================================
// �R���X�g���N�^
//==================================
CBg::CBg() : CModel(OBJTYPE_BG)
{
	
}

//==================================
// �f�X�g���N�^
//==================================
CBg::~CBg()
{
}

//==================================
// �N���G�C�g
//==================================
CBg * CBg::Create(void)
{
	// �������̊m��
	CBg *pBg = new CBg;
	// ����������
	pBg->Init();

	return pBg;
}


//==================================
// ����������
//==================================
HRESULT CBg::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// ���f�����蓖��
	BindModel(CResourceModel::GetModel(CResourceModel::MODEL_BG));

	// �T�C�Y�̐ݒ�
	SetSize(SIZE);
	
	return S_OK;
}

//==================================
// �I������
//==================================
void CBg::Uninit(void)
{
	CModel::Uninit();
}

//==================================
// �X�V����
//==================================
void CBg::Update(void)
{
	// ��������
	SetRot(GetRot() + ADD_ROT);
}

//==================================
// �`�揈��
//==================================
void CBg::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	// ���C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	CModel::Draw();

	// ���C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
