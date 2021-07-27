//=============================================================================
//
// passingpenguin�N���X�̏��� [passingpenguin.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "passingpenguin.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define HIERARCHY_TEXT_PATH_PASSING "./data/Texts/hierarchy/pengin00.txt"   // �K�w�\���e�L�X�g�̃p�X

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CResourceModel::Model CPassingPenguin::m_model[MAX_PARTS_NUM] = {};    // ���f���\����
int CPassingPenguin::m_nPartsNum = 0;	//���f���p�[�c��
char CPassingPenguin::m_achAnimPath[64] = { "./data/Texts/motion/run.txt" };  // ���[�V�����e�L�X�g�̃p�X�i�[�p

//=============================================================================
//passingpenguin�N���X�̃R���X�g���N�^
//=============================================================================
CPassingPenguin::CPassingPenguin()
{
	m_pMotion = NULL;
}

//=============================================================================
//passingpenguin�N���X�̃f�X�g���N�^
//=============================================================================
CPassingPenguin::~CPassingPenguin()
{
}

//=============================================================================
//passingpenguin�N���X�̃N���G�C�g����
//=============================================================================
CPassingPenguin * CPassingPenguin::Create(D3DXVECTOR3 pos)
{
	CPassingPenguin *pPassingPenguin = NULL;

	//�C���X�^���X����
	pPassingPenguin = new CPassingPenguin;

	if (pPassingPenguin)
	{
		pPassingPenguin->SetPos(pos);
		pPassingPenguin->Init();
	}

	return pPassingPenguin;
}

//=============================================================================
//passingpenguin�N���X��
//=============================================================================
HRESULT CPassingPenguin::Load(void)
{
	//���f���̓ǂݍ���
	LoadModels(HIERARCHY_TEXT_PATH_PASSING, m_model, &m_nPartsNum);
	return S_OK;
}

//=============================================================================
//passingpenguin�N���X��
//=============================================================================
void CPassingPenguin::Unload(void)
{
	for (int nCntParts = 0; nCntParts < m_nPartsNum; nCntParts++)
	{
		//���b�V���̔j��
		if (m_model[nCntParts].pMesh)
		{
			m_model[nCntParts].pMesh->Release();
			m_model[nCntParts].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (m_model[nCntParts].pBuffMat)
		{
			m_model[nCntParts].pBuffMat->Release();
			m_model[nCntParts].pBuffMat = NULL;
		}
	}

}

//=============================================================================
//passingpenguin�N���X�̏���������
//=============================================================================
HRESULT CPassingPenguin::Init(void)
{
	//�K�w�\���t�����f���N���X�̏�����
	if (FAILED(CModelHierarchy::Init(m_nPartsNum, &m_model[0], HIERARCHY_TEXT_PATH_PASSING)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
//passingpenguin�N���X�̏I������
//=============================================================================
void CPassingPenguin::Uninit(void)
{
	//�K�w���f���̏I��
	CModelHierarchy::Uninit();
}


//=============================================================================
//passingpenguin�N���X�̍X�V����
//=============================================================================
void CPassingPenguin::Update(void)
{
}

//=============================================================================
//passingpenguin�N���X�̕`�揈��
//=============================================================================
void CPassingPenguin::Draw(void)
{
	//�`��
	CModelHierarchy::Draw();
}

//=============================================================================
//passingpenguin�N���X�̃��f���̕`�揈��
//=============================================================================
void CPassingPenguin::DrawModel(void)
{
}

//=============================================================================
//passingpenguin�N���X�̃V�F�[�_�[�̐ݒ菈��
//=============================================================================
void CPassingPenguin::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
{
}
