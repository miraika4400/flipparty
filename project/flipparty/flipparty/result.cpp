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
#include "camera_base.h"
#include "player.h"
#include "bg.h"
#include "count_selection.h"
#include "tears_manager.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//**********************************
// �}�N����`
//**********************************
#define PLAYER_SPACE 150.0f //�@�v���C���[�ʒu�̊Ԋu
#define PLAYER_POS_Z 100.0f // �v���C���[��Z�ʒu
#define PLAYER_FALL_COUNT 100 // �v���C���[��������J�E���g��

//=============================
// �R���X�g���N�^
//=============================
CResult::CResult()
{
	m_pPolygon = NULL;
	ZeroMemory(&m_apPlayer, sizeof(m_apPlayer));
	m_nCntFallTime = 0;
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
	//// �J�����N���X�̐���
	CManager::SetCamera(CCamera::Create());
	//m_pCamera = CGame::GetCamera();

	// �w�i�̐���
	CBg::Create();

	// �v���C���[���̎擾
	int nPlayNum = CCountSelect::GetPlayerNum();

	// �v���C���[�̐���
	// �����ʒuX���̒���
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		m_apPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(posX, -PLAYER_CENTER_HEIGHT, PLAYER_POS_Z), nCntPlayer);

		// �J�����̕����ɑ̂�������
		D3DXVECTOR3 cemeraPos = CManager::GetCamera()->GetPos();
		float fRotY = atan2f(posX - cemeraPos.x, PLAYER_POS_Z - cemeraPos.z);

		// �p�x�̒���
		m_apPlayer[nCntPlayer]->SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));
		
		// ����t���Ofalse
		m_apPlayer[nCntPlayer]->SetMoveFlag(false);

		posX -= PLAYER_SPACE;
	}

	// �J�E���g�̏�����
	m_nCntFallTime = 0;

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
void CResult::Update(void)
{

	// �J�����N���X�̍X�Vv����
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Update();
	}

	if (m_pPolygon != NULL)
	{
		// �|���S���̍X�V����
		m_pPolygon->Update();
	}

	//// �J�E���g��i�߂�
	//m_nCntFallTime++;
	//if (PLAYER_FALL_COUNT <= m_nCntFallTime)
	//{// ���̃J�E���g��
	//	// �J�E���g�̃��Z�b�g
	//	m_nCntFallTime = 0;
	//	// �v���C���[���̎擾
	//	int nPlayNum = CCountSelect::GetPlayerNum();
	//
	//	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	//	{
	//		// �R�P�郂�[�V�����̍Đ�
	//		m_apPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_FALL);
	//
	//		D3DXVECTOR3 headPos;
	//		headPos.x = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._41;
	//		headPos.y = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._42;
	//		headPos.z = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._43 - 10;
	//		CTearsManager::Create(headPos);
	//	}
	//}

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
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->SetCamera();
	}

	if (m_pPolygon != NULL)
	{
		// �|���S���̕`�揈��
		m_pPolygon->Draw();
	}
}
