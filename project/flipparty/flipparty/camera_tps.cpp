////////////////////////////////////////////////////
//
//    �J�����N���X�̏���[camera.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "camera_tps.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "mouse.h"
#include "joypad.h"

//******************************
// �}�N����`
//******************************
#define CAMERA_DISTANCE 200.0f                               // �J�����ƑΏۂ̋���
#define CAMERA_THETA_BASE D3DXToRadian(75.0f)                // �J�����̃t�@�C(����)�̊�{�p�x

//******************************
// �ÓI�����o�ϐ��錾
//******************************

//******************************
// �R���X�g���N�^
//******************************
CTpsCamera::CTpsCamera()
{
	m_fRad   = 0.0f; // �ڕW����̋���
	m_fTheta = 0.0f; // �p�x�V�[�^
	m_fPhi   = 0.0f; // �p�x�t�@�C
}

//******************************
// �f�X�g���N�^
//******************************
CTpsCamera::~CTpsCamera()
{
}

//******************************
// �N���G�C�g
//******************************
CTpsCamera * CTpsCamera::Create(void)
{
	CTpsCamera * pCamera = new CTpsCamera;
	pCamera->Init();

	return pCamera;
}


//******************************
// ����������
//******************************
HRESULT CTpsCamera::Init(void)
{
	// �J�����N���X�̏�����
	CCamera::Init();

	// �ϐ��̏�����
	m_fRad = CAMERA_DISTANCE;     // ����
	m_fTheta = D3DXToRadian(90);  // �p�x�V�[�^
	m_fPhi = CAMERA_THETA_BASE;   // �p�x�t�@�C
	
	// ���ʍ��W�̐ݒ�
	m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
	m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
	m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);
	return S_OK;
}

//******************************
// �X�V����
//******************************
void CTpsCamera::Update(void)
{
	m_fTheta -= CManager::GetMouse()->GetMouseMove().x;
	m_fPhi -= CManager::GetMouse()->GetMouseMove().y;
	
	// ���ʍ��W�̐ݒ�
	m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
	m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
	m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);
}