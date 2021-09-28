//=============================================================================
//
// enddisplay���� [enddisplay.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enddisplay.h"
#include "resource_texture.h"
#include "manager.h"
#include "sound.h"
#include "rule_base.h"
#include "game.h"
#include "rule_manager.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define DISPLAY_SIZE D3DXVECTOR3(200.0f,50.0f,0.0f)	//�|���S���̃T�C�Y
#define DISPLAY_SIZE_DIST DISPLAY_SIZE * 2	//�g���̃T�C�Y
#define DISPLAY_RATE 0.1f	//�g��W��
#define END_TIME 120	//�I������^�C��

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEndDisplay::CEndDisplay() :CScene2d(CScene::OBJTYPE_SYSTEM)
{
	m_nCntTime = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEndDisplay::~CEndDisplay()
{
}

//=============================================================================
//�N���G�C�g����
//=============================================================================
CEndDisplay * CEndDisplay::Create(void)
{
	CEndDisplay *pEndDisplay = NULL;

	//�C���X�^���X����
	pEndDisplay = new CEndDisplay;

	if (pEndDisplay)
	{
		pEndDisplay->Init();
	}

	return pEndDisplay;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CEndDisplay::Init(void)
{
	//����������
	CScene2d::Init();
	
	//�ʒu�̐ݒ�
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	
	//�T�C�Y�̐ݒ�
	SetSize(DISPLAY_SIZE);
	
	//�e�N�X�`���̐ݒ�
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_END_ICON));
	
	//�Đ����Ă��邷�ׂẲ������~
	CManager::GetSound()->Stop();

	//�I�������Đ�
	CManager::GetSound()->Play(CSound::LABEL_SE_GAME_END);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CEndDisplay::Uninit(void)
{
	//�I������
	CScene2d::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CEndDisplay::Update(void)
{
	m_nCntTime++;

	if (m_nCntTime == END_TIME)
	{
		//�~�j���U���g�ֈڍs
		CGame::GetRuleManager()->GetRule()->SetRuleState(CRuleBase::RULE_STATE_MINI_RESULT);
		
		//�I������
		Uninit();

		return;
	}
	else
	{
		//�T�C�Y���擾
		D3DXVECTOR3 size = GetSize();

		size += (DISPLAY_SIZE_DIST - size) * DISPLAY_RATE;

		//�T�C�Y��ݒ�
		SetSize(size);
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CEndDisplay::Draw(void)
{
	//�`�揈��
	CScene2d::Draw();
}
