//=============================================================================
//
// player_flag_raicing���� [player_flag_raicing.cpp]
// Author : �R�c�@�ˑ�
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player_flag_raicing.h"
#include "flipper.h"
#include "flag_raicing_game_rule.h"
#include "add_point_display.h"
#include "manager.h"
#include "joypad.h"
#include "sound.h"
#include "keyboard.h"
#include "resource_texture.h"
#include "scene3d.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPlayerFlagRaicing::CPlayerFlagRaicing()
{
	m_pAddPointDisplay = NULL;
	m_bIsOldLeftJoyPad = false;
	m_bIsOldRightJoyPad = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPlayerFlagRaicing::~CPlayerFlagRaicing()
{
}

//=============================================================================
//�N���G�C�g����
//=============================================================================
CPlayerFlagRaicing * CPlayerFlagRaicing::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
	CPlayerFlagRaicing *pPlayerFlag = NULL;

	//�C���X�^���X����
	pPlayerFlag = new CPlayerFlagRaicing;

	if (pPlayerFlag)
	{
		pPlayerFlag->SetPlayerNumber(nPlayerNum);			//�ԍ��̐ݒ�
		pPlayerFlag->SetPos(pos);							//�ʒu�̐ݒ�
		pPlayerFlag->SetPriority(CScene::OBJTYPE_PLAYER);	//�`�揇��ݒ�
		pPlayerFlag->Init();								//������		

		//�@�e�̐���
		CScene3d * p3DPolygon = CScene3d::Create(D3DXVECTOR3(pos.x, pos.y + 1.0f, pos.z), PLAYER_SHADOW_SIZE);
		p3DPolygon->SetPriority(CScene::OBJTYPE_PARTICLE); // �v���C�I���e�B�̐ݒ�
		p3DPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PENGUIN_SHADOW));// �e�N�X�`��
		p3DPolygon->SetColor(PLAYER_SHADOW_COLOR);// �F
	}

	return pPlayerFlag;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CPlayerFlagRaicing::Init(void)
{
	CPlayer::Init();

	m_pAddPointDisplay = CAddPointDisplay::Create(GetPlayerNumber());

	m_bIsOldLeftJoyPad = false;
	m_bIsOldRightJoyPad = false;
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CPlayerFlagRaicing::Uninit(void)
{
	CPlayer::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CPlayerFlagRaicing::Update(void)
{
	CPlayer::Update();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CPlayerFlagRaicing::Draw(void)
{
	CPlayer::Draw();
}

//=============================================================================
//�H�̃R���g���[������
//=============================================================================
void CPlayerFlagRaicing::ControllFlipper(void)
{
#ifdef _DEBUG
	// �L�[�{�[�h����
	// �E�H�𑀍�
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_UP))
	{// �グ��
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_UP)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
		}

		// �ړ���Ԃ̍X�V
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);

		//�ύX�����������グ���[���N���X�֑���
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);

	}
	else if (CManager::GetKeyboard()->GetKeyTrigger(DIK_DOWN))
	{// ������
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_DOWN)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
		}

		// �ړ���Ԃ̍X�V
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);

		//�ύX�����������グ���[���N���X�֑���
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);

	}

	// ���H�𑀍�
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_W))
	{// �グ��
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_UP)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
		}

		// �ړ���Ԃ̍X�V
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);

		//�ύX�����������グ���[���N���X�֑���
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);

	}
	else if (CManager::GetKeyboard()->GetKeyTrigger(DIK_S))
	{// ������
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_DOWN)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
		}

		// �ړ���Ԃ̍X�V
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);

		//�ύX�����������グ���[���N���X�֑���
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
	}

#endif // _DEBUG

	// �R���g���[���[����
	// �E�H�𑀍�
	if (CManager::GetJoypad()->GetStick(GetPlayerNumber()).lRz <= -10)
	{// �グ��

		//�O��E�X�e�B�b�N���g�p���Ă��Ȃ����
		if (m_bIsOldRightJoyPad == false)
		{
			if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_UP)
			{
				// SE
				CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + GetPlayerNumber()));

				m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
			}

			// �ړ���Ԃ̍X�V
			m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);

			//�ύX�����������グ���[���N���X�֑���
			CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);

			//�E�X�e�B�b�N���g�p���Ă��邱�Ƃɂ���
			m_bIsOldRightJoyPad = true;
		}
	}
	else if (CManager::GetJoypad()->GetStick(GetPlayerNumber()).lRz >= 10)
	{// ������

		//�O��E�X�e�B�b�N���g�p���Ă��Ȃ����
		if (m_bIsOldRightJoyPad == false)
		{
			if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_DOWN)
			{
				// SE
				CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + GetPlayerNumber()));

				m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
			}
			// �ړ���Ԃ̍X�V
			m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);

			//�ύX�����������グ���[���N���X�֑���
			CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);

			//�E�X�e�B�b�N���g�p���Ă��邱�Ƃɂ���
			m_bIsOldRightJoyPad = true;
		}
	}
	else
	{
		m_bIsOldRightJoyPad = false;
	}

	// ���H�𑀍�
	if (CManager::GetJoypad()->GetStick(GetPlayerNumber()).lY <= -10)
	{// �グ��

		//�O�񍶃X�e�B�b�N���g�p���Ă��Ȃ����
		if (m_bIsOldLeftJoyPad == false)
		{
			if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_UP)
			{
				// SE
				CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + GetPlayerNumber()));

				m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
			}

			// �ړ���Ԃ̍X�V
			m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);

			//�ύX�����������グ���[���N���X�֑���
			CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);

			//���X�e�B�b�N���g�p���Ă��邱�Ƃɂ���
			m_bIsOldLeftJoyPad = true;
		}
	}
	else if (CManager::GetJoypad()->GetStick(GetPlayerNumber()).lY >= 10)
	{// ������

		//�O�񍶃X�e�B�b�N���g�p���Ă��Ȃ����
		if (m_bIsOldLeftJoyPad == false)
		{
			if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_DOWN)
			{
				// SE
				CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + GetPlayerNumber()));

				m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
			}

			// �ړ���Ԃ̍X�V
			m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);

			//�ύX�����������グ���[���N���X�֑���
			CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);

			//���X�e�B�b�N���g�p���Ă��邱�Ƃɂ���
			m_bIsOldLeftJoyPad = true;
		}
	}
	else
	{
		m_bIsOldLeftJoyPad = false;
	}
}