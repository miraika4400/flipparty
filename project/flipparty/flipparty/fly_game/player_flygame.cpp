////////////////////////////////////////////////////
//
//    particle�N���X�̏���[particle.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "player_flygame.h"
#include "rule_flygame.h"
#include "manager.h"
#include "keyboard.h"
#include "joypad.h"
#include "sound.h"

//*****************************
// �}�N����`
//*****************************
#define FLY_HEIGHT 0.5f // ���̔���Ŕ�ԍ���
#define FLY_RATE 1.0f   // ��ԌW��
#define STAN_FLANE 100  // �X�^���t���[����

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************

//******************************
// �R���X�g���N�^
//******************************
CFlyGamePlayer::CFlyGamePlayer()
{
	m_fHeightDist = 0.0f;
	m_state = STATE_NORMAL;
	m_nCntState = 0;
}

//******************************
// �f�X�g���N�^
//******************************
CFlyGamePlayer::~CFlyGamePlayer()
{
}

//******************************
// �N���G�C�g
//******************************
CFlyGamePlayer * CFlyGamePlayer::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
	// �������̊m��
	CFlyGamePlayer *pPlayer;
	pPlayer = new CFlyGamePlayer;

	// �v���C���[�ԍ��̃Z�b�g
	pPlayer->SetPlayerNumber(nPlayerNum);

	// ������
	pPlayer->Init();

	// �e�l�̑���E�Z�b�g
	pPlayer->SetPos(pos);
	pPlayer->SetPriority(OBJTYPE_PLAYER); // �I�u�W�F�N�g�^�C�v
	pPlayer->m_fHeightDist = pos.y;

	return pPlayer;
}

//******************************
// ����������
//******************************
HRESULT CFlyGamePlayer::Init(void)
{
	CPlayer::Init();

	// ��ԏ�����
	m_state = STATE_NORMAL;
	m_nCntState = 0;

	SetFacePattern(FACE_PATTERN_GOOD);
	return S_OK;
}

//******************************
// �I������
//******************************
void CFlyGamePlayer::Uninit(void)
{
	CPlayer::Uninit();
}

//******************************
// �X�V����
//******************************
void CFlyGamePlayer::Update(void)
{
	// ��ԊǗ�
	ManageState();

	// �t���b�p�[�X�V�O�̈ړ����
	CFlipper::FLIPPER_STATE leftStateOld = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT);
	CFlipper::FLIPPER_STATE rightStateOld = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT);

	// �v���C���[�N���X�̍X�V����
	CPlayer::Update();

	if (GetMoveFlag())
	{
		// ��ԏ���
		Fly(GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT), leftStateOld);
		Fly(GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT), rightStateOld);
	}
}

//******************************
// �`�揈��
//******************************
void CFlyGamePlayer::Draw(void)
{
	CPlayer::Draw();
}

//******************************
// ��ԏ���
//******************************
void CFlyGamePlayer::Fly(CFlipper::FLIPPER_STATE stateNow, CFlipper::FLIPPER_STATE stateOld)
{
	if (stateNow != stateOld)
	{
		// �����Ƀv���X
		m_fHeightDist += FLY_HEIGHT;

		SetMotion(MOTION_FLY);
		SetFacePattern(FACE_PATTERN_NORMAL);
	}

	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();
	pos.y += (m_fHeightDist - pos.y)*FLY_RATE;
	// ���W�̃Z�b�g
	SetPos(pos);
}

//******************************
// ��ԊǗ�
//******************************
void CFlyGamePlayer::ManageState(void)
{
	switch (m_state)
	{
	case STATE_NORMAL:
		break;
	case STATE_STAN:

		if (m_nCntState == 0) 
		{
			SetMotion(MOTION_THUNDER);
			SetMoveFlag(false);
			SetFacePattern(FACE_PATTERN_NO_GOOD);

			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_STAN1) + GetPlayerNumber()));
		}

		m_nCntState++;
		if (m_nCntState >= STAN_FLANE)
		{
			m_nCntState = 0;
			m_state = STATE_NORMAL;
			SetMotion(MOTION_FLY);
			SetMoveFlag(CRuleFly::GetPlayFlag());
			SetFacePattern(FACE_PATTERN_NORMAL);
		}
		break;

	default:
		break;
	}
}

////******************************
//// �H�̑��쏈��
////******************************
//void CFlyGamePlayer::ControllFlipper(void)
//{
//
//#ifdef _DEBUG
//	// �L�[�{�[�h����
//	// �E�H�𑀍�
//	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_A))
//	{
//		if (GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT) == CFlipper::FLIPPERSTATE_DOWN)
//		{// �グ��
//			SetFlipperDist(CFlipper::FLIPPER_TYPE_RIGHT, RIGHT_FLIPPER_DIST_ANGLE_UP);
//
//			// �ړ���Ԃ̍X�V
//			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
//		}
//		else
//		{// ������
//			SetFlipperDist(CFlipper::FLIPPER_TYPE_RIGHT, RIGHT_FLIPPER_DIST_ANGLE_DOWN);
//
//			// �ړ���Ԃ̍X�V
//			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
//		}
//	}
//
//	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_D))
//	{
//		if (GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT) == CFlipper::FLIPPERSTATE_DOWN)
//		{// �グ��
//			SetFlipperDist(CFlipper::FLIPPER_TYPE_LEFT, LEFT_FLIPPER_DIST_ANGLE_UP);
//
//			// �ړ���Ԃ̍X�V
//			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
//		}
//		else
//		{// ������
//			SetFlipperDist(CFlipper::FLIPPER_TYPE_LEFT, LEFT_FLIPPER_DIST_ANGLE_DOWN);
//
//			// �ړ���Ԃ̍X�V
//			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
//		}
//	}
//
//#endif // _DEBUG
//	// �R���g���[���[����
//
//	// �v���C���[�ԍ��̎擾
//	int nPlayerNum = GetPlayerNumber();
//	// �E�H�𑀍�
//	if (CManager::GetJoypad()->GetJoystickTrigger(5, nPlayerNum))
//	{
//		if (GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT) == CFlipper::FLIPPERSTATE_DOWN)
//		{
//			// �グ��
//			SetFlipperDist(CFlipper::FLIPPER_TYPE_RIGHT, RIGHT_FLIPPER_DIST_ANGLE_UP);
//
//			// �ړ���Ԃ̍X�V
//			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
//		}
//		else
//		{// ������
//			SetFlipperDist(CFlipper::FLIPPER_TYPE_RIGHT, RIGHT_FLIPPER_DIST_ANGLE_DOWN);
//
//			// �ړ���Ԃ̍X�V
//			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
//		}
//	}
//
//	// ���H�𑀍�
//	if (CManager::GetJoypad()->GetJoystickTrigger(4, nPlayerNum))
//	{
//		if (GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT) == CFlipper::FLIPPERSTATE_DOWN)
//		{// �グ��
//			SetFlipperDist(CFlipper::FLIPPER_TYPE_LEFT, LEFT_FLIPPER_DIST_ANGLE_UP);
//
//			// �ړ���Ԃ̍X�V
//			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
//		}
//		else
//		{// ������
//			SetFlipperDist(CFlipper::FLIPPER_TYPE_LEFT, LEFT_FLIPPER_DIST_ANGLE_DOWN);
//
//			// �ړ���Ԃ̍X�V
//			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
//		}
//	}
//}
