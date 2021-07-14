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
#include "flag_raicing_game_rule.h"
#include "resource_shader.h"
#include "resource_texture.h"
#include "game.h"
#include "light.h"
#include "camera_base.h"
#include "motion.h"
#include "billboard.h"
#include "blind.h"

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
#define FACE_PARTS_NUMBER 3  // �\��p�[�c�̃p�[�c�ԍ�
#define FACE_PATTERN 3       // �\��p�^�[����
#define FACE_TEX_V (1.0f/(float)FACE_PATTERN) * (float)m_facePattern
#define SCALE_VALUE 1.2f	//���f���̃T�C�Y�g��W��
#define FLAG_RIGHT_POS D3DXVECTOR3(-50.0f,0.0f,100.0f)
#define FLAG_LEFT_POS D3DXVECTOR3(50.0f,0.0f,100.0f)
#define FLAG_RIGHT_SIZE D3DXVECTOR3(10.0f,10.0f,0.0f)
#define FLAG_LEFT_SIZE D3DXVECTOR3(10.0f,10.0f,0.0f)

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CResourceModel::Model CCaptain::m_model[MAX_PARTS_NUM] = {};
int CCaptain::m_nPartsNum = 0;
char CCaptainm_achAnimPath[64]
{
	 "./data/Texts/motion/idol.txt"          // �ҋ@�A�j���[�V����
};

//******************************
// �R���X�g���N�^
//******************************
CCaptain::CCaptain() :CModelHierarchy(OBJTYPE_CPU)
{
	// �ϐ��̃N���A
	m_pFlipper = NULL;
	ZeroMemory(&m_fFlipperDist, sizeof(m_fFlipperDist)); // �H�̊p�x �ڕW�l
	m_nColor = 0;
	m_nCount = 0;
	m_nChoice = 0;
	m_facePattern = 0;

	m_bJudgRed = false;
	m_bJudgWhite = false;

	m_eColorRed = RED_FLAG_DOWN;
	m_eColorWhite = WHITE_FLAG_DOWN;

	m_pMotion = NULL;
	ZeroMemory(&m_falgTexVal, sizeof(m_falgTexVal));
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
	pCaptain->SetPriority(OBJTYPE_CPU); // �I�u�W�F�N�g�^�C�v

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

	for (int nCnt = 0; nCnt < MAX_PARTS_NUM; nCnt++)
	{
		m_model[nCnt].size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	// �t���b�p�[�N���X�̐���
	m_pFlipper = CFlipper::Create();

	// �H�̖ڕW�p�x�̏�����
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = 0.0f;
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = 0.0f;

	// �\��̏�����
	m_facePattern = 0;

	//�@���[�V�����̐ݒ�
	m_pMotion = CMotion::Create(GetPartsNum(), CCaptainm_achAnimPath, GetModelData());
	m_pMotion->SetActiveMotion(true);

	//�E�����w���r���{�[�h�̍쐬
	m_falgTexVal.apFlagTex[FLAG_TEX_RIGHT] = CBillboard::Create(FLAG_RIGHT_POS, FLAG_RIGHT_SIZE);
	
	//�������w���r���{�[�h�̍쐬
	m_falgTexVal.apFlagTex[FLAG_TEX_LEFT] = CBillboard::Create(FLAG_LEFT_POS, FLAG_LEFT_SIZE);

	return S_OK;
}

//******************************
// �I������
//******************************
void CCaptain::Uninit(void)
{
	//�K�w���f���̏I��
	CModelHierarchy::Uninit();

	// �t���b�p�[�N���X�̏I������
	if (m_pFlipper != NULL)
	{
		m_pFlipper->Uninit();
		m_pFlipper = NULL;
	}
	for (int nCnt = 0; nCnt < FLAG_TEX_MAX; nCnt++)
	{
		// �e�N�X�`���N���X�̏I������
		if (m_falgTexVal.apFlagTex[nCnt] != NULL)
		{
			//�r���{�[�h�̏I��
			m_falgTexVal.apFlagTex[nCnt]->Uninit();

			//�������̍폜
			delete m_falgTexVal.apFlagTex[nCnt];

			//�������̃N���A
			m_falgTexVal.apFlagTex[nCnt] = NULL;
		}
	}
}

//******************************
// �X�V����
//******************************
void CCaptain::Update(void)
{
    // �L���v�e������������
	if (CFlagRaicingGame_rule::GetGameLoop() == CFlagRaicingGame_rule::CAPTAIN_TRUN)
	{
		// �S�������Ă�����
		Judge(RED_FLAG_DOWN, WHITE_FLAG_DOWN, WHITE_DOWN, RED_DOWN);
		// �������グ�Ă�����
		Judge(RED_FLAG_DOWN, WHITE_FLAG_UP, WHITE_UP, RED_DOWN);
		// �Ԃ����グ�Ă�����
		Judge(RED_FLAG_UP, WHITE_FLAG_DOWN, WHITE_DOWN, RED_UP);
		// �ǂ�����オ���Ă�����
		Judge(RED_FLAG_UP, WHITE_FLAG_UP, WHITE_UP, RED_UP);

        // �v���C���[�̃^�[���ɕύX
		CFlagRaicingGame_rule::SetGameLoop(CFlagRaicingGame_rule::PLAYER_TRUN);
	}

	// ���グ���菈��
	FlagJudge();
	// �H�̊p�x�̊Ǘ�
	ManageFlipperAngle();
}

//******************************
// �`�揈��
//******************************
void CCaptain::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Z�o�b�t�@�ݒ�̕ۑ��p�ϐ�
	DWORD dwCurZTest = 0;

	if (CFlagRaicingGame_rule::GetBlind()->GetState() != CBlind::BLIND_STATE_NORMAL)
	{
		//�E�������Ă�����
		if (m_falgTexVal.bFlagRight)
		{
			if (m_falgTexVal.apFlagTex[FLAG_TEX_LEFT])
			{
				m_falgTexVal.apFlagTex[FLAG_TEX_RIGHT]->Draw();
			}
		}
		//���������Ă�����
		if (m_falgTexVal.bFlagLeft)
		{
			if (m_falgTexVal.apFlagTex[FLAG_TEX_LEFT])
			{
				m_falgTexVal.apFlagTex[FLAG_TEX_LEFT]->Draw();
			}
		}
	}
	
	if (CFlagRaicingGame_rule::GetBlind()->GetState() == CBlind::BLIND_STATE_NORMAL)
	{
		//Z�o�b�t�@�̐ݒ���ꎞ�ۑ�
		pDevice->GetRenderState(D3DRS_ZFUNC, &dwCurZTest);

		//Z�e�X�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);	//Z�o�b�t�@�ւ̏������݂��֎~����

		//�X�e���V���e�X�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);				//�X�e���V���e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x05);				//�X�e���V���o�b�t�@�֔��f����Q�ƒl�̐ݒ�
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);			//�}�X�N�̐ݒ�i�r�b�g�����Ȃ��悤�Ɏw��j
		pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);	//0xffffffff�ɂ���
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);		//�X�e���V���e�X�g�̔����K����������悤�Ɏw��

		//�e�X�g�̌��ʂ̑g�ݍ��킹�ݒ�
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		//�X�e���V���EZ�e�X�g�Ƃ��Ɏ��s�����ꍇ
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);	//�X�e���V���̂ݐ��������ꍇ
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);		//�����Ƃ����������ꍇ

		//�X�e���V���o�b�t�@�֕`��
		CModelHierarchy::Draw();

		pDevice->SetRenderState(D3DRS_ZFUNC, dwCurZTest);		//Z�o�b�t�@�̐ݒ��߂�
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);	//�X�e���V���e�X�g�𖳌��ɂ���
	}

	if (CFlagRaicingGame_rule::GetBlind()->GetState() != CBlind::BLIND_STATE_NORMAL)
	{
		//Z�o�b�t�@�֒ʏ�`��
		CModelHierarchy::Draw();
	}
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
			m_falgTexVal.apFlagTex[FLAG_TEX_RIGHT]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_RIGHT_UP));
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
			m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
			m_eColorWhite = WHITE_FLAG_UP;
			m_bJudgWhite = true;
			m_falgTexVal.bFlagRight = true;
			m_falgTexVal.bFlagLeft = false;
		}
		break;
		// ����
	case WHITE_DOWN:
		if (m_bJudgWhite)
		{
			m_falgTexVal.apFlagTex[FLAG_TEX_RIGHT]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_RIGHT_DOWN));
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
			m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
			m_eColorWhite = WHITE_FLAG_DOWN;
			m_bJudgWhite = false;
			m_falgTexVal.bFlagRight = true;
			m_falgTexVal.bFlagLeft = false;
		}
		break;
		// �ԏグ
	case RED_UP:
		if (!m_bJudgRed)
		{
			m_falgTexVal.apFlagTex[FLAG_TEX_LEFT]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_LEFT_UP));
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
			m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
			m_eColorRed = RED_FLAG_UP;
			m_bJudgRed = true;
			m_falgTexVal.bFlagLeft = true;
			m_falgTexVal.bFlagRight = false;
		}
		break;
		// �ԉ���
	case RED_DOWN:
		if (m_bJudgRed)
		{
			m_falgTexVal.apFlagTex[FLAG_TEX_LEFT]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_LEFT_DOWN));
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
			m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
			m_eColorRed = RED_FLAG_DOWN;
			m_bJudgRed = false;
			m_falgTexVal.bFlagLeft = true;
			m_falgTexVal.bFlagRight = false;
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
}

//******************************
// ���f���̕`��
//******************************
void CCaptain::DrawModel(void)
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
				shader.pEffect->SetFloat("fTexV", FACE_TEX_V);
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
			// �V�F�[�_�[�I��
			shader.pEffect->End();
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
		// �e�N�X�`���̏�����
		pDevice->SetTexture(0, 0);
	}
}

//******************************
// �V�F�[�_�[�ɒl�𑗂�
//******************************
void CCaptain::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
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

