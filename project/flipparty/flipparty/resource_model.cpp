////////////////////////////////////////////////////
//
//    resource_model�N���X�̏���[resource_model.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "resource_model.h"
#include "renderer.h"
#include "manager.h"

//******************************
// �}�N����`
//******************************
#define GENERAL_MODEL_COLOR D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)

//******************************
// �ÓI�����o�ϐ��錾
//******************************
CResourceModel *CResourceModel::m_pSingle = NULL; //���f���N���X�̃|�C���^*�V���O���g���p
// ���f���̃p�X
const std::string CResourceModel::m_aModelPath[CResourceModel::MODEL_MAX]
{
	"PATH_NONE_SPHERE",   // �ėp���f��(��)*x�t�@�C������Ȃ�
	"PATH_NONE_BOX",      // �ėp���f��(��)*x�t�@�C������Ȃ�
	"data/Models/player.x"

};

//===================================
// �R���X�g���N�^
//===================================
CResourceModel::CResourceModel()
{
	memset(&m_apModel, 0, sizeof(m_apModel));
}

//===================================
// �f�X�g���N�^
//===================================
CResourceModel::~CResourceModel()
{
}

//=============================================================================
//���f���N���X�̃N���G�C�g����
//=============================================================================
CResourceModel * CResourceModel::Create(void)
{
	if (m_pSingle == NULL)
	{
		// �������m��
		m_pSingle = new CResourceModel;

		if (m_pSingle != NULL)
		{
			// �������m�ۂɐ��������Ƃ�
			m_pSingle->Load();
		}
		else
		{
			// �������m�ۂɎ��s�����Ƃ�
			return NULL;
		}
	}

	return m_pSingle;
}

//===================================
// �N���X�̔j��
//===================================
void CResourceModel::Release(void)
{
	if (m_pSingle != NULL)
	{
		// �e�N�X�`���j��
		m_pSingle->Unload();
		// �������̔j��
		delete m_pSingle;
		m_pSingle = NULL;
	}
}

//===================================
// ���f���擾
//===================================
CResourceModel::Model* CResourceModel::GetModel(MODEL_TYPE type)
{
	if (m_pSingle != NULL)
	{
		return &m_pSingle->m_apModel[type];
	}
	else
	{
		return NULL;
	}
}

//===================================
// �e�N�X�`���ǂݍ���
//===================================
void CResourceModel::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���f���������[�v
	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
	{
		// ���f���̓ǂݍ���
		if (strcmp(m_aModelPath[nCntModel].c_str(), "PATH_NONE_SPHERE") == 0 || strcmp(m_aModelPath[nCntModel].c_str(), "PATH_NONE_BOX") == 0)
		{// �ėp���f��
			
			// ���f������
			// ��
			if(strcmp(m_aModelPath[nCntModel].c_str(), "PATH_NONE_SPHERE") == 0) D3DXCreateSphere(pDevice, 1, 10, 10, &m_apModel[nCntModel].pMesh, &m_apModel[nCntModel].pBuffMat);
			// ��
			else D3DXCreateBox(pDevice, 1, 1, 1, &m_apModel[nCntModel].pMesh, &m_apModel[nCntModel].pBuffMat);
			
			m_apModel[nCntModel].nNumMat = 1;
			// �F�̏����ݒ�
			D3DXMATERIAL* mat = (D3DXMATERIAL*)m_apModel[nCntModel].pBuffMat->GetBufferPointer();
			mat->MatD3D.Ambient  = GENERAL_MODEL_COLOR;
			mat->MatD3D.Diffuse  = GENERAL_MODEL_COLOR;
			mat->MatD3D.Specular = GENERAL_MODEL_COLOR;
			mat->MatD3D.Emissive = GENERAL_MODEL_COLOR;
		}
		else
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(m_aModelPath[nCntModel].c_str(), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_apModel[nCntModel].pBuffMat, NULL, &m_apModel[nCntModel].nNumMat, &m_apModel[nCntModel].pMesh);

			// �e�N�X�`���ǂݍ���
			if (m_apModel[nCntModel].nNumMat != 0)
			{
				D3DXMATERIAL*pMat = (D3DXMATERIAL*)m_apModel[nCntModel].pBuffMat->GetBufferPointer();
				for (int nCnt = 0; nCnt < (int)m_apModel[nCntModel].nNumMat; nCnt++)
				{
					if (pMat[nCnt].pTextureFilename != NULL)
					{
						char cPath[128] = {};
						sprintf(cPath, "./data/Textures/%s", pMat[nCnt].pTextureFilename);
						// �e�N�X�`���̐���
						D3DXCreateTextureFromFile(pDevice, cPath, &m_apModel[nCntModel].apTexture[nCnt]);
					}
				}
			}
		}
	}
}

//===================================
// �j��
//===================================
void CResourceModel::Unload(void)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// ���b�V���̉��
		if (m_apModel[nCnt].pMesh != NULL)
		{
			m_apModel[nCnt].pMesh->Release();
			m_apModel[nCnt].pMesh = NULL;
		}
		// �o�b�t�@�̉��
		if (m_apModel[nCnt].pBuffMat != NULL)
		{
			m_apModel[nCnt].pBuffMat->Release();
			m_apModel[nCnt].pBuffMat = NULL;
		}

		// �}�e���A���������[�v
		for (int nCntTex = 0; nCntTex < (int)m_apModel[nCnt].nNumMat; nCntTex++)
		{
			// �e�N�X�`���̉��
			if (m_apModel[nCnt].apTexture[nCntTex] != NULL)
			{
				m_apModel[nCnt].apTexture[nCntTex]->Release();
				m_apModel[nCnt].apTexture[nCntTex] = NULL;
			}
		}
	}
}
