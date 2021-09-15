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
#include "rank_ui.h"
#include "tears_manager.h"
#include "rule_manager.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//**********************************
// �}�N����`
//**********************************
#define PLAYER_SPACE 150.0f //�@�v���C���[�ʒu�̊Ԋu
#define BLACKOUT_SIZE  D3DXVECTOR3(10000.0f, 10000.0f, 0.0f)
#define BLACKOUT_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f)
#define BLACKOUT_POS   D3DXVECTOR3(0.0f, 2000.0f, 50.0f)
#define PLAYER_RESULT_WORST_ROT_X D3DXToRadian(70.0f) // �ŉ��ʂ̎��̉�]����X�̒l
#define RANK_UI_HEGHT -50  // �����L���O��UI�v���C���[����̈ʒu

//=============================
// �R���X�g���N�^
//=============================
CMiniResult::CMiniResult():CScene(OBJTYPE_MINIRESULT_SYSTEM)
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
	// �J�����̐؂�ւ�
	CCamera * pCamera = CCamera::Create();
	// �J�����N���X�̐���
	CManager::SetCamera(pCamera);
	pCamera->SetCamera();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �w�i���Â�����悤
	CScene3d * p3DPolygon = CScene3d::Create(BLACKOUT_POS, BLACKOUT_SIZE);
	p3DPolygon->SetColor(BLACKOUT_COLOR);            //�F�̐ݒ�
	p3DPolygon->SetPriority(OBJTYPE_MINIRESULT_OBJ); // �v���C�I���e�B�̐ݒ�

	// �v���C���[���̎擾
	int nPlayNum = CCountSelect::GetPlayerNum();

	// �v���C���[�I�u�W�F�N�g�̎擾
	CPlayer *pPlayer = (CPlayer *)CScene::GetTop(CScene::OBJTYPE_PLAYER);

	if (pPlayer != NULL)
	{
		// �ŉ��ʂ̏���
		int nWorstRank = pPlayer->GetRank();
		for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
		{
			// �ŉ��ʂ̏���
			if (nWorstRank < pPlayer->GetRank())
			{
				nWorstRank = pPlayer->GetRank();
			}
			pPlayer = (CPlayer*)pPlayer->GetNext();
		}

		// �v���C���[���̏�����
		pPlayer = (CPlayer *)CScene::GetTop(CScene::OBJTYPE_PLAYER);

		// �����ʒuX���̒���
		float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
		for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
		{
			// �v���C���[�����ʒu
			D3DXVECTOR3 createPlayerPos = D3DXVECTOR3(posX, 2000.0f - PLAYER_CENTER_HEIGHT, 100.0f);

			// �v���C���[�̐���
			CPlayer * pResultPlayer = CPlayer::Create(createPlayerPos, nCntPlayer);
			// �I�u�W�F�N�g�^�C�v
			pResultPlayer->SetPriority(OBJTYPE_MINIRESULT_OBJ);
			// ����s��
			pResultPlayer->SetMoveFlag(false);

			// �J�����̕����ɑ̂�������
			D3DXVECTOR3 cemeraPos = CManager::GetCamera()->GetPos();
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
			else if (pPlayer->GetRank() == nWorstRank)
			{// �ŉ���
				pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_4);
				// �p�x�̒���
				pResultPlayer->SetPos(D3DXVECTOR3(createPlayerPos.x, createPlayerPos.y - 20, createPlayerPos.z));
				// �\��̐ݒ�
				pResultPlayer->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);
				pResultPlayer->Draw();
				D3DXVECTOR3 headPos;
				headPos.x = pResultPlayer->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._41;
				headPos.y = pResultPlayer->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._42;
				headPos.z = pResultPlayer->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._43 - 10;
				CTearsManager::Create(headPos);
			}
			else if (pPlayer->GetRank() == 1)
			{// ���
				pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_2);
			}
			else if (pPlayer->GetRank() == 2)
			{// �O��
				pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_3);
				// �\��̐ݒ�
				pResultPlayer->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);
			}

			// �����NUI�̐���
			CRankUI::Create(D3DXVECTOR3(createPlayerPos.x, createPlayerPos.y + RANK_UI_HEGHT, createPlayerPos.z), pPlayer->GetRank());

			// �ʒu�����炷
			posX -= PLAYER_SPACE;

			pPlayer = (CPlayer*)pPlayer->GetNext();
		}
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
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
		CManager::GetMouse()->GetMouseTrigger(0) ||
		CManager::GetJoypad()->GetJoystickTrigger(3, 0) ||
		CManager::GetJoypad()->GetJoystickTrigger(11, 0))
	{
		CGame::GetRuleManager()->TransitionRule();
	}
}


//=============================
// �`�揈��
//=============================
void CMiniResult::Draw(void)
{
	// �J�����̐؂�ւ�
	CCamera * pCamera = CCamera::Create();
	// �J�����N���X�̐���
	CManager::SetCamera(pCamera);
	pCamera->SetCamera();
}
