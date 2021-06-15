////////////////////////////////////////////////////
//
//    captain�N���X�̏���[captain.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "captain.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "game.h"


//*****************************
// �}�N����`
//*****************************
#define HIERARCHY_TEXT_PATH "./data/Texts/hierarchy/Player1.txt"    //�K�w�\���e�L�X�g�̃p�X

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CResourceModel::Model CCaptain::m_model[MAX_PARTS_NUM] = {};
int CCaptain::m_nPartsNum = 0;

//******************************
// �R���X�g���N�^
//******************************
CCaptain::CCaptain() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// �ϐ��̃N���A
}

//******************************
// �f�X�g���N�^
//******************************
CCaptain::~CCaptain()
{
}

//******************************
// �N���G�C�g
//******************************
CCaptain * CCaptain::Create(D3DXVECTOR3 pos)
{
	// �������̊m��
	CCaptain *pCaptain;
	pCaptain = new CCaptain;

	// ������
	pCaptain->Init();

	// �e�l�̑���E�Z�b�g
	pCaptain->SetPos(pos);
	pCaptain->SetPriority(OBJTYPE_PLAYER); // �I�u�W�F�N�g�^�C�v

	return pCaptain;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CCaptain::Load(void)
{

	// ���f���̓ǂݍ���
	LoadModels(HIERARCHY_TEXT_PATH, &m_model[0], &m_nPartsNum);

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CCaptain::Unload(void)
{

	for (int nCnt = 0; nCnt < m_nPartsNum; nCnt++)
	{
		//���b�V���̔j��
		if (m_model[nCnt].pMesh != NULL)
		{
			m_model[nCnt].pMesh->Release();
			m_model[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (m_model[nCnt].pBuffMat != NULL)
		{
			m_model[nCnt].pBuffMat->Release();
			m_model[nCnt].pBuffMat = NULL;
		}
	}
}


//******************************
// ����������
//******************************
HRESULT CCaptain::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nPartsNum, &m_model[0], HIERARCHY_TEXT_PATH)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//******************************
// �I������
//******************************
void CCaptain::Uninit(void)
{
	CModelHierarchy::Uninit();
}

//******************************
// �X�V����
//******************************
void CCaptain::Update(void)
{
}

//******************************
// �`�揈��
//******************************
void CCaptain::Draw(void)
{
	CModelHierarchy::Draw();
}
