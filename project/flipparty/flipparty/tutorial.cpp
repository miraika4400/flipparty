////////////////////////////////////////////////////
//
//    tutorial�̏���[tutorial.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "resource_texture.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture[TUTORIAL_NUM] = {};

//**********************************
// �}�N����`
//**********************************

//=============================
// �R���X�g���N�^
//=============================
CTutorial::CTutorial()
{
	m_pPolygon = NULL;
	m_nNumTutorial = 0;
}

//=============================
// �f�X�g���N�^
//=============================
CTutorial::~CTutorial()
{
}

//=============================
// �N���G�C�g
//=============================
CTutorial * CTutorial::Create(void)
{
	// �������̊m��
	CTutorial *pTitle = new CTutorial;

	// ������
	pTitle->Init();
	return pTitle;
}

//=============================
// ����������
//=============================
HRESULT CTutorial::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���̐���
	m_pTexture[0] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TUTORIAL);

	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pPolygon->BindTexture(m_pTexture[0]);
	return S_OK;
}

//=============================
// �I������
//=============================
void CTutorial::Uninit(void)
{
	if (m_pPolygon != NULL)
	{
		// �|���S���̏I������
		m_pPolygon->Uninit();

		// �������̉��
		delete m_pPolygon;
		m_pPolygon = NULL;
	}

	// �J������
	Release();
}

//=============================
// �X�V����
//=============================
void CTutorial::Update(void)
{
	// �|���S���̍X�V����
	m_pPolygon->Update();

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
		CManager::GetMouse()->GetMouseTrigger(0) ||
		CManager::GetJoypad()->GetJoystickTrigger(3, 0))
	{
		m_nNumTutorial++;
		if (m_nNumTutorial >= TUTORIAL_NUM)
		{
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
		}
		else
		{
			m_pPolygon->BindTexture(m_pTexture[m_nNumTutorial]);
		}
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_BACKSPACE) ||
		CManager::GetJoypad()->GetJoystickTrigger(2, 0))
	{
		m_nNumTutorial--;
		if (m_nNumTutorial < 0)
		{
			m_nNumTutorial = 0;
		}

		m_pPolygon->BindTexture(m_pTexture[m_nNumTutorial]);
	}
}

//=============================
// �`�揈��
//=============================
void CTutorial::Draw(void)
{
	// �|���S���̕`�揈��
	m_pPolygon->Draw();
}
