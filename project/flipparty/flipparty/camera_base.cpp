////////////////////////////////////////////////////
//
//    �J�����N���X�̏���[camera.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "camera_base.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "mouse.h"
#include "joypad.h"

//******************************
// �}�N����`
//******************************
#define CAMERA_INIT_POS D3DXVECTOR3(0.0f,0.0f,0.0f)
#define CAMERA_VIEW_MAX 100000.0f                            // �J�����̕`�拗��(��)
#define CAMERA_VIEW_MIN 10.0f                                // �J�����̕`�拗��(��)
#define CAMERA_FOV_BASE D3DXToRadian(45.0f)                  // ����p

//******************************
// �ÓI�����o�ϐ��錾
//******************************

//******************************
// �R���X�g���N�^
//******************************
CCamera::CCamera()
{
	// �ϐ��̃N���A
	m_posV = { 0.0f,0.0f,0.0f };
	m_posR = { 0.0f,0.0f,0.0f };
	m_vecU = { 0.0f,0.0f,0.0f };
	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixIdentity(&m_mtxView);
	m_fFov = 0.0f;
}

//******************************
// �f�X�g���N�^
//******************************
CCamera::~CCamera()
{
}

//******************************
// �N���G�C�g
//******************************
CCamera * CCamera::Create(void)
{
	CCamera * pCamera = new CCamera;
	pCamera->Init();

	return pCamera;
}


//******************************
// ����������
//******************************
HRESULT CCamera::Init(void)
{
	// �ϐ��̏�����

	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // �����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);      // ������x�N�g��
	m_posV = CAMERA_INIT_POS; // �ʒu

	m_fFov = CAMERA_FOV_BASE; //����p

	return S_OK;
}

//******************************
// �I������
//******************************
void CCamera::Uninit(void)
{
	delete this;
}

//******************************
// �X�V����
//******************************
void CCamera::Update(void)
{
}

//******************************
// �J�����̃Z�b�g
//******************************
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIXA16 matWorld;

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&this->m_mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&this->m_mtxView, &this->m_posV, &this->m_posR, &this->m_vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &this->m_mtxView);

	//�v���W�F�N�g�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&this->m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&this->m_mtxProjection,
		m_fFov, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, CAMERA_VIEW_MIN, CAMERA_VIEW_MAX);
	
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &this->m_mtxProjection);
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 1.0f, 0);
}