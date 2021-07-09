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

	if (GetMoveFlag())
	{
		// �t���b�p�[�X�V�O�̈ړ����
		CFlipper::FLIPPER_STATE leftStateOld = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT);
		CFlipper::FLIPPER_STATE rightStateOld = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT);

		// �v���C���[�N���X�̍X�V����
		CPlayer::Update();

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

void CFlyGamePlayer::ManageState(void)
{
	switch (m_state)
	{
	case STATE_NORMAL:
		break;
	case STATE_STAN:

		if (m_nCntState == 0) 
		{
			SetMotion(MOTION_MINIRESULT_3);
			SetMoveFlag(false);
			SetFacePattern(FACE_PATTERN_NO_GOOD);
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
