////////////////////////////////////////////////////
//
//    �J�����N���X�̏���[camera.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "camera_flygame.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "mouse.h"
#include "joypad.h"

//******************************
// �}�N����`
//******************************
#define CAMERA_POS D3DXVECTOR3(0.0f,0.0f, 500.0f)

//******************************
// �ÓI�����o�ϐ��錾
//******************************

//******************************
// �R���X�g���N�^
//******************************
CFlyGameCamera::CFlyGameCamera()
{
	// �ϐ��̃N���A
}

//******************************
// �f�X�g���N�^
//******************************
CFlyGameCamera::~CFlyGameCamera()
{
}

//******************************
// �N���G�C�g
//******************************
CFlyGameCamera * CFlyGameCamera::Create(void)
{
	CFlyGameCamera * pCamera = new CFlyGameCamera;
	pCamera->Init();

	return pCamera;
}


//******************************
// ����������
//******************************
HRESULT CFlyGameCamera::Init(void)
{
	CCamera::Init();

	// �ʒu�̐ݒ�
	m_posV = CAMERA_POS;

	m_posR = D3DXVECTOR3(0.0f, 150.0f, 0.0f);
	return S_OK;
}

//******************************
// �X�V����
//******************************
void CFlyGameCamera::Update(void)
{
}

//******************************
// �J�����̃Z�b�g
//******************************
void CFlyGameCamera::SetCamera(void)
{
	CCamera::SetCamera();

	//// �f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//D3DXMATRIXA16 matWorld;
	//
	////�r���[�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(GetViewMtx());
	////�r���[�}�g���b�N�X�̍쐬
	//D3DXMatrixLookAtLH(GetViewMtx(), &this->m_posV, &this->m_posR, &this->m_vecU);
	////�r���[�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_VIEW, GetViewMtx());
	//
	////�v���W�F�N�g�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(GetProjectionMtx());
	//
	////�v���W�F�N�V�����}�g���b�N�X�̍쐬*���s���e
	//D3DXMatrixOrthoLH(GetProjectionMtx(), ((float)SCREEN_WIDTH)*0.5f, ((float)SCREEN_HEIGHT)*0.5f, 10, 100000);
	//
	////�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_PROJECTION, GetProjectionMtx());
	//pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 1.0f, 0);
}