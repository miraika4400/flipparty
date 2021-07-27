////////////////////////////////////////////////////
//
//    ���U���g�N���X�̏���[result.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//=============================
// �C���N���[�h
//=============================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "score.h"
#include "camera_base.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//**********************************
// �}�N����`
//**********************************

//=============================
// �R���X�g���N�^
//=============================
CResult::CResult()
{
	m_pPolygon = NULL;
}

//=============================
// �f�X�g���N�^
//=============================
CResult::~CResult()
{
}

//=============================
// �N���G�C�g
//=============================
CResult * CResult::Create(void)
{
	// �������̊m��
	CResult *pResult = new CResult;
	// ������
	pResult->Init();
	return pResult;
}

//=============================
// ����������
//=============================
HRESULT CResult::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	/*m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));*/

	//m_pPolygon->BindTexture();
	
	return S_OK;
}

//=============================
// �I������
//=============================
void CResult::Uninit(void)
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
void CResult::Update(void)
{
	if (m_pPolygon != NULL)
	{
		// �|���S���̍X�V����
		m_pPolygon->Update();
	}

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) || 
		CManager::GetMouse()->GetMouseTrigger(0) || 
		CManager::GetJoypad()->GetJoystickTrigger(3, 0))
	{
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
	}
}


//=============================
// �`�揈��
//=============================
void CResult::Draw(void)
{
	if (m_pPolygon != NULL)
	{
		// �|���S���̕`�揈��
		m_pPolygon->Draw();
	}
}
