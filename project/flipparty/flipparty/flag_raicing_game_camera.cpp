////////////////////////////////////////////////////
//
//    �J�����N���X�̏���[camera.cpp]
//    Author:���� �r�H
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "flag_raicing_game_camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "mouse.h"
#include "joypad.h"

//******************************
// �}�N����`
//******************************
#define CAMERA_POS_V D3DXVECTOR3(0.0f, 0.0f, 250.0f)  // �ʒu
#define CAMERA_POS_R D3DXVECTOR3(0.0f, 0.0f, 0.0f) // �����_
//******************************
// �ÓI�����o�ϐ��錾
//******************************

//******************************
// �R���X�g���N�^
//******************************
CFlagRaicingGameCamera::CFlagRaicingGameCamera()
{
	// �ϐ��̃N���A
}

//******************************
// �f�X�g���N�^
//******************************
CFlagRaicingGameCamera::~CFlagRaicingGameCamera()
{
}

//******************************
// �N���G�C�g
//******************************
CFlagRaicingGameCamera * CFlagRaicingGameCamera::Create(void)
{
	CFlagRaicingGameCamera * pCamera = new CFlagRaicingGameCamera;
	pCamera->Init();

	return pCamera;
}


//******************************
// ����������
//******************************
HRESULT CFlagRaicingGameCamera::Init(void)
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
void CFlagRaicingGameCamera::Update(void)
{
}

//******************************
// �J�����̃Z�b�g
//******************************
void CFlagRaicingGameCamera::SetCamera(void)
{
	CCamera::SetCamera();
}