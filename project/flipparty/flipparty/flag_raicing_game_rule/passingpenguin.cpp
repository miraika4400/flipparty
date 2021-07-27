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
#include "renderer.h"
#include "motion.h"
#ifdef _DEBUG
#include "manager.h"
#include "keyboard.h"
#endif
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
		pPassingPenguin->SetPriority(OBJTYPE_CPU); // �I�u�W�F�N�g�^�C�v
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

	//���[�V�����̐���
	m_pMotion = CMotion::Create(m_nPartsNum, m_achAnimPath, GetModelData());

	//���[�V�����̍Đ�
	m_pMotion->SetActiveMotion(true);

	return S_OK;
}

//=============================================================================
//passingpenguin�N���X�̏I������
//=============================================================================
void CPassingPenguin::Uninit(void)
{
	//�K�w�\���t�����f���N���X�̏I��
	CModelHierarchy::Uninit();
}


//=============================================================================
//passingpenguin�N���X�̍X�V����
//=============================================================================
void CPassingPenguin::Update(void)
{
#ifdef _DEBUG
	D3DXVECTOR3 pos = GetPos();

	//��
	if (CManager::GetKeyboard()->GetKeyPress(DIK_NUMPAD4))
	{
		pos.x += 1.0f;
	}
	//�E
	if (CManager::GetKeyboard()->GetKeyPress(DIK_NUMPAD6))
	{
		pos.x -= 1.0f;
	}

	//��O
	if (CManager::GetKeyboard()->GetKeyPress(DIK_NUMPAD2))
	{
		pos.z += 1.0f;
	}
	//��
	if (CManager::GetKeyboard()->GetKeyPress(DIK_NUMPAD8))
	{
		pos.z -= 1.0f;
	}

	SetPos(pos);
#endif
}

//=============================================================================
//passingpenguin�N���X�̕`�揈��
//=============================================================================
void CPassingPenguin::Draw(void)
{
	//�K�w�\���t�����f���N���X�̕`��
	CModelHierarchy::Draw();
}

////=============================================================================
////passingpenguin�N���X�̃��f���̕`�揈��
////=============================================================================
//void CPassingPenguin::DrawModel(void)
//{
//	
//}
//
////=============================================================================
////passingpenguin�N���X�̃V�F�[�_�[�̐ݒ菈��
////=============================================================================
//void CPassingPenguin::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
//{
//}
