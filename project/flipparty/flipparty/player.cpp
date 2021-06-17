////////////////////////////////////////////////////
//
//    particle�N���X�̏���[particle.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "game.h"
#include "flipper.h"
#include "polygon.h"
#include "resource_texture.h"

//*****************************
// �}�N����`
//*****************************
#define HIERARCHY_TEXT_PATH1 "./data/Texts/hierarchy/pengin00.txt"    //�K�w�\���e�L�X�g�̃p�X
#define RIGHT_FLIPPER_PARTS_NUM 5 // �E�H�̃p�[�c�ԍ�
#define LEFT_FLIPPER_PARTS_NUM  4 // ���H�̃p�[�c�ԍ�
#define RIGHT_FLIPPER_DIST_ANGLE_UP   D3DXToRadian(-60.0f)
#define RIGHT_FLIPPER_DIST_ANGLE_DOWN D3DXToRadian(30.0f)
#define LEFT_FLIPPER_DIST_ANGLE_UP    -RIGHT_FLIPPER_DIST_ANGLE_UP
#define LEFT_FLIPPER_DIST_ANGLE_DOWN  -RIGHT_FLIPPER_DIST_ANGLE_DOWN
#define FLIPPER_RATE 0.07f // �H�𓮂����Ƃ��̌W��
#define FLIPPER_JUDGE D3DXToRadian(20.0f) // �オ���Ă��邩�������Ă��邩����̊�l

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CResourceModel::Model CPlayer::m_model[MAX_PARTS_NUM] = {};
int CPlayer::m_nPartsNum = 0;

//******************************
// �R���X�g���N�^
//******************************
CPlayer::CPlayer() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// �ϐ��̃N���A
	m_pFlieer = NULL;
	m_nPlayerNum = 0;                  // �v���C���[�ԍ�
	ZeroMemory(&m_fFlipperDist, sizeof(m_fFlipperDist)); // �H�̊p�x �ڕW�l

#ifdef _DEBUG
	// �f�o�b�O�p�ϐ�
	ZeroMemory(&m_pPolygon, sizeof(m_pPolygon));// �|���S���N���X�̃|�C���^
#endif // _DEBUG
}

//******************************
// �f�X�g���N�^
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// �N���G�C�g
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
	// �������̊m��
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->m_nPlayerNum = nPlayerNum;
	
	// ������
	pPlayer->Init();

	// �e�l�̑���E�Z�b�g
	pPlayer->SetPos(pos);
	pPlayer->SetPriority(OBJTYPE_PLAYER); // �I�u�W�F�N�g�^�C�v

	return pPlayer;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CPlayer::Load(void)
{

	// ���f���̓ǂݍ���
	LoadModels(HIERARCHY_TEXT_PATH1, &m_model[0], &m_nPartsNum);

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CPlayer::Unload(void)
{

	for (int nCnt = 0; nCnt < m_nPartsNum; nCnt++)
	{
		//���b�V���̔j��
		if (m_model[nCnt].pMesh != NULL)
		{
			m_model[nCnt].pMesh->Release();
			m_model[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (m_model[nCnt].pBuffMat != NULL)
		{
			m_model[nCnt].pBuffMat->Release();
			m_model[nCnt].pBuffMat = NULL;
		}
	}
}


//******************************
// ����������
//******************************
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nPartsNum, &m_model[0], HIERARCHY_TEXT_PATH1)))
	{
		return E_FAIL;
	}

	m_pFlieer = CFlipper::Create();

	// �H�̖ڕW�p�x�̏�����
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = 0.0f;
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = 0.0f;



#ifdef _DEBUG
	// �f�o�b�O�p
	m_pPolygon[CFlipper::FLIPPER_TYPE_LEFT] = CPolygon::Create(D3DXVECTOR3(50.0f, 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));// �|���S���N���X�̃|�C���^
	m_pPolygon[CFlipper::FLIPPER_TYPE_RIGHT] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH - 50.0f, 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));// �|���S���N���X�̃|�C���^
#endif // _DEBU
	return S_OK;
}

//******************************
// �I������
//******************************
void CPlayer::Uninit(void)
{
	CModelHierarchy::Uninit();

	// �t���b�p�[�N���X�̏I������
	if (m_pFlieer != NULL)
	{
		m_pFlieer->Uninit();
		m_pFlieer = NULL;
	}

#ifdef _DEBUG
	for (int nCntPolygon = 0; nCntPolygon < 2; nCntPolygon++)
	{
		if (m_pPolygon[nCntPolygon] != NULL)
		{			  
			m_pPolygon[nCntPolygon]->Uninit();
			delete m_pPolygon[nCntPolygon];
			m_pPolygon[nCntPolygon] = NULL;
		}
	}
#endif // _DEBU
}

//******************************
// �X�V����
//******************************
void CPlayer::Update(void)
{
	// �H�𓮂���
	ControllFlipper();

#ifdef _DEBUG

	for (int nCntPolygon = 0; nCntPolygon < 2; nCntPolygon++)
	{
		CFlipper::FLIPPER_STATE flipperState = m_pFlieer->GetState((CFlipper::FLIPPER_TYPE)nCntPolygon);

		switch (flipperState)
		{
		case CFlipper::FLIPPERSTATE_UP:
			m_pPolygon[nCntPolygon]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UP));
			break;
		case CFlipper::FLIPPERSTATE_DOWN:
			m_pPolygon[nCntPolygon]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_DOWN));
			break;
		case CFlipper::FLIPPER_STATE_NONE:

			if (nCntPolygon == CFlipper::FLIPPER_TYPE_LEFT)
			{
				m_pPolygon[nCntPolygon]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_LEFT));
			}
			else
			{
				m_pPolygon[nCntPolygon]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_RIGHT));
			}
			break;
		default:
			break;
		}
	}
#endif // _DEBU
}

//******************************
// �`�揈��
//******************************
void CPlayer::Draw(void)
{
	CModelHierarchy::Draw();

#ifdef _DEBUG
	m_pPolygon[CFlipper::FLIPPER_TYPE_LEFT]->Draw();
	m_pPolygon[CFlipper::FLIPPER_TYPE_RIGHT]->Draw();
#endif // _DEBU
}

//******************************
// �H�̑��쏈��
//******************************
void CPlayer::ControllFlipper(void)
{


#ifdef _DEBUG
	// �L�[�{�[�h����
	// ���H�𑀍�
	if (CManager::GetKeyboard()->GetKeyPress(DIK_UP))
	{// �グ��
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_DOWN))
	{// ������
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
	}

	// �E�H�𑀍�
	if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
	{// �グ��
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_S))
	{// ������
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
	}
#endif // _DEBUG
	// �R���g���[���[����
	
	// ���H�𑀍�
	if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lRz <= -10)
	{// �グ��
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
	}
	else if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lRz >= 10)
	{// ������
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
	}

	// �E�H�𑀍�
	if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lY <= -10)
	{// �グ��
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
	}
	else if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lY >= 10)
	{// ������
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
	}

	// �H�̊p�x�̊Ǘ�
	ManageFlipperAngle();

}

//******************************
// �H�̊p�x�̊Ǘ�
//******************************
void CPlayer::ManageFlipperAngle(void)
{
	// ���f���f�[�^�̎擾
	CResourceModel::Model * pModelData = GetModelData();
	// �E�H�𓮂���
	pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z += (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] - pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z)*FLIPPER_RATE;
	// ���H�𓮂���
	pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z += (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] - pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z)*FLIPPER_RATE;

	// �E�H�̏オ���Ă��邩�������Ă��邩�̔���
	if (pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z <= RIGHT_FLIPPER_DIST_ANGLE_UP + FLIPPER_JUDGE)
	{// �オ���Ă���Ƃ�
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z >= RIGHT_FLIPPER_DIST_ANGLE_DOWN - FLIPPER_JUDGE)
	{// �������Ă���Ƃ�
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
	}
	else
	{// ����
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPER_STATE_NONE);
	}

	// �E�H�̏オ���Ă��邩�������Ă��邩�̔���
	if (pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z >= LEFT_FLIPPER_DIST_ANGLE_UP - FLIPPER_JUDGE)
	{// �オ���Ă���Ƃ�
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z <= LEFT_FLIPPER_DIST_ANGLE_DOWN + FLIPPER_JUDGE)
	{// �������Ă���Ƃ�
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
	}
	else
	{// ����
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPER_STATE_NONE);
	}
}
