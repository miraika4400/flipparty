////////////////////////////////////////////////////
//
//    captain�N���X�̏���[captain.cpp]
//    Author:���V ����(����r�H)
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "captain.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "game.h"
#include "flipper.h"


//*****************************
// �}�N����`
//*****************************
#define HIERARCHY_TEXT_PATH "./data/Texts/hierarchy/pengin00.txt"    //�K�w�\���e�L�X�g�̃p�X
#define RIGHT_FLIPPER_PARTS_NUM 5                                    // �E�H�̃p�[�c�ԍ�
#define LEFT_FLIPPER_PARTS_NUM  4                                    // ���H�̃p�[�c�ԍ�
#define RIGHT_FLIPPER_DIST_ANGLE_UP   D3DXToRadian(-60.0f)           // �E�H���グ���Ƃ��̊p�x
#define RIGHT_FLIPPER_DIST_ANGLE_DOWN D3DXToRadian(30.0f)            // �E�H���������Ƃ��̊p�x
#define LEFT_FLIPPER_DIST_ANGLE_UP    -RIGHT_FLIPPER_DIST_ANGLE_UP   // ���H���グ���Ƃ��̊p�x
#define LEFT_FLIPPER_DIST_ANGLE_DOWN  -RIGHT_FLIPPER_DIST_ANGLE_DOWN // ���H���������Ƃ��̊p�x
#define FLIPPER_RATE 0.07f                                           // �H�𓮂����Ƃ��̌W��
#define FLIPPER_JUDGE D3DXToRadian(20.0f)                            // �オ���Ă��邩�������Ă��邩����̊�l

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CResourceModel::Model CCaptain::m_model[MAX_PARTS_NUM] = {};
int CCaptain::m_nPartsNum = 0;

//******************************
// �R���X�g���N�^
//******************************
CCaptain::CCaptain() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// �ϐ��̃N���A
	m_pFlieer = NULL;
	ZeroMemory(&m_fFlipperDist, sizeof(m_fFlipperDist)); // �H�̊p�x �ڕW�l
	m_nColor = 0;
	m_nCount = 0;
	m_nChoice = 0;

	m_bLoop = true;
	m_bJudgRed = false;
	m_bJudgWhite = false;

	m_eColorRed = RED_FLAG_DOWN;
	m_eColorWhite = WHITE_FLAG_DOWN;
}

//******************************
// �f�X�g���N�^
//******************************
CCaptain::~CCaptain()
{
}

//******************************
// �N���G�C�g
//******************************
CCaptain * CCaptain::Create(D3DXVECTOR3 pos)
{
	// �������̊m��
	CCaptain *pCaptain;
	pCaptain = new CCaptain;

	// ������
	pCaptain->Init();

	// �e�l�̑���E�Z�b�g
	pCaptain->SetPos(pos);
	pCaptain->SetPriority(OBJTYPE_PLAYER); // �I�u�W�F�N�g�^�C�v

	return pCaptain;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CCaptain::Load(void)
{

	// ���f���̓ǂݍ���
	LoadModels(HIERARCHY_TEXT_PATH, &m_model[0], &m_nPartsNum);

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CCaptain::Unload(void)
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
HRESULT CCaptain::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nPartsNum, &m_model[0], HIERARCHY_TEXT_PATH)))
	{
		return E_FAIL;
	}
	// �t���b�p�[�N���X�̐���
	m_pFlieer = CFlipper::Create();

	// �H�̖ڕW�p�x�̏�����
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = 0.0f;
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = 0.0f;

	return S_OK;
}

//******************************
// �I������
//******************************
void CCaptain::Uninit(void)
{
	CModelHierarchy::Uninit();
}

//******************************
// �X�V����
//******************************
void CCaptain::Update(void)
{
	while (m_bLoop)
	{
		// �S�������Ă�����
		Judge(RED_FLAG_DOWN, WHITE_FLAG_DOWN, WHITE_DOWN, RED_DOWN);
		// �������グ�Ă�����
		Judge(RED_FLAG_DOWN, WHITE_FLAG_UP, WHITE_UP, RED_DOWN);
		// �Ԃ����グ�Ă�����
		Judge(RED_FLAG_UP, WHITE_FLAG_DOWN, WHITE_DOWN, RED_UP);
		// �ǂ�����オ���Ă�����
		Judge(RED_FLAG_UP, WHITE_FLAG_UP, WHITE_UP, RED_UP);

		// ���グ���菈��
		FlagJudge();
	}
	// �H�̊p�x�̊Ǘ�
	ManageFlipperAngle();
}

//******************************
// �`�揈��
//******************************
void CCaptain::Draw(void)
{
	CModelHierarchy::Draw();
}

//******************************
// �F���ʏ���
//******************************
void CCaptain::Judge(FLAG ColorFlagRed, FLAG ColorFlagWhite, COLOR ColorRed, COLOR ColorWhite)
{
	// �S�������Ă�����
	if (m_eColorRed == ColorFlagRed && m_eColorWhite == ColorFlagWhite)
	{
		while (true)
		{
			// �F����
			m_nColor = rand() % 4 + 1;
			if (m_nColor != ColorRed && m_nColor != ColorWhite)
			{
				break;
			}
		}
	}
}

//******************************
// �����Ă��邩�グ�Ă��邩�̊m�F
//******************************
void CCaptain::JudgeColor(FLAG ColorFlagRed, FLAG ColorFlagWhite, COLOR ColorRed, COLOR ColorWhite)
{

}

//******************************
// ���グ���菈��
//******************************
void CCaptain::FlagJudge()
{
	// ���グ���菈��
	switch (m_nColor)
	{
		// �グ
	case WHITE_UP:
		if (!m_bJudgWhite)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;

			if (m_nChoice != 1)
			{
				m_bLoop = false;
			}
			else
			{
				m_eColorWhite = WHITE_FLAG_UP;
				m_bJudgWhite = true;
				m_nCount++;
			}
		}
		break;
		// ����
	case WHITE_DOWN:
		if (m_bJudgWhite)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;

			if (m_nChoice != 1)
			{
				m_bLoop = false;
			}
			else
			{
				m_eColorWhite = WHITE_FLAG_DOWN;
				m_bJudgWhite = false;
				m_nCount++;
			}
		}
		break;
		// �ԏグ
	case RED_UP:
		if (!m_bJudgRed)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;

			if (m_nChoice != 2)
			{
				m_bLoop = false;
			}
			else
			{
				m_eColorRed = RED_FLAG_UP;
				m_bJudgRed = true;
				m_nCount++;
			}
		}
		break;
		// �ԉ���
	case RED_DOWN:
		if (m_bJudgRed)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;

			if (m_nChoice != 2)
			{
				m_bLoop = false;
			}
			else
			{
				m_eColorRed = RED_FLAG_DOWN;
				m_bJudgRed = false;
				m_nCount++;
			}
		}
		break;
	}
}
//******************************
// �H�̊p�x�̊Ǘ�
//******************************
void CCaptain::ManageFlipperAngle(void)
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

