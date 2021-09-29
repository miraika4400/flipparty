//=============================================================================
//
// add_point_display�w�b�_ [add_point_display.cpp]
// Author : �R�c�@�ˑ�
//
//=============================================================================
#include "add_point_display.h"
#include "resource_texture.h"
#include "count_selection.h"
#include "manager.h"
#include "sound.h"
#include "game.h"
#include "rule_base.h"
#include "rule_manager.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define U_ONE_FRAME 1.0f / MAX_PLAYER_NUM
#define V_ONE_FRAME 1.0f / POINT_DISPLAY_TYPE_MAX
#define DISPLAY_SIZE D3DXVECTOR3(80.0f,40.0f,0.0f)

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CAddPointDisplay::CAddPointDisplay()
{
	m_displayType = POINT_DISPLAY_TYPE_3PT;
	m_IsDraw = false;
	m_nPlayerNumber = 0;
	m_nShoeCounter = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CAddPointDisplay::~CAddPointDisplay()
{
}

//=============================================================================
//�N���G�C�g����
//=============================================================================
CAddPointDisplay * CAddPointDisplay::Create(int nPlayerNumber)
{
	CAddPointDisplay *pPointDisplay = NULL;

	//�C���X�^���X����
	pPointDisplay = new CAddPointDisplay;

	if (pPointDisplay)
	{
		pPointDisplay->m_nPlayerNumber = nPlayerNumber;
		pPointDisplay->Init();
	}
	return pPointDisplay;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CAddPointDisplay::Init(void)
{
	CScene2d::Init();

	//�T�C�Y
	SetSize(DISPLAY_SIZE);

	//�e�N�X�`���̐ݒ�
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ADD_POINT_DISPLAY));
	
	D3DXVECTOR2 uvPos[4];
	uvPos[0] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME, m_displayType * V_ONE_FRAME);
	uvPos[1] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME + U_ONE_FRAME, m_displayType * V_ONE_FRAME);
	uvPos[2] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME, m_displayType * V_ONE_FRAME + V_ONE_FRAME);
	uvPos[3] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME + U_ONE_FRAME, m_displayType * V_ONE_FRAME + V_ONE_FRAME);

	//UV���W�̐ݒ�
	SetTextureUV(uvPos);

	//�`�揇��ݒ�
	SetPriority(OBJTYPE_UI);

	//�e�N�X�`���^�C�v��ݒ�
	m_displayType = POINT_DISPLAY_TYPE_3PT;

	//�`����I�t�ɂ���
	m_IsDraw = false;

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CAddPointDisplay::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CAddPointDisplay::Update(void)
{
	CScene2d::Update();

	if (m_IsDraw)
	{
		if (m_nShoeCounter == 40)
		{
			m_IsDraw = false;
		}

		m_nShoeCounter++;
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CAddPointDisplay::Draw(void)
{
	if (m_IsDraw)
	{
		CScene2d::Draw();
	}
}

//=============================================================================
//�f�B�X�v���C�ݒ菈��
//=============================================================================
void CAddPointDisplay::SetDisplay(POINT_DISPLAY_TYPE displayType)
{
	if (CGame::GetRuleManager()->GetRule()->GetRuleState() == CRuleBase::RULE_STATE_GAME)
	{
		m_displayType = displayType;

		m_IsDraw = true;
		m_nShoeCounter = 0;
		D3DXVECTOR2 uvPos[4];
		uvPos[0] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME, m_displayType * V_ONE_FRAME);
		uvPos[1] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME + U_ONE_FRAME, m_displayType * V_ONE_FRAME);
		uvPos[2] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME, m_displayType * V_ONE_FRAME + V_ONE_FRAME);
		uvPos[3] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME + U_ONE_FRAME, m_displayType * V_ONE_FRAME + V_ONE_FRAME);

		//UV���W�̐ݒ�
		SetTextureUV(uvPos);

		if (m_displayType == POINT_DISPLAY_TYPE_MISS)
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_MISS);
		}
		else
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_OK);
		}
	}
}