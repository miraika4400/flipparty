//=======================================================================================
//
//�^�C�g�����j���[���� [titlemenu.cpp]
// Author : Masuzawa Mirai
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "pause.h"
#include "polygon.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "joypad.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define BACK_SIZE D3DXVECTOR3(200.0f,180.0f,0.0f)                  // �w�ʃT�C�Y
#define BACK_POS D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f) // �w�ʍ��W

#define STRING_SIZE D3DXVECTOR3(150.0f,50.0f,0.0f)                                  // ������
#define RESUME_POS  D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y - (STRING_SIZE.y + 25),0.0f) // ������
#define RESTART_POS D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y,0.0f)                        // ���X�^�[�g
#define EXIT_POS   	D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y + (STRING_SIZE.y + 25),0.0f) // �I��

#define MENU_ENTER_COL D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f)     // �I��ł郁�j���[�̐F
#define MENU_NOT_ENTER_COL D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) // �I��łȂ����j���[�̐F
//=======================================================================================
// �O���錾
//=======================================================================================
LPDIRECT3DTEXTURE9 CPause::m_apTexture[CPause::PARTS_MAX] = {};

//=======================================================================================
// 
//=======================================================================================
CPause::CPause()
{
	memset(&m_pPolygon, 0, sizeof(m_pPolygon));
	m_nMenu = RESUME;
}

//=======================================================================================
// 
//=======================================================================================
CPause::~CPause()
{

}

//=======================================================================================
// 
//=======================================================================================
CPause* CPause::Create(void)
{
	CPause* pPause = new CPause();

	pPause->Init();

	return pPause;
}

//=======================================================================================
// 
//=======================================================================================
HRESULT CPause::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_back.png"   , &m_apTexture[BACK]);
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_resume.png" , &m_apTexture[RESUME]);
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_restart.png", &m_apTexture[RESTART]);
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_exit.png" , &m_apTexture[EXIT]);

	return S_OK;
}
//=======================================================================================
// �e�N�X�`���̃A�����[�h
//=======================================================================================
void CPause::Unload(void)
{

	for (int nCntTex = 0; nCntTex < PARTS_MAX; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
//=======================================================================================
// 
//=======================================================================================
HRESULT CPause::Init(void)
{
	// �|���S������

	// ���̂��
	m_pPolygon[BACK] = CPolygon::Create(BACK_POS, BACK_SIZE);
	m_pPolygon[BACK]->BindTexture(m_apTexture[BACK]);
	// �ĊJ�̂��
	m_pPolygon[RESUME] = CPolygon::Create(RESUME_POS, STRING_SIZE);
	m_pPolygon[RESUME]->BindTexture(m_apTexture[RESUME]);
	// ���X�^�[�g�̂��
	m_pPolygon[RESTART] = CPolygon::Create(RESTART_POS, STRING_SIZE);
	m_pPolygon[RESTART]->BindTexture(m_apTexture[RESTART]);
	// EXIT�̂��
	m_pPolygon[EXIT] = CPolygon::Create(EXIT_POS, STRING_SIZE);
	m_pPolygon[EXIT]->BindTexture(m_apTexture[EXIT]);
	

	return S_OK;
}

//=======================================================================================
// 
//=======================================================================================
void CPause::Uninit(void)
{
	for (int nCntTex = 0; nCntTex < PARTS_MAX; nCntTex++)
	{
		if (m_pPolygon[nCntTex] != NULL)
		{
			//�I������
			m_pPolygon[nCntTex]->Uninit();
			// �������̉��
			delete m_pPolygon[nCntTex];
			m_pPolygon[nCntTex] = NULL;
		}
	}
}

//=======================================================================================
// 
//=======================================================================================
void CPause::Update(void)
{
	// �I��ł郁�j���[�ŐF����
	for (int nCntMenu = RESUME; nCntMenu < PARTS_MAX; nCntMenu++)
	{
		if (m_nMenu == nCntMenu)
		{// �I��ł�Ƃ�
			m_pPolygon[nCntMenu]->SetColor(MENU_ENTER_COL);
		}
		else
		{// �I��łȂ��Ƃ�
			m_pPolygon[nCntMenu]->SetColor(MENU_NOT_ENTER_COL);
		}
	}

	// ���j���[����
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_W) || CManager::GetKeyboard()->GetKeyTrigger(DIK_UP))
	{// ��
		m_nMenu--;
	}
	else if (CManager::GetKeyboard()->GetKeyTrigger(DIK_S) || CManager::GetKeyboard()->GetKeyTrigger(DIK_DOWN))
	{// ��
		m_nMenu++;
	}

	// �͈͊O�ɍs���Ȃ��悤��
	if (m_nMenu > EXIT)
	{
		m_nMenu = RESUME;
	}
	else if (m_nMenu < RESUME)
	{
		m_nMenu = EXIT;
	}

	// ���j���[�R�}���h
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		switch (m_nMenu)
		{
		case RESUME:
			// ������
			CManager::SetActivePause(false);
			break;
		case RESTART:
			// ���X�^�[�g
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
			break;
		case EXIT:
			// �I������
			DestroyWindow(FindWindow(WINDOW_CLASS_NAME, NULL));
			break;
		default:
			break;
		}
	}
}

//=======================================================================================
// 
//=======================================================================================
void CPause::Draw(void)
{
	for (int nCntPolygon = 0; nCntPolygon < PARTS_MAX; nCntPolygon++)
	{
		if (m_pPolygon[nCntPolygon] != NULL)
		{
			m_pPolygon[nCntPolygon]->Draw();
		}
	}
}