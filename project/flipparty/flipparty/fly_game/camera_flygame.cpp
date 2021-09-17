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
#include "player_flygame.h"
#include "rule_flygame.h"

//******************************
// �}�N����`
//******************************
#define CAMERA_POS_V D3DXVECTOR3(0.0f, 50.0f, 500.0f) // �ʒu
#define CAMERA_POS_R D3DXVECTOR3(0.0f, 100.0f, 0.0f)  // �����_

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
	D3DXVECTOR3 playerPos = CRuleFly::GetPlayer(0)->GetPos();

	for (int nCntPlayer = 1; nCntPlayer > MAX_PLAYER_NUM; nCntPlayer++)
	{
		if (playerPos.y < CRuleFly::GetPlayer(nCntPlayer)->GetPos().y)
		{
			playerPos = CRuleFly::GetPlayer(nCntPlayer)->GetPos();
		}
	}

	m_posR.y += ((playerPos.y + CAMERA_POS_R.y)- m_posR.y)*0.05f;
}