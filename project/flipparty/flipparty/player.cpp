////////////////////////////////////////////////////
//
//    particle�N���X�̏���[particle.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "game.h"
#include "flipper.h"

//*****************************
// �}�N����`
//*****************************
#define HIERARCHY_TEXT_PATH1 "./data/Texts/hierarchy/pengin00.txt"    //�K�w�\���e�L�X�g�̃p�X

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CResourceModel::Model CPlayer::m_model[MAX_PARTS_NUM] = {};
int CPlayer::m_nPartsNum = 0;

//******************************
// �R���X�g���N�^
//******************************
CPlayer::CPlayer() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// �ϐ��̃N���A
	m_pFlieer = NULL;
	m_nPlayerNum = 0;                  // �v���C���[�ԍ�
}

//******************************
// �f�X�g���N�^
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// �N���G�C�g
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
	// �������̊m��
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->m_nPlayerNum = nPlayerNum;
	
	// ������
	pPlayer->Init();

	// �e�l�̑���E�Z�b�g
	pPlayer->SetPos(pos);
	pPlayer->SetPriority(OBJTYPE_PLAYER); // �I�u�W�F�N�g�^�C�v

	return pPlayer;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CPlayer::Load(void)
{

	// ���f���̓ǂݍ���
	LoadModels(HIERARCHY_TEXT_PATH1, &m_model[0], &m_nPartsNum);

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CPlayer::Unload(void)
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
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nPartsNum, &m_model[0], HIERARCHY_TEXT_PATH1)))
	{
		return E_FAIL;
	}

	m_pFlieer = CFlipper::Create();
	return S_OK;
}

//******************************
// �I������
//******************************
void CPlayer::Uninit(void)
{
	CModelHierarchy::Uninit();

	// �t���b�p�[�N���X�̏I������
	if (m_pFlieer != NULL)
	{
		m_pFlieer->Uninit();
		m_pFlieer = NULL;
	}
}

//******************************
// �X�V����
//******************************
void CPlayer::Update(void)
{
	CResourceModel::Model * pModelData = GetModelData();
	
	if (CManager::GetKeyboard()->GetKeyPress(DIK_UP))
	{
		pModelData[5].rot.z -= D3DXToRadian(2.0f);
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_DOWN))
	{
		pModelData[5].rot.z += D3DXToRadian(2.0f);
	}

	if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
	{
		pModelData[4].rot.z += D3DXToRadian(2.0f);
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_S))
	{
		pModelData[4].rot.z -= D3DXToRadian(2.0f);
	}
	
}

//******************************
// �`�揈��
//******************************
void CPlayer::Draw(void)
{
	CModelHierarchy::Draw();
}
