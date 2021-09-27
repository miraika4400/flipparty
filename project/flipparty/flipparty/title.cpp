////////////////////////////////////////////////////
//
//    �^�C�g���N���X�̏���[title.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//=============================
// �C���N���[�h
//=============================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "sound.h"
#include "resource_texture.h"
#include "count_selection.h"
#include "camera_base.h"
#include "sea.h"
#include "bg.h"
#include "iceberg.h"
#include "stage.h"
#include "rule_base.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//**********************************
// �}�N����`
//**********************************
#define OBJ_BACE_POS_Y 2000.0f
#define STAGE_SPACE 150.0f

//=============================
// �R���X�g���N�^
//=============================
CTitle::CTitle()
{
	m_pPolygon = NULL;
}

//=============================
// �f�X�g���N�^
//=============================
CTitle::~CTitle()
{
}

//=============================
// �N���G�C�g
//=============================
CTitle * CTitle::Create(void)
{
	// �������̊m��
	CTitle *pTitle = new CTitle;
	// ������
	pTitle->Init();
	return pTitle;
}

//=============================
// ����������
//=============================
HRESULT CTitle::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 200.0f, 0.0f),
		D3DXVECTOR3(400.0f, 200.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TITLE));
	
	// �l���I���N���X�̐���
	CCountSelect::Create();

	// �J�����̐���
	CManager::SetCamera(CCamera::Create());
	// �J�����̈ʒu����
	CManager::GetCamera()->SetPosV(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y + 150.0f, 500.0f));

	// �C�̐���
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y -24.0f, 0.0f), 0.001f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y -22.0f, 0.0f), 0.0025f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y -20.0f, 0.0f), 0.004f, CSea::TYPE_NORMAL);

	// �w�i
	CBg::Create();

	// �X�R�̐���
	CIceberg::Create(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y - 50.0f, -900.0f), CIceberg::ICEBERG_TYPE(rand() % CIceberg::ICEBERG_MAX));

	if (rand() % 2 == 0)
	{
		CStage::Create(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y, 0.0f), CStage::STAGE_TYPE_LARGE);
	}
	else
	{
		// �v���C���[�̐���
		// �����ʒuX���̒���
		float posX = 0 + ((float)(MAX_PLAYER_NUM - 1) * STAGE_SPACE) / 2;
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
		{
			// �X�e�[�W�̐���
			CStage::Create(D3DXVECTOR3(posX, OBJ_BACE_POS_Y, 0.0f), CStage::STAGE_TYPE_NORMAL);

			posX -= STAGE_SPACE;
		}
	}

	return S_OK;
}

//=============================
// �I������
//=============================
void CTitle::Uninit(void)
{
	// �J�����N���X�̉������
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		CManager::SetCamera(NULL);
		pCamera = NULL;
	}

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
void CTitle::Update(void)
{
	// �J�����N���X�̉������
	// �J�����N���X�X�V����
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Update();
	}


	// �|���S���̍X�V����
	m_pPolygon->Update();

	//if( CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) || 
	//	CManager::GetMouse()->GetMouseTrigger(0) || 
	//	CManager::GetJoypad()->GetJoystickTrigger(3, 0)||
	//	CManager::GetJoypad()->GetJoystickTrigger(11, 0))
	//{
	//	CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
	//}
}


//=============================
// �`�揈��
//=============================
void CTitle::Draw(void)
{
	// �J�����N���X�X�V����
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->SetCamera();
	}

	// �|���S���̕`�揈��
	m_pPolygon->Draw();
}
