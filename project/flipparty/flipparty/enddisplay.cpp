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

#define DISPLAY_SIZE D3DXVECTOR3(100.0f,50.0f,0.0f)
#define SIPLAY_SIZE_DIST DISPLAY_SIZE * 2

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
	//
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
	CScene2d::Init();
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	SetSize(DISPLAY_SIZE);
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_ICON_FLAGRACING));
	
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
	CScene2d::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CEndDisplay::Update(void)
{
	m_nCntTime++;

	if (m_nCntTime == 120)
	{
		//�~�j���U���g�ֈڍs
		CGame::GetRuleManager()->GetRule()->SetRuleState(CRuleBase::RULE_STATE_MINI_RESULT);
		Uninit();

		return;
	}
	else
	{
		//�T�C�Y���擾
		D3DXVECTOR3 size = GetSize();

		size += (SIPLAY_SIZE_DIST - size) * 0.1f;

		//�T�C�Y��ݒ�
		SetSize(size);
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CEndDisplay::Draw(void)
{
	CScene2d::Draw();
}
