////////////////////////////////////////////////////
//
//    �~�j�Q�[�����U���g�N���X�̏���[mini_result.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//=============================
// �C���N���[�h
//=============================
#include "cloud.h"
#include "manager.h"
#include "renderer.h"
#include "resource_model.h"
#include "game.h"
#include "camera_base.h"
#include "light.h"
#include "resource_shader.h"
#include "resource_texture.h"
#include "thunder.h"
#include "rule_flygame.h"
#include "player_flygame.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//**********************************
// �}�N����`
//**********************************
#define MAX_SIZE  D3DXVECTOR3(1.0f, 1.0f, 1.0f)
#define SIZE_RATE 0.07f
//#define CLOUD_COLOR_NORMAL D3DXCOLOR(0.95f, 0.95f, 0.95f, m_fAlpha)  // �_�̐F*�ʏ펞
#define CLOUD_COLOR_NORMAL D3DXCOLOR(0.3f , 0.3f , 0.3f , m_fAlpha)  // �_�̐F*�ʏ펞
#define CLOUD_COLOR_OUT    D3DXCOLOR(0.3f , 0.3f , 0.3f , m_fAlpha)  // �_�̐F*�A�E�g��
#define THUNDER_CREATE_COUNT_MIN 20
#define THUNDER_CREATE_COUNT_MAX 50

#define THUNDER_POS_Y -60
#define CLOUD_POS_Y   150

//=============================
// �R���X�g���N�^
//=============================
CCloud::CCloud() :CModel(OBJTYPE_MAP)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAction = 0;
	m_fAlpha = 0.0f;
	m_nPlayerNum = 0;
	m_playerPosSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bThunder = false;
	m_color = CLOUD_COLOR_NORMAL;
}

//=============================
// �f�X�g���N�^
//=============================
CCloud::~CCloud()
{
}

//=============================
// �N���G�C�g
//=============================
CCloud * CCloud::Create(int nPlayerNum)
{
	// �������̊m��
	CCloud *pCloud = new CCloud;
	
	pCloud->m_nPlayerNum = nPlayerNum;
	// ������
	pCloud->Init();
	

	return pCloud;
}

//=============================
// ����������
//=============================
HRESULT CCloud::Init(void)
{
	// ���f���N���X�̏�����
	CModel::Init();

	// ���W�̐ݒ�
	D3DXVECTOR3 pos = CRuleFly::GetPlayer(m_nPlayerNum)->GetPos();
	SetPos(D3DXVECTOR3(pos.x, pos.y + CLOUD_POS_Y, 30.0f));

	// ���f���̊��蓖��
	BindModel(CResourceModel::GetModel(CResourceModel::MODEL_CLOUD));

	// �T�C�Y�̏�����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetSize(m_size);

	// �J�E���g�̏�����
	m_nCntAction = 0;
	// �A���t�@�l�̏�����
	m_fAlpha = 0.0f;
	// �v���C���[���W�ۑ��ϐ�
	m_playerPosSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ���t���O
	m_bThunder = false;

	// �F�̏�����
	m_color = CLOUD_COLOR_NORMAL;

	return S_OK;
}

//=============================
// �I������
//=============================
void CCloud::Uninit(void)
{
	CModel::Uninit();
}


//=============================
// �X�V����
//=============================
void CCloud::Update(void)
{
	m_nCntAction++;
	if (m_nCntAction >= THUNDER_CREATE_COUNT_MAX)
	{
		// �T�C�Y�̕ύX
		m_size += (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_size)*SIZE_RATE;
		m_fAlpha += (-0.1f - m_fAlpha)*SIZE_RATE;
		
	}
	else
	{
		// �T�C�Y�̕ύX
		m_size += (MAX_SIZE - m_size)*SIZE_RATE;
		m_fAlpha += (1.0f - m_fAlpha)*SIZE_RATE;
	}
	// �A���t�@�l�̕ۊ�
	m_color.a = m_fAlpha;

	// ���𗎂Ƃ����̔���
	if (m_nCntAction == THUNDER_CREATE_COUNT_MIN)
	{
		// ���W�̕ۑ�
		m_playerPosSave = CRuleFly::GetPlayer(m_nPlayerNum)->GetPos();
	}
	if (m_nCntAction >= THUNDER_CREATE_COUNT_MIN&&m_nCntAction <= THUNDER_CREATE_COUNT_MAX)
	{
		// �F�̐ݒ�
		m_color = CLOUD_COLOR_OUT;

		// �ۑ����Ă������W�ƈႤ��&&�����܂����Ƃ��Ă��Ȃ��Ƃ�
		if(m_playerPosSave!= CRuleFly::GetPlayer(m_nPlayerNum)->GetPos()&& !m_bThunder)
		{
			// ���̐���
			D3DXVECTOR3 pos = GetPos();
			CThunder::Create(D3DXVECTOR3(pos.x, pos.y + THUNDER_POS_Y, pos.z), m_nPlayerNum);
			// ���𗎂Ƃ�����Ԃɂ���
			m_bThunder = true;

			m_nCntAction = THUNDER_CREATE_COUNT_MAX;
		}
	}
	else
	{
		// �F�̐ݒ�
		m_color = CLOUD_COLOR_NORMAL;
	}
	// �T�C�Y�̃Z�b�g
	SetSize(m_size);

	// ��������
	if (m_fAlpha <= 0.0f)
	{
		Uninit();
	}
}

//=============================
// �`�揈��
//=============================
void CCloud::Draw(void)
{
	CModel::Draw();
}

//=============================
// ���f���`��
//=============================
void CCloud::DrawModel(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef; //���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;   //�}�e���A���f�[�^�ւ̃|�C���^

	// ���f���f�[�^�̎擾
	CResourceModel::Model * pModelData = GetModelData();

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &pModelData->mtxWorld);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	// �V�F�[�_�[���̎擾
	CResourceShader::Shader shader = CResourceShader::GetShader(CResourceShader::SHADER_CLOUD);

	if (shader.pEffect != NULL)
	{
		// �V�F�[�_�[�v���O�����ɒl�𑗂�
		SetShaderVariable(shader.pEffect, pModelData);
		if (pModelData->pBuffMat != NULL)
		{
			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)pModelData->pBuffMat->GetBufferPointer();

			// �p�X���̎擾
			UINT numPass = 0;
			shader.pEffect->Begin(&numPass, 0);

			// �p�X�����`�揈���̃��[�v
			for (int nCntEffect = 0; nCntEffect < (int)numPass; nCntEffect++)
			{
				for (int nCntMat = 0; nCntMat < (int)pModelData->nNumMat; nCntMat++)
				{
					//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
					pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// �e�N�X�`��
					pDevice->SetTexture(0, pModelData->apTexture[nCntMat]);

					// �e�N�X�`�����V�F�[�_�[�ɑ���
					shader.pEffect->SetTexture("ToonTex", CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TOONSHADOW_CLOUD));
					// �F
					shader.pEffect->SetFloatArray("DiffuseColor", (float*)&m_color, 4);
					// �V�F�[�_�p�X�̕`��J�n
					shader.pEffect->BeginPass(nCntEffect);
					//���f���p�[�c�̕`��
					pModelData->pMesh->DrawSubset(nCntMat);
					// �V�F�[�_�p�X�̏I��
					shader.pEffect->EndPass();

					pMat[nCntMat] = pModelData->defMat[nCntMat];
				}
			}
			// �V�F�[�_�[�I��
			shader.pEffect->End();
		}
	}
	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
	// �e�N�X�`�����̏�����
	pDevice->SetTexture(0, 0);
}

//=============================
// ���[���h�}�g���b�N�X�̐ݒ�
//=============================
void CCloud::SetWorldmtx(void)
{

	D3DXMATRIX  mtxRot;   // ��]�s��
	D3DXMATRIX	mtxTrans; // �ʒu�s��
	D3DXMATRIX	mtxScail; // �T�C�Y�s��

	// ���f���f�[�^�̎擾
	CResourceModel::Model * pModelData = GetModelData();
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pModelData->mtxWorld);

	// �T�C�Y�𔽉f
	D3DXMatrixScaling(&mtxScail, pModelData->size.x, pModelData->size.y, pModelData->size.z);
	D3DXMatrixMultiply(&pModelData->mtxWorld, &pModelData->mtxWorld, &mtxScail);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pModelData->rot.y, pModelData->rot.x, pModelData->rot.z);
	D3DXMatrixMultiply(&pModelData->mtxWorld, &pModelData->mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pModelData->pos.x, pModelData->pos.y, pModelData->pos.z);
	D3DXMatrixMultiply(&pModelData->mtxWorld, &pModelData->mtxWorld, &mtxTrans);
}

//=============================
// �V�F�[�_�[�ɒl�𑗂�
//=============================
void CCloud::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
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
