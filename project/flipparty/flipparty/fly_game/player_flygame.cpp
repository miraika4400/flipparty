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

//*****************************
// �}�N����`
//*****************************
#define FLY_HEIGHT 0.5f // ���̔���Ŕ�ԍ���
#define FLY_RATE 1.0f   // ��ԌW��

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************

//******************************
// �R���X�g���N�^
//******************************
CFlyGamePlayer::CFlyGamePlayer()
{
	m_fHeightDist = 0.0f;
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

	}

	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();
	pos.y += (m_fHeightDist - pos.y)*FLY_RATE;
	// ���W�̃Z�b�g
	SetPos(pos);
}
