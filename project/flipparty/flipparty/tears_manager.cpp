////////////////////////////////////////////////////
//
//    �^�C�g���N���X�̏���[title.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//=============================
// �C���N���[�h
//=============================
#include "tears_manager.h"
#include "tears_particle.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//**********************************
// �}�N����`
//**********************************
#define TEARS_INTERVAL 10 // �܂𐶐�����C���^�[�o��

//=============================
// �R���X�g���N�^
//=============================
CTearsManager::CTearsManager(): CScene(OBJTYPE_SYSTEM)
{
	m_nCntTesrsInterval = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================
// �f�X�g���N�^
//=============================
CTearsManager::~CTearsManager()
{
}

//=============================
// �N���G�C�g
//=============================
CTearsManager * CTearsManager::Create(D3DXVECTOR3 pos)
{
	// �������̊m��
	CTearsManager *pTearsManager = new CTearsManager;
	// ������
	pTearsManager->Init();
	// ���W
	pTearsManager->m_pos = pos;

	return pTearsManager;
}

//=============================
// ����������
//=============================
HRESULT CTearsManager::Init(void)
{
	// �J�E���g������
	m_nCntTesrsInterval = 0;

	return S_OK;
}

//=============================
// �I������
//=============================
void CTearsManager::Uninit(void)
{
	// �J������
	Release();
}


//=============================
// �X�V����
//=============================
void CTearsManager::Update(void)
{
	// �܂̐���
	m_nCntTesrsInterval++;
	if ((m_nCntTesrsInterval%TEARS_INTERVAL) == 0)
	{
		CTearsParticle::Create(m_pos);
	}
}


//=============================
// �`�揈��
//=============================
void CTearsManager::Draw(void)
{
}
