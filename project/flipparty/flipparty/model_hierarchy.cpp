//=============================================================================
//
// ���f������ [ModelHirarchy.cpp]
// Author : ���V����
//
//=============================================================================
#include "model_hierarchy.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CModelHierarchy::CModelHierarchy(int nPriority) :CScene(nPriority)
{
	// �ϐ��̃N���A
	memset(&m_model, 0, sizeof(m_model));
	m_nNumParts = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	for (int nCnt = 0; nCnt < MAX_PARTS_NUM; nCnt++)
	{
		m_model[nCnt].size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CModelHierarchy::~CModelHierarchy()
{
}

//=============================================================================
// �K�w�\���̓ǂݍ��݃N���X
//=============================================================================
void CModelHierarchy::LoadModels(char * pPath, CResourceModel::Model *model,int * pNumModel)
{
	// �t�@�C���I�[�v��
	FILE*pFile = NULL;
	pFile = fopen(pPath, "r");

	if (pFile != NULL)
	{
		// �e�L�X�g�t�@�C���̉��

		char chChar[256] = {};
		fscanf(pFile, "%s", chChar);

		// "NUM_MODEL"�ǂݍ��ނ܂Ń��[�v
		while (strcmp(chChar, "NUM_MODEL") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}

		// �ǂݍ��ރ��f���̐�
		fscanf(pFile, "%*s %d # %*s", pNumModel);

		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		for (int nCnt = 0; nCnt < *pNumModel; nCnt++)
		{
			// �ǂݍ��񂾕����i�[�p
			char chPath[64] = {};
			// "MODEL_FILENAME"��ǂݍ��ނ܂Ń��[�v
			while (strcmp(chChar, "MODEL_FILENAME") != 0)
			{
				fscanf(pFile, "%s", chChar);
			}
			// �t�@�C���p�X�̓ǂݍ���
			fscanf(pFile, "%*s %s", chPath);

			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(chPath,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&model[nCnt].pBuffMat,
				NULL,
				&model[nCnt].nNumMat,
				&model[nCnt].pMesh);

			// �e�N�X�`���ǂݍ���
			if (model[nCnt].nNumMat != 0)
			{
				D3DXMATERIAL*pMat = (D3DXMATERIAL*)model[nCnt].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)model[nCnt].nNumMat; nCntMat++)
				{
					model[nCnt].defMat[nCntMat] = pMat[nCntMat];
					if (pMat[nCntMat].pTextureFilename != NULL)
					{
						char cPath[128] = {};
						sprintf(cPath, "./data/Textures/%s", pMat[nCntMat].pTextureFilename);
						// �e�N�X�`���̐���
						D3DXCreateTextureFromFile(pDevice, cPath, &model[nCnt].apTexture[nCntMat]);
					}
				}
			}

			// ���̕�����ǂݍ���
			fscanf(pFile, "%s", chChar);
		}
	}
}

//=============================================================================
//�e�L�X�g�t�@�C���̓ǂݍ���
//=============================================================================
void CModelHierarchy::LoadHierarchy(CResourceModel::Model * model, char * pPath)
{
	// �t�@�C���I�[�v��
	FILE*pFile = NULL;
	pFile = fopen(pPath, "r");

	// �p�[�c��
	int nPartsNum = 0;

	if (pFile != NULL)
	{
		// �e�L�X�g�t�@�C���̉��

		char chChar[256] = {};
		fscanf(pFile, "%s", chChar);

		// "SCRIPT"�ǂݍ��ނ܂Ń��[�v
		while (strcmp(chChar, "CHARACTERSET") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}

		// �����r���p
		char cString[32] = {};

		fscanf(pFile, "%s %s %d", &cString, &cString, &nPartsNum);

		// "END_PARTSSET"�ǂݍ��ނ܂Ń��[�v
		while (strcmp(chChar, "END_CHARACTERSET") != 0)
		{
			fscanf(pFile, "%s", chChar);
			if (strcmp(chChar, "PARTSSET") == 0)
			{
				// �C���f�b�N�X�ꎞ�ۊǗp
				int nIndex = 0;
				// �C���f�b�N�X�̓ǂݍ���
				fscanf(pFile, "%*s %*s %d # %*s", &nIndex);
				// �e�ԍ��̓ǂݍ���
				fscanf(pFile, "%*s %*s %d # %*s", &model[nIndex].nParent);
				// ���W�̓ǂݍ���
				fscanf(pFile, "%*s %*s %f %f %f", &model[nIndex].pos.x, &model[nIndex].pos.y, &model[nIndex].pos.z);
				// ��]�̓ǂݍ���
				fscanf(pFile, "%*s %*s %f %f %f", &model[nIndex].rot.x, &model[nIndex].rot.y, &model[nIndex].rot.z);

				fscanf(pFile, "%*s");
			}

		}
		fclose(pFile);
	}
}

//=============================================================================
//����������
//=============================================================================
HRESULT CModelHierarchy::Init(void)
{

	return S_OK;
}

HRESULT CModelHierarchy::Init(int nNumParts, CResourceModel::Model * model, char*pPath)
{
	LoadHierarchy(model, pPath);
	// �����̑��
	m_nNumParts = nNumParts;
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_model[nCnt] = model[nCnt];

		for (int nCntMat = 0; nCntMat < (int)m_model[nCnt].nNumMat; nCntMat++)
		{
			m_model[nCnt].defMat[nCntMat] = ((D3DXMATERIAL*)m_model[nCnt].pBuffMat->GetBufferPointer())[nCntMat];

		}
	}

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CModelHierarchy::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CModelHierarchy::Update(void)
{
}

//=============================================================================
//�`�揈��
//=============================================================================
void CModelHierarchy::Draw(void)
{
	// ���W�A�T�C�Y�A��]�̐ݒ�
	SetWorldmtx();
	// ���f���̕`�揈��
	DrawModel();
}

//=============================================================================
//���f���f�[�^�̃Z�b�g
//=============================================================================
void CModelHierarchy::SetModelData(CResourceModel::Model *pModel)
{
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		m_model[nCnt].pos = pModel[nCnt].pos;
		m_model[nCnt].rot = pModel[nCnt].rot;
	}
}

//=============================================================================
//���[���h�}�g���b�N�X�̐ݒ�
//=============================================================================
void CModelHierarchy::SetWorldmtx(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// ��]�A�ʒu�A�T�C�Y�s��
	D3DXMATRIX mtxRot, mtxTrans, mtxScail;

	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_model[nCntParts].mtxWorld);

		if (m_model[nCntParts].nParent == -1)
		{// ��������Ԃ̐e�̂Ƃ�

		 //�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_model[nCntParts].rot.y, m_model[nCntParts].rot.x, m_model[nCntParts].rot.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxRot, m_model[nCntParts].pos.x, m_model[nCntParts].pos.y, m_model[nCntParts].pos.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxTrans);

		}
		else
		{// ��������Ԃ̐e����Ȃ��Ƃ�

		 //�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_model[nCntParts].rot.y, m_model[nCntParts].rot.x, m_model[nCntParts].rot.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, m_model[nCntParts].pos.x, m_model[nCntParts].pos.y, m_model[nCntParts].pos.z);
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &mtxTrans);

			// �e�̃��[���h�}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&m_model[nCntParts].mtxWorld, &m_model[nCntParts].mtxWorld, &m_model[m_model[nCntParts].nParent].mtxWorld);
		}
	}
}

//=============================================================================
//���f���̕`�揈��
//=============================================================================
void CModelHierarchy::DrawModel(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_model[nCntParts].mtxWorld);

		//���݂̃}�e���A�����擾����
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾

		pMat = (D3DXMATERIAL*)m_model[nCntParts].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_model[nCntParts].nNumMat; nCntMat++)
		{
			//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
			pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// �e�N�X�`��
			pDevice->SetTexture(0, m_model[nCntParts].apTexture[nCntMat]);
			//���f���p�[�c�̕`��
			m_model[nCntParts].pMesh->DrawSubset(nCntMat);

			pMat[nCntMat] = m_model[nCntParts].defMat[nCntMat];
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
		// �e�N�X�`���̏�����
		pDevice->SetTexture(0, 0);
	}
}
