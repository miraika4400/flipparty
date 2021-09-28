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
#include "resource_texture.h"
#include "scene3d.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPlayerFlagRaicing::CPlayerFlagRaicing()
{
	m_pAddPointDisplay = NULL;
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
//	//�O��̒l���擾
//	CFlipper::FLIPPER_STATE oldLeftFlipper = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT);
//	CFlipper::FLIPPER_STATE oldRightFlipper = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT);
//
	CPlayer::Update();

	////����̒l���擾
	//CFlipper::FLIPPER_STATE nowLeftFlipper = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT);
	//CFlipper::FLIPPER_STATE nowRightFlipper = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT);

	////����check
	//if (nowLeftFlipper != oldLeftFlipper)
	//{
	//	//�ύX�����������グ���[���N���X�֑���
	//	CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_LEFT, nowLeftFlipper);

	//}
	//if (nowRightFlipper != oldRightFlipper)
	//{
	//	//�ύX�����������グ���[���N���X�֑���
	//	CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_RIGHT, nowRightFlipper);
	//}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CPlayerFlagRaicing::Draw(void)
{
	CPlayer::Draw();
}

CAddPointDisplay *CPlayerFlagRaicing::GetAddPoitDisplay(void)
{
	return m_pAddPointDisplay;
}

