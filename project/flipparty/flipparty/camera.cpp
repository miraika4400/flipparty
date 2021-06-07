////////////////////////////////////////////////////
//
//    �J�����N���X�̏���[camera.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "mouse.h"
#include "joypad.h"

//******************************
// �}�N����`
//******************************
#define CAMERA_DISTANCE 850.0f                               // �J�����ƑΏۂ̋���
#define CAMERA_VIEW_MAX 100000.0f                            // �J�����̕`�拗��(��)
#define CAMERA_VIEW_MIN 10.0f                                // �J�����̕`�拗��(��)
#define CAMERA_FOV_BASE D3DXToRadian(45.0f)                  // ����p
#define CAMERA_FOV_RATE 0.05f                                // ����p�ω����̌W��
#define CAMERA_MOVE_SPEED_MAX 0.04f                          // �J�������슴�x�ő�l
#define DAMERA_THETA_RATE 0.05f                              // �J�����̃V�[�^�������̌W��
#define CAMERA_THETA_BASE D3DXToRadian(75.0f)                // �J�����̃t�@�C(����)�̊�{�p�x
#define DAMERA_PHI_RATE 0.01f                                // �J�����̃t�@�C(����)�������̌W��
#define THETA_DIFFERENCE D3DXToRadian(60)                    // �V�[�^�ƃV�[�^�̖ڕW�l�̍��̍ő�

// CPU�ɒǏ]�ւ���ɐ؂�ւ���}�N��
#define CPU_CAMERA
//#undef  CPU_CAMERA

//******************************
// �ÓI�����o�ϐ��錾
//******************************
CCamera*CCamera::m_pCamera = NULL;

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


	m_fRad   = 0.0f; // �ڕW����̋���
	m_fTheta = 0.0f; // �p�x�V�[�^
	m_fPhi   = 0.0f; // �p�x�t�@�C
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

	m_pCamera = new CCamera;
	m_pCamera->Init();


	return m_pCamera;
}


//******************************
// ����������
//******************************
HRESULT CCamera::Init(void)
{
	// �ϐ��̏�����

	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // �����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);      // ������x�N�g��

	m_fRad = CAMERA_DISTANCE;     // ����
	m_fTheta = D3DXToRadian(90);  // �p�x�V�[�^
	m_fPhi = CAMERA_THETA_BASE;   // �p�x�t�@�C

	// ���ʍ��W�̐ݒ�
	m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
	m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
	m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);

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
	m_fTheta -= CManager::GetMouse()->GetMouseMove().x;
	m_fPhi -= CManager::GetMouse()->GetMouseMove().y;

	// ���ʍ��W�̐ݒ�
	m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
	m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
	m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);
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
	D3DXMatrixIdentity(&m_pCamera->m_mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_pCamera->m_mtxView, &m_pCamera->m_posV, &m_pCamera->m_posR, &m_pCamera->m_vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_pCamera->m_mtxView);

	//�v���W�F�N�g�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_pCamera->m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_pCamera->m_mtxProjection,
		m_fFov, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, CAMERA_VIEW_MIN, CAMERA_VIEW_MAX);
	
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera->m_mtxProjection);
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 1.0f, 0);
}