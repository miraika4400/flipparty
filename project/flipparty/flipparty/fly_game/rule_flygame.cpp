////////////////////////////////////////////////////
//
//    �J�����N���X�̏���[camera.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "rule_flygame.h"
#include "count_selection.h"
#include "player.h"
#include "game.h"
#include "camera_flygame.h"
#include "light.h"

//******************************
// �}�N����`
//******************************
#define PLAYER_SPACE 150.0f

//******************************
// �ÓI�����o�ϐ��錾
//******************************

//******************************
// �R���X�g���N�^
//******************************
CRuleFly::CRuleFly()
{
	// �ϐ��̃N���A
}

//******************************
// �f�X�g���N�^
//******************************
CRuleFly::~CRuleFly()
{
}

//******************************
// �N���G�C�g
//******************************
CRuleFly * CRuleFly::Create(void)
{
	CRuleFly * pCamera = new CRuleFly;
	pCamera->Init();

	return pCamera;
}

//******************************
// ����������
//******************************
HRESULT CRuleFly::Init(void)
{
	// �J�����N���X�̐���
	CGame::SetCamera(CFlyGameCamera::Create());

	// �v���C���[���̎擾
	int nPlayNum = CCountSelect::GetPlayerNum();
	
	// �v���C���[�̐���
	// �����ʒuX���̒���
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		CPlayer::Create(D3DXVECTOR3(posX, 0.0f, 0.0f), nCntPlayer);
		posX -= PLAYER_SPACE;
	}

	return S_OK;
}

//******************************
// ����������
//******************************
void CRuleFly::Uninit(void)
{

}

//******************************
// �X�V����
//******************************
void CRuleFly::Update(void)
{
}
