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
#define CAMERA_POS_V D3DXVECTOR3(0.0f,0.0f, 500.0f)  // �ʒu
#define CAMERA_POS_R D3DXVECTOR3(0.0f, 150.0f, 0.0f) // �����_

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
	m_posV = CAMERA_POS_V;

	m_posR = CAMERA_POS_R;
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
}