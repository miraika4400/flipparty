//=============================================================================
//
// stratcount�w�b�_ [stratcount.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "startcount.h"
#include "number.h"
#include "manager.h"
#include "sound.h"
#include "resource_texture.h"
#include "scene2d.h"
#include "game.h"
#include "rule_manager.h"
#include "rule_base.h"
#include "game.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define LIMIT_TIME 3
#define STRAT_NUMBER_SIZE_X 50.0f
#define STRAT_NUMBER_SIZE_Y 100.0f
#define STRAT_ICON_SIZE_X 200.0f
#define STRAT_ICON_SIZE_Y 50.0f 
#define STRAT_ICON_SIZE_DIST (D3DXVECTOR3(STRAT_ICON_SIZE_X * 2, STRAT_ICON_SIZE_Y *2, 0.0f))
#define SCALE_RATE 0.1f
#define NUMBER_UPDATE_TIME 1	//�i���o�[�N���X���X�V����ŏI����
#define NUMBER_DELETE_TIME 0	//�i���o�[�N���X���폜����c�莞��
#define SCENE_DELETE_TIME -2	//2D�|���S���̍폜����c�莞��

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CStratCount::CStratCount() :CScene(CScene::OBJTYPE_SYSTEM)
{
	m_pNumber = NULL;
	m_pScene2D = NULL;
	m_nCntTime = 0;
	m_nLimitTime = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CStratCount::~CStratCount()
{
}

//=============================================================================
//�N���G�C�g����
//=============================================================================
CStratCount * CStratCount::Create(void)
{
	CStratCount *pStratCount = NULL;

	//�C���X�^���X����
	pStratCount = new CStratCount;

	if (pStratCount)
	{
		//������
		pStratCount->Init();
		//�v���C�I���e�B�̐ݒ�
		pStratCount->SetPriority(CScene::OBJTYPE_SYSTEM);
	}

	return pStratCount;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CStratCount::Init(void)
{
	//�����̏�����
	m_nLimitTime = LIMIT_TIME;

	m_nCntTime = 0;

	//�i���o�[�̐���
	m_pNumber = CNumber::Create(
		m_nLimitTime,
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(STRAT_NUMBER_SIZE_X, STRAT_NUMBER_SIZE_Y, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�J�E���g���̍Đ�
	CManager::GetSound()->Play(CSound::LABEL_SE_COUNT);
	
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CStratCount::Uninit(void)
{
	//���g��j��
	CScene::Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CStratCount::Update(void)
{
	//�J�E���g�𑝂₷
	m_nCntTime++;

	if (m_nCntTime >= 60)
	{
		//�J�E���g��������
		m_nCntTime = 0;

		//�������Ԃ����炷
		m_nLimitTime--;

		if (m_pNumber && m_nLimitTime >= NUMBER_UPDATE_TIME)
		{
			//�ύX���ꂽ�l��^����
			m_pNumber->SetNumber(m_nLimitTime);

			//�J�E���g���̍Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_COUNT);
		}
	}

	if (m_nLimitTime <= SCENE_DELETE_TIME)
	{
		//���[���̏�Ԃ��Q�[���֐ݒ�
		CGame::GetRuleManager()->GetRule()->SetRuleState(CRuleBase::RULE_STATE_GAME);

		//�|���S���̏I��
		m_pScene2D->Uninit();

		//�I������
		Uninit();

		return;
	}
	else if (m_nLimitTime <= NUMBER_DELETE_TIME)
	{
		//�i���o�[�̍폜
		if (m_pNumber)
		{
			//�I������
			m_pNumber->Uninit();

			//�������폜
			delete m_pNumber;

			//�������̃N���A
			m_pNumber = NULL;
		}
		if (!m_pScene2D)
		{
			//�|���S������
			m_pScene2D = CScene2d::Create();

			//�T�C�Y�̐ݒ�
			m_pScene2D->SetSize(D3DXVECTOR3(STRAT_ICON_SIZE_X, STRAT_ICON_SIZE_Y, 0.0f));

			//�e�N�X�`���̐ݒ�
			m_pScene2D->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_STRAT_ICON));

			//�X�^�[�g���������ōĐ��\��
		}
		else
		{
			//�T�C�Y���擾
			D3DXVECTOR3 size = m_pScene2D->GetSize();

			//�ړI�T�C�Y�ɂȂ�悤�ɉ��Z
			size += (STRAT_ICON_SIZE_DIST - size) * SCALE_RATE;

			//�T�C�Y�̐ݒ�
			m_pScene2D->SetSize(size);
		}
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CStratCount::Draw(void)
{
	if (m_pNumber)
	{
		//�`�揈��
		m_pNumber->Draw();
	}
}
