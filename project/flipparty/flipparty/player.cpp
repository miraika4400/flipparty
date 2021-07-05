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
#include "billboard.h"
#include "motion.h"
#include "resource_shader.h"
#include "camera_base.h"
#include "light.h"

//*****************************
// �}�N����`
//*****************************
#define HIERARCHY_TEXT_PATH1 "./data/Texts/hierarchy/pengin00.txt"   // �K�w�\���e�L�X�g�̃p�X
#define RIGHT_FLIPPER_DIST_ANGLE_UP   D3DXToRadian(-60.0f)           // �E�H���グ���Ƃ��̊p�x
#define RIGHT_FLIPPER_DIST_ANGLE_DOWN D3DXToRadian(30.0f)            // �E�H���������Ƃ��̊p�x
#define LEFT_FLIPPER_DIST_ANGLE_UP    -RIGHT_FLIPPER_DIST_ANGLE_UP   // ���H���グ���Ƃ��̊p�x
#define LEFT_FLIPPER_DIST_ANGLE_DOWN  -RIGHT_FLIPPER_DIST_ANGLE_DOWN // ���H���������Ƃ��̊p�x
#define FLIPPER_RATE 0.1f                                            // �H�𓮂����Ƃ��̌W��
#define FLIPPER_JUDGE D3DXToRadian(20.0f)                            // �オ���Ă��邩�������Ă��邩����̊�l
#define PLAYER_NUMBER_ICON_HEIGHT 85.0f                              // �v���C���[�ԍ��A�C�R���̍���
#define PLAYER_NUMBER_ICON_SIZE D3DXVECTOR3(10.0f,10.0f,0.0f)        // �v���C���[�ԍ��A�C�R���̃T�C�Y
#define PLAYER_NUMBER_ICON_POS  D3DXVECTOR3(GetPos().x, GetPos().y + PLAYER_NUMBER_ICON_HEIGHT, GetPos().z) // �v���C���[�ԍ��A�C�R���̈ʒu
#define FACE_PARTS_NUMBER 3  // �\��p�[�c�̃p�[�c�ԍ�
#define FACE_PATTERN 3       // �\��p�^�[����
#define FACE_TEX_V (1.0f/(float)FACE_PATTERN) * (float)m_facePattern

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CResourceModel::Model CPlayer::m_model[MAX_PARTS_NUM] = {};
int CPlayer::m_nPartsNum = 0;
char CPlayer::m_achAnimPath[MOTION_MAX][64]
{
	{ "./data/Texts/motion/idol.txt" },          // �ҋ@�A�j���[�V����
	{ "./data/Texts/motion/miniresult_1.txt" }, // ��ʃA�j���[�V����
	{ "./data/Texts/motion/miniresult_2.txt" }, // ��ʃA�j���[�V����
	{ "./data/Texts/motion/miniresult_3.txt" }, // �O�ʃA�j���[�V����
	{ "./data/Texts/motion/miniresult_4.txt" }, // �ŉ��ʃA�j���[�V����
	{ "./data/Texts/motion/fly.txt" },          // fly�A�j���[�V����
	
};

//******************************
// �R���X�g���N�^
//******************************
CPlayer::CPlayer() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// �ϐ��̃N���A
	m_pFlipper = NULL;
	m_pFlipperMoveState = NULL;
	m_nPlayerNum = 0;                  // �v���C���[�ԍ�
	ZeroMemory(&m_fFlipperDist, sizeof(m_fFlipperDist)); // �H�̊p�x �ڕW�l
	m_pPlayerNumIcon = NULL; // �v���C���[�ԍ��A�C�R��
	m_bMove = false;         // �����邩�ǂ����̃t���O
	m_nRank = 0;
	m_pActiveMotion = NULL;
	m_facePattern = FACE_PATTERN_NORMAL;
	m_nPoint = 0;

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
	// �|�C���g�̏�����
	m_nPoint = 0;

	// �t���b�p�[�N���X�̐���
	m_pFlipper = CFlipper::Create();
	m_pFlipperMoveState = CFlipper::Create();

	// �H�̖ڕW�p�x�̏�����
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = 0.0f;
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = 0.0f;

	// �v���C���[�A�C�R���̐ݒ�
	m_pPlayerNumIcon = CBillboard::Create(PLAYER_NUMBER_ICON_POS, PLAYER_NUMBER_ICON_SIZE);
	
	// �A�C�R���e�N�X�`���̐ݒ�
	if (m_pPlayerNumIcon != NULL)
	{
		// �e�N�X�`������
		switch (m_nPlayerNum)
		{
		case 0:
			m_pPlayerNumIcon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_1P));
			break;
		case 1:
			m_pPlayerNumIcon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_2P));
			break;
		case 2:
			m_pPlayerNumIcon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_3P));
			break;
		case 3:
			m_pPlayerNumIcon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_4P));
			break;
		default:
			break;
		}
	}

	// ������t���O�̏�����
	m_bMove = false;

	// �A�j���[�V�����̐���
	for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
	{
		m_apMotion[nCntAnim] = CMotion::Create(GetPartsNum(), m_achAnimPath[nCntAnim], GetModelData());
	}

	SetMotion(MOTION_IDOL);

#ifdef _DEBUG
	m_bMove = true;
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
	if (m_pFlipper != NULL)
	{
		m_pFlipper->Uninit();
		m_pFlipper = NULL;
	}

	// �t���b�p�[�ړ���ԏI������
	if (m_pFlipperMoveState != NULL)
	{
		m_pFlipperMoveState->Uninit();
		m_pFlipperMoveState = NULL;
	}
	
	// �A�C�R���̉��
	if (m_pPlayerNumIcon != NULL)
	{
		m_pPlayerNumIcon->Uninit();
		delete m_pPlayerNumIcon;
		m_pPlayerNumIcon = NULL;
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
	if (m_bMove)
	{// �t���O��true�̎�
		// �H�𓮂���
		ControllFlipper();
	}
	else
	{
		// �ړ���Ԃ̍X�V
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT , CFlipper::FLIPPER_STATE_NONE);
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT  , CFlipper::FLIPPER_STATE_NONE);
	}

	// �v���C���[�ԍ��A�C�R���̈ʒu�̐ݒ�
	if (m_pPlayerNumIcon != NULL)
	{
		m_pPlayerNumIcon->SetPos(PLAYER_NUMBER_ICON_POS);
	}

#ifdef _DEBUG

	for (int nCntPolygon = 0; nCntPolygon < FLIPPER_NUM; nCntPolygon++)
	{
		CFlipper::FLIPPER_STATE flipperState = m_pFlipper->GetState((CFlipper::FLIPPER_TYPE)nCntPolygon);

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
	
	if (m_pPlayerNumIcon != NULL)
	{
		m_pPlayerNumIcon->Draw();
	}

#ifdef _DEBUG
	m_pPolygon[CFlipper::FLIPPER_TYPE_LEFT]->Draw();
	m_pPolygon[CFlipper::FLIPPER_TYPE_RIGHT]->Draw();
#endif // _DEBUG
}

//******************************
// ���[�V�����̃Z�b�g����
//******************************
void CPlayer::SetMotion(MOTION_TYPE type)
{
	// ���݃A�N�e�B�u�̃��[�V�����̒�~
	if (m_pActiveMotion != NULL)
	{
		if (m_apMotion[type] != m_pActiveMotion)
		{
			m_pActiveMotion->SetActiveMotion(false);
			m_pActiveMotion = NULL;
		}
	}

	// ���[�V�����̍Đ�
	if (m_apMotion[type] != NULL)
	{
		if (!m_apMotion[type]->GetActiveMotion())
		{
			m_apMotion[type]->SetActiveMotion(true);
			m_pActiveMotion = m_apMotion[type];
		}
	}
}

//******************************
// ���f���̕`�揈��
//******************************
void CPlayer::DrawModel(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

	CResourceModel::Model *pModelData = GetModelData();

	for (int nCntParts = 0; nCntParts < GetPartsNum(); nCntParts++)
	{
		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &pModelData[nCntParts].mtxWorld);

		//���݂̃}�e���A�����擾����
		pDevice->GetMaterial(&matDef);

		// �V�F�[�_�[���̎擾
		CResourceShader::Shader shader = CResourceShader::GetShader(CResourceShader::SHADER_PLAYER);

		if (shader.pEffect != NULL)
		{
			// �V�F�[�_�[�v���O�����ɒl�𑗂�
			SetShaderVariable(shader.pEffect, &pModelData[nCntParts]);

			// �t�F�C�X�p�^�[��
			if (nCntParts != FACE_PARTS_NUMBER)
			{
				shader.pEffect->SetFloat("fTexV", 0.0f);
			}
			else
			{
				shader.pEffect->SetFloat("fTexV", FACE_TEX_V );
			}

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)pModelData[nCntParts].pBuffMat->GetBufferPointer();

			// �p�X���̎擾
			UINT numPass = 0;
			shader.pEffect->Begin(&numPass, 0);

			// �p�X�����`�揈���̃��[�v
			for (int nCntEffect = 0; nCntEffect < (int)numPass; nCntEffect++)
			{
				for (int nCntMat = 0; nCntMat < (int)pModelData[nCntParts].nNumMat; nCntMat++)
				{
					//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
					pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// �e�N�X�`��
					pDevice->SetTexture(0, pModelData[nCntParts].apTexture[nCntMat]);

					// �e�N�X�`�����V�F�[�_�[�ɑ���
					shader.pEffect->SetTexture("Tex", pModelData[nCntParts].apTexture[nCntMat]);
					// �e�N�X�`�����V�F�[�_�[�ɑ���
					shader.pEffect->SetTexture("ToonTex", CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TOONSHADOW));
					// �F
					shader.pEffect->SetFloatArray("DiffuseColor", (float*)&pMat[nCntMat].MatD3D.Diffuse, 4);
					// �V�F�[�_�p�X�̕`��J�n
					shader.pEffect->BeginPass(nCntEffect);
					//���f���p�[�c�̕`��
					pModelData[nCntParts].pMesh->DrawSubset(nCntMat);
					// �V�F�[�_�p�X�̏I��
					shader.pEffect->EndPass();


					pMat[nCntMat] = pModelData[nCntParts].defMat[nCntMat];
				}
			}
			shader.pEffect->End();
		}
		
		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
		// �e�N�X�`���̏�����
		pDevice->SetTexture(0, 0);
	}
}

//******************************
// �H�̑��쏈��
//******************************
void CPlayer::ControllFlipper(void)
{

#ifdef _DEBUG
		// �L�[�{�[�h����
		// �E�H�𑀍�
		if (CManager::GetKeyboard()->GetKeyPress(DIK_UP))
		{// �グ��
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;

			// �ړ���Ԃ̍X�V
			m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
		}
		else if (CManager::GetKeyboard()->GetKeyPress(DIK_DOWN))
		{// ������
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;

			// �ړ���Ԃ̍X�V
			m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
		}

		// ���H�𑀍�
		if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
		{// �グ��
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;

			// �ړ���Ԃ̍X�V
			m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
		}
		else if (CManager::GetKeyboard()->GetKeyPress(DIK_S))
		{// ������
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;

			// �ړ���Ԃ̍X�V
			m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
		}
#endif // _DEBUG
	// �R���g���[���[����
	
	// �E�H�𑀍�
	if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lRz <= -10)
	{// �グ��
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;

		// �ړ���Ԃ̍X�V
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lRz >= 10)
	{// ������
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;

		// �ړ���Ԃ̍X�V
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
	}

	// ���H�𑀍�
	if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lY <= -10)
	{// �グ��
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;

		// �ړ���Ԃ̍X�V
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lY >= 10)
	{// ������
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;

		// �ړ���Ԃ̍X�V
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
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
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z >= RIGHT_FLIPPER_DIST_ANGLE_DOWN - FLIPPER_JUDGE)
	{// �������Ă���Ƃ�
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
	}
	else
	{// ����
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPER_STATE_NONE);
	}

	// �E�H�̏オ���Ă��邩�������Ă��邩�̔���
	if (pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z >= LEFT_FLIPPER_DIST_ANGLE_UP - FLIPPER_JUDGE)
	{// �オ���Ă���Ƃ�
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z <= LEFT_FLIPPER_DIST_ANGLE_DOWN + FLIPPER_JUDGE)
	{// �������Ă���Ƃ�
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
	}
	else
	{// ����
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPER_STATE_NONE);
	}
}


//******************************
// �V�F�[�_�[�v���O�����ɒl�𑗂�
//******************************
void CPlayer::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
{
	if (pEffect != NULL)
	{
		// �V�F�[�_�[�ɏ���n��
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		mat = pModelData->mtxWorld * (*CGame::GetCamera()->GetViewMtx())* (*CGame::GetCamera()->GetProjectionMtx());
		// ���[���h�v���W�F�N�V����
		pEffect->SetMatrix("WorldViewProj", &mat);
		// ���[���h���W
		pEffect->SetMatrix("World", &pModelData->mtxWorld);
		// ���C�g�f�B���N�V����
		D3DXVECTOR3 lightDir = CGame::GetLight()->GetDir();
		pEffect->SetFloatArray("LightDirection", (float*)&D3DXVECTOR3(lightDir.x, -lightDir.y, -lightDir.z), 3);
		// ���_�ʒu
		D3DXVECTOR3 eye = CGame::GetCamera()->GetPos();
		pEffect->SetFloatArray("Eye", (float*)&eye, 3);
	}
}