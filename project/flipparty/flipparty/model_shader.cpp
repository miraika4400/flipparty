//=============================================================================
//
// model_shader�w�b�_ [model_shader.cpp]
// Author : ���V ����
//
//=============================================================================


//******************************
// �C���N���[�h
//******************************
#include "model_shader.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "camera.h"
#include "light.h"
#include "resource_model.h"

//*****************************
// �}�N����`
//*****************************

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************

//******************************
// �R���X�g���N�^
//******************************
CModelShader::CModelShader(int nPliority) :CModel(nPliority)
{
	// �ϐ��̃N���A
	memset(&m_shader, 0, sizeof(m_shader)); // �V�F�[�_�[
}

//******************************
// �f�X�g���N�^
//******************************
CModelShader::~CModelShader()
{
}

//******************************
// ����������
//******************************
HRESULT CModelShader::Init(void)
{
	// ���f���N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//******************************
// �I������
//******************************
void CModelShader::Uninit(void)
{
	CModel::Uninit();
}

//******************************
// �X�V����
//******************************
void CModelShader::Update(void)
{
	// ���f���N���X�̍X�V����
	CModel::Update();
}

//******************************
// �`�揈��
//******************************
void CModelShader::Draw(void)
{

	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �V�F�[�_�[�����v�Z�����邽�߃��C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIX mtxRot, mtxTrans, mtxScail;
	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

	// ���f���f�[�^�̎擾
	CResourceModel::Model model = *GetModelData();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&model.mtxWorld);

	//�T�C�Y�𔽉f
	D3DXMatrixScaling(&mtxScail, model.size.x, model.size.y, model.size.z);
	D3DXMatrixMultiply(&model.mtxWorld, &model.mtxWorld, &mtxScail);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, model.rot.y, model.rot.x, model.rot.z);
	D3DXMatrixMultiply(&model.mtxWorld, &model.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, model.pos.x, model.pos.y, model.pos.z);
	D3DXMatrixMultiply(&model.mtxWorld, &model.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &model.mtxWorld);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	if (m_shader.pEffect != NULL)
	{
		if (model.pBuffMat != NULL)
		{
			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)model.pBuffMat->GetBufferPointer();

			// �e�N�j�b�N
			m_shader.pEffect->SetTechnique("TexShader");

			// �p�X���̎擾
			UINT numPass = 0;
			m_shader.pEffect->Begin(&numPass, 0);

			for (int nCntMat = 0; nCntMat < (int)model.nNumMat; nCntMat++)
			{
				if (model.apTexture[nCntMat] != NULL)
				{
					// �V�F�[�_�̏I��
					m_shader.pEffect->End();
					// �e�N�j�b�N
					m_shader.pEffect->SetTechnique("TexShader");

					// �p�X���̎擾
					numPass = 0;
					m_shader.pEffect->Begin(&numPass, 0);
				}
				else
				{
					// �V�F�[�_�̏I��
					m_shader.pEffect->End();
					// �e�N�j�b�N
					m_shader.pEffect->SetTechnique("NotTexShader");

					// �p�X���̎擾
					numPass = 0;
					m_shader.pEffect->Begin(&numPass, 0);
				}

				// ���_�ʒu
				m_shader.pEffect->SetFloatArray("Eye", (float*)&D3DXVECTOR3(-0.0f, 2000.0f, -3000.0f), 3);

				// �V�F�[�_�ɏ��
				D3DXMATRIX mat;
				D3DXMatrixIdentity(&mat);

				int nDrawCnt = CManager::GetRenderer()->GetDrawCount();
				mat = model.mtxWorld * (*CGame::GetCamera()->GetViewMtx())* (*CGame::GetCamera()->GetProjectionMtx());
				m_shader.pEffect->SetMatrix("WorldViewProj", &mat);                                                // �v���W�F�N�V����
				m_shader.pEffect->SetMatrix("World", &model.mtxWorld);                                                    // ���[���h
				m_shader.pEffect->SetFloatArray("SpecularColor", (float*)&D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 4); // �X�y�L�����J���[
				m_shader.pEffect->SetFloatArray("LightDirection", LIGHT_DIR, 3);                                   // ���C�g�f�B���N�V����
				m_shader.pEffect->SetTexture("CubeTex", m_shader.pCubeTex);                                        // �L���[�u�e�N�X�`��

				// �p�X�����`�揈���̃��[�v
				for (int nCntEffect = 0; nCntEffect < (int)numPass; nCntEffect++)
				{
					//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
					pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// �e�N�X�`��
					pDevice->SetTexture(0, model.apTexture[nCntMat]);
					// �e�N�X�`��
					m_shader.pEffect->SetTexture("Tex", model.apTexture[nCntMat]);

					// �F
					m_shader.pEffect->SetFloatArray("DiffuseColor", (float*)&pMat[nCntMat].MatD3D.Diffuse, 4);
					
					// �V�F�[�_�p�X�̕`��J�n
					m_shader.pEffect->BeginPass(nCntEffect);

					// ���f���p�[�c�̕`��
					model.pMesh->DrawSubset(nCntMat);
					
					// �V�F�[�_�p�X�̏I��
					m_shader.pEffect->EndPass();

					pMat[nCntMat] = model.defMat[nCntMat];
				}
			}
		}
		// �V�F�[�_�̏I��
		m_shader.pEffect->End();
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
	// ���C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}