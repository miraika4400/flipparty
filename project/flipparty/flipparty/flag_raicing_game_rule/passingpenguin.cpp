//=============================================================================
//
// passingpenguin�N���X�̏��� [passingpenguin.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "passingpenguin.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "resource_texture.h"
#include "resource_shader.h"
#include "game.h"
#include "camera_base.h"
#include "light.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define HIERARCHY_TEXT_PATH_PASSING "./data/Texts/hierarchy/pengin00.txt"   // �K�w�\���e�L�X�g�̃p�X
#define FACE_PARTS_NUMBER 3  // �\��p�[�c�̃p�[�c�ԍ�
#define FACE_PATTERN 3       // �\��p�^�[����
#define FACE_TEX_V (1.0f/(float)FACE_PATTERN) * (float)m_facePattern
#define MOVE_SPEED 3.0f	//�ړ����x
#define LEFT_START_POS_X -330.0f
#define RIGHT_START_POS_X 330.0f
#define PASSING_SIZE D3DXVECTOR3(1.25f,1.25f,1.25f)

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CResourceModel::Model CPassingPenguin::m_model[MAX_PARTS_NUM] = {};    // ���f���\����
int CPassingPenguin::m_nPartsNum = 0;	//���f���p�[�c��
char CPassingPenguin::m_achAnimPath[64] = { "./data/Texts/motion/run.txt" };  // ���[�V�����e�L�X�g�̃p�X�i�[�p

//=============================================================================
//passingpenguin�N���X�̃R���X�g���N�^
//=============================================================================
CPassingPenguin::CPassingPenguin()
{
	m_pMotion = NULL;
	m_facePattern = 0;
	m_moveDirection = MOVE_DIRECTION_LEFT;
	m_state = STATE_WAIT;
	m_move = VEC3_ZERO;
}

//=============================================================================
//passingpenguin�N���X�̃f�X�g���N�^
//=============================================================================
CPassingPenguin::~CPassingPenguin()
{
}

//=============================================================================
//passingpenguin�N���X�̃N���G�C�g����
//=============================================================================
CPassingPenguin * CPassingPenguin::Create(D3DXVECTOR3 pos)
{
	CPassingPenguin *pPassingPenguin = NULL;

	//�C���X�^���X����
	pPassingPenguin = new CPassingPenguin;

	if (pPassingPenguin)
	{
		pPassingPenguin->SetPos(pos);
		pPassingPenguin->Init();
		pPassingPenguin->SetPriority(OBJTYPE_CPU); // �I�u�W�F�N�g�^�C�v
	}

	return pPassingPenguin;
}

//=============================================================================
//passingpenguin�N���X��
//=============================================================================
HRESULT CPassingPenguin::Load(void)
{
	//���f���̓ǂݍ���
	LoadModels(HIERARCHY_TEXT_PATH_PASSING, m_model, &m_nPartsNum);

	return S_OK;
}

//=============================================================================
//passingpenguin�N���X��
//=============================================================================
void CPassingPenguin::Unload(void)
{
	for (int nCntParts = 0; nCntParts < m_nPartsNum; nCntParts++)
	{
		//���b�V���̔j��
		if (m_model[nCntParts].pMesh)
		{
			m_model[nCntParts].pMesh->Release();
			m_model[nCntParts].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (m_model[nCntParts].pBuffMat)
		{
			m_model[nCntParts].pBuffMat->Release();
			m_model[nCntParts].pBuffMat = NULL;
		}
	}

}

//=============================================================================
//passingpenguin�N���X�̏���������
//=============================================================================
HRESULT CPassingPenguin::Init(void)
{
	//�K�w�\���t�����f���N���X�̏�����
	if (FAILED(CModelHierarchy::Init(m_nPartsNum, &m_model[0], HIERARCHY_TEXT_PATH_PASSING)))
	{
		return E_FAIL;
	}

	//���[�V�����̐���
	m_pMotion = CMotion::Create(m_nPartsNum, m_achAnimPath, GetModelData());

	//���[�V�����̍Đ�
	m_pMotion->SetActiveMotion(true);

	//�t�F�C�X�p�^�[���̏�����
	m_facePattern = 0;

	// �T�C�Y
	SetSize(PASSING_SIZE);

	return S_OK;
}

//=============================================================================
//passingpenguin�N���X�̏I������
//=============================================================================
void CPassingPenguin::Uninit(void)
{
	//�K�w�\���t�����f���N���X�̏I��
	CModelHierarchy::Uninit();
}


//=============================================================================
//passingpenguin�N���X�̍X�V����
//=============================================================================
void CPassingPenguin::Update(void)
{
	if (m_state == STATE_MOVE)
	{
		//�ړ�
		Move();
	}
}

//=============================================================================
//passingpenguin�N���X�̕`�揈��
//=============================================================================
void CPassingPenguin::Draw(void)
{
	if (m_state != STATE_WAIT)
	{
		//�K�w�\���t�����f���N���X�̕`��
		CModelHierarchy::Draw();
	}
	
}

//=============================================================================
//passingpenguin�N���X�̈ړ������̐ݒ菈��
//=============================================================================
void CPassingPenguin::SetMoveDirection(MOVE_DIRECTION moveDirection)
{
	//�ړ�������ݒ�
	m_moveDirection = moveDirection;

	//���݈ʒu���擾
	D3DXVECTOR3 pos = GetPos();

	//�������擾
	D3DXVECTOR3 rot = GetRot();

	switch (m_moveDirection)
	{
	case MOVE_DIRECTION_LEFT:
		pos = D3DXVECTOR3(LEFT_START_POS_X, pos.y, pos.z);
		m_move = D3DXVECTOR3(MOVE_SPEED, 0.0f, 0.0f);
		rot = D3DXVECTOR3(rot.x, D3DXToRadian(-90.0f), rot.z);

		break;

	case MOVE_DIRECTION_RIGHT:
		pos = D3DXVECTOR3(RIGHT_START_POS_X, pos.y, pos.z);
		m_move = D3DXVECTOR3(-MOVE_SPEED, 0.0f, 0.0f);
		rot = D3DXVECTOR3(rot.x, D3DXToRadian(90.0f), rot.z);
	
		break;
	default:
		break;
	}
	
	//�ʒu�̐ݒ�
	SetPos(pos);

	//�����̐ݒ�
	SetRot(rot);

	//��Ԃ��ړ��֐ݒ�
	m_state = STATE_MOVE;
}

//=============================================================================
//passingpenguin�N���X�̈ړ�����
//=============================================================================
void CPassingPenguin::Move(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();

	//�ړ��ʂ�^����
	pos += m_move;

	//�ʒu�̐ݒ�
	SetPos(pos);

	if (pos.x <= LEFT_START_POS_X || pos.x >= RIGHT_START_POS_X)
	{
		//��Ԃ�ҋ@�ɐݒ�
		m_state = STATE_WAIT;
	}
}

//=============================================================================
//passingpenguin�N���X�̃��f���̕`�揈��
//=============================================================================
void CPassingPenguin::DrawModel(void)
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

//=============================================================================
//passingpenguin�N���X�̃V�F�[�_�[�̐ݒ菈��
//=============================================================================
void CPassingPenguin::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
{
	if (pEffect != NULL)
	{
		// �V�F�[�_�[�ɏ���n��
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		mat = pModelData->mtxWorld * (*CManager::GetCamera()->GetViewMtx())* (*CManager::GetCamera()->GetProjectionMtx());
		// ���[���h�v���W�F�N�V����
		pEffect->SetMatrix("WorldViewProj", &mat);
		// ���[���h���W
		pEffect->SetMatrix("World", &pModelData->mtxWorld);
		// ���C�g�f�B���N�V����
		D3DXVECTOR3 lightDir = CGame::GetLight()->GetDir();
		pEffect->SetFloatArray("LightDirection", (float*)&D3DXVECTOR3(lightDir.x, -lightDir.y, -lightDir.z), 3);
		// ���_�ʒu
		D3DXVECTOR3 eye = CManager::GetCamera()->GetPos();
		pEffect->SetFloatArray("Eye", (float*)&eye, 3);
	}
}
