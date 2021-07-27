////////////////////////////////////////////////////
//
//    �~�j�Q�[�����U���g�N���X�̏���[mini_result.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//=============================
// �C���N���[�h
//=============================
#include "Iceberg.h"
#include "manager.h"
#include "renderer.h"
#include "resource_model.h"
#include "game.h"
#include "camera_base.h"
#include "light.h"
#include "resource_shader.h"
#include "resource_texture.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//**********************************
// �}�N����`
//**********************************

//=============================
// �R���X�g���N�^
//=============================
CIceberg::CIceberg() :CModel(OBJTYPE_MAP)
{

}

//=============================
// �f�X�g���N�^
//=============================
CIceberg::~CIceberg()
{
}

//=============================
// �N���G�C�g
//=============================
CIceberg * CIceberg::Create(D3DXVECTOR3 pos, ICEBERG_TYPE type)
{
	// �������̊m��
	CIceberg *pIceberg = new CIceberg;

	// �^�C�v�̐ݒ�
	pIceberg->m_type = type;
	// ������
	pIceberg->Init();
	// ���W�̐ݒ�
	pIceberg->SetPos(pos);

	return pIceberg;
}

//=============================
// ����������
//=============================
HRESULT CIceberg::Init(void)
{
	// ���f���N���X�̏�����
	CModel::Init();

	// ���f���̊��蓖��
	switch (m_type)
	{
	case ICEBERG_Y:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_ICEBERG_Y));
		break;
	case ICEBERG_M:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_ICEBERG_M));
		break;
	case ICEBERG_K:
		BindModel(CResourceModel::GetModel(CResourceModel::MODEL_ICEBERG_K));
		break;
	default:
		break;
	}
	

	return S_OK;
}

//=============================
// �I������
//=============================
void CIceberg::Uninit(void)
{
	CModel::Uninit();
}


//=============================
// �X�V����
//=============================
void CIceberg::Update(void)
{
}

//=============================
// �`�揈��
//=============================
void CIceberg::Draw(void)
{
	CModel::Draw();
}

//=============================
// ���f���`��
//=============================
void CIceberg::DrawModel(void)
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
	CResourceShader::Shader shader = CResourceShader::GetShader(CResourceShader::SHADER_ICEBERG);

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
					shader.pEffect->SetTexture("Tex", pModelData->apTexture[nCntMat]);
					shader.pEffect->SetTexture("ToonTex", CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TOONSHADOW_ICEBERG));
					// �F
					shader.pEffect->SetFloatArray("DiffuseColor", (float*)&pMat[nCntMat].MatD3D.Diffuse, 4);
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
void CIceberg::SetWorldmtx(void)
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
void CIceberg::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
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
