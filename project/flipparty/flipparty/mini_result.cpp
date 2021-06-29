////////////////////////////////////////////////////
//
//    �~�j�Q�[�����U���g�N���X�̏���[mini_result.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//=============================
// �C���N���[�h
//=============================
#include "mini_result.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "sound.h"
#include "game.h"
#include "camera_base.h"
#include "count_selection.h"
#include "player.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//**********************************
// �}�N����`
//**********************************
#define PLAYER_SPACE 150.0f //�@�v���C���[�ʒu�̊Ԋu
#define BLACKOUT_SIZE  D3DXVECTOR3(10000.0f, 10000.0f, 0.0f)
#define BLACKOUT_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f)
#define BLACKOUT_POS   D3DXVECTOR3(0.0f, 0.0f, 50.0f)
#define LIGHT_DIR     

//=============================
// �R���X�g���N�^
//=============================
CMiniResult::CMiniResult():CScene(OBJTYPE_MINIRESULT)
{
}

//=============================
// �f�X�g���N�^
//=============================
CMiniResult::~CMiniResult()
{
}

//=============================
// �N���G�C�g
//=============================
CMiniResult * CMiniResult::Create(void)
{
	// �������̊m��
	CMiniResult *pMiniResult = new CMiniResult;
	// ������
	pMiniResult->Init();
	return pMiniResult;
}

//=============================
// ����������
//=============================
HRESULT CMiniResult::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �w�i���Â�����悤
	CScene3d * p3DPolygon = CScene3d::Create(BLACKOUT_POS, BLACKOUT_SIZE);
	p3DPolygon -> SetColor(BLACKOUT_COLOR);      //�F�̐ݒ�
	p3DPolygon->SetPriority(OBJTYPE_MINIRESULT); // �v���C�I���e�B�̐ݒ�

	// �v���C���[���̎擾
	int nPlayNum = CCountSelect::GetPlayerNum();

	// �v���C���[�I�u�W�F�N�g�̎擾
	CPlayer *pPlayer = (CPlayer *)CScene::GetTop(CScene::OBJTYPE_PLAYER);

	// �ŉ��ʂ̏���
	int nWorstRank = pPlayer->GetRank();

	// �����ʒuX���̒���
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		// �ŉ��ʂ̏���
		if (nWorstRank < pPlayer->GetRank())
		{
			nWorstRank = pPlayer->GetRank();
		}

		// �v���C���[�����ʒu
		D3DXVECTOR3 createPlayerPos = D3DXVECTOR3(posX, -PLAYER_CENTER_HEIGHT, 100.0f);
		// �v���C���[�̐���
		CPlayer * pResultPlayer = CPlayer::Create(createPlayerPos, nCntPlayer);
		// �I�u�W�F�N�g�^�C�v
		pResultPlayer->SetPriority(OBJTYPE_MINIRESULT);
		// ����s��
		pResultPlayer->SetMoveFlag(false);

		// �J�����̕����ɑ̂�������
		D3DXVECTOR3 cemeraPos = CGame::GetCamera()->GetPos();
		float fRotY = atan2f(createPlayerPos.x - cemeraPos.x, createPlayerPos.z - cemeraPos.z);

		// �p�x�̒���
		pResultPlayer->SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));

		// ���[�V�����̕���
		if (pPlayer->GetRank() == 0)
		{// ���
			pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_1);
			// �\��̐ݒ�
			pResultPlayer->SetFacePattern(CPlayer::FACE_PATTERN_GOOD);
		}
		else if(pPlayer->GetRank() == nWorstRank)
		{// �ŉ���
			pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_4);
			// �p�x�̒���
			pResultPlayer->SetRot(D3DXVECTOR3(D3DXToRadian(90.0f), fRotY, 0.0f));
			// �\��̐ݒ�
			pResultPlayer->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);
		}
		else if (pPlayer->GetRank() == 1)
		{// ���
			pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_2);
		}
		else if (pPlayer->GetRank() == 2)
		{// �ŉ���
			pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_3);
			// �\��̐ݒ�
			pResultPlayer->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);
		}

		// �ʒu�����炷
		posX -= PLAYER_SPACE;

		pPlayer = (CPlayer *)pPlayer->GetNext();
	}

	return S_OK;
}

//=============================
// �I������
//=============================
void CMiniResult::Uninit(void)
{
	// �J������
	Release();
}


//=============================
// �X�V����
//=============================
void CMiniResult::Update(void)
{

}


//=============================
// �`�揈��
//=============================
void CMiniResult::Draw(void)
{
	// �J�����̐؂�ւ�
	CCamera * pCamera = CCamera::Create();
	// �J�����N���X�̐���
	CGame::SetCamera(pCamera);
	pCamera->SetCamera();

}
