////////////////////////////////////////////////////
//
//    Resource_Shader�N���X�̏���[Resource_Shader.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "Resource_Shader.h"
#include "renderer.h"
#include "manager.h"

//******************************
// �}�N����`
//******************************

//******************************
// �ÓI�����o�ϐ��錾
//******************************
CResourceShader *CResourceShader::m_pSingleTex = NULL; // shader�|�C���^*�V���O���g���p

//shader�̃p�X
const std::string CResourceShader::m_aEffectPath[CResourceShader::SHADER_MAX]
{
	"data/HLSL/PlayerShader.fx",       // �v���C���[
	"data/HLSL/CloudShader.fx",        // �_
	"data/HLSL/ZValuePlot.fx",         // Z�l�e�N�X�`��
	
};

// �e�N�j�b�N��
const std::string CResourceShader::m_aTechniqueName[CResourceShader::SHADER_MAX]
{
	"Shader",        // �v���C���[
	"Shader",        // �_
	"ZValuePlotTec", // Z�l�e�N�X�`��
};

//===================================
// �R���X�g���N�^
//===================================
CResourceShader::CResourceShader()
{
	memset(&m_apShader, 0, sizeof(m_apShader));
}

//===================================
// �f�X�g���N�^
//===================================
CResourceShader::~CResourceShader()
{
}

//=============================================================================
//���f���N���X�̃N���G�C�g����
//=============================================================================
CResourceShader * CResourceShader::Create(void)
{
	if (m_pSingleTex == NULL)
	{
		// �������m��
		m_pSingleTex = new CResourceShader;

		if (m_pSingleTex != NULL)
		{
			// �������m�ۂɐ��������Ƃ�
			m_pSingleTex->Load();
		}
		else
		{
			// �������m�ۂɎ��s�����Ƃ�
			return NULL;
		}
	}

	return m_pSingleTex;
}

//===================================
// �N���X�̔j��
//===================================
void CResourceShader::Release(void)
{
	if (m_pSingleTex != NULL)
	{
		// �e�N�X�`���j��
		m_pSingleTex->Unload();
		// �������̔j��
		delete m_pSingleTex;
		m_pSingleTex = NULL;
	}
}

//===================================
// �e�N�X�`���擾
//===================================
CResourceShader::Shader CResourceShader::GetShader(SHADER_TYPE type)
{
	return m_pSingleTex->m_apShader[type];
}

//===================================
// �e�N�X�`���ǂݍ���
//===================================
void CResourceShader::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���������[�v
	for (int nCnt = 0; nCnt < SHADER_MAX; nCnt++)
	{
		// HLSL�t�@�C���̓ǂݍ���
		D3DXCreateEffectFromFile(pDevice, m_aEffectPath[nCnt].c_str(), NULL, NULL, 0, NULL, &m_apShader[nCnt].pEffect, NULL);

		// �e�N�j�b�N��
		sprintf(&m_apShader[nCnt].achTechniqueName[0], "%s", m_aTechniqueName[nCnt].c_str());

		// �e�N�j�b�N�̃Z�b�g
		m_apShader[nCnt].pEffect->SetTechnique(m_apShader[nCnt].achTechniqueName);
	}
}

//===================================
// �e�N�X�`���j��
//===================================
void CResourceShader::Unload(void)
{
	// �e�N�X�`���������[�v
	for (int nCnt = 0; nCnt < SHADER_MAX; nCnt++)
	{
		if (m_apShader[nCnt].pEffect != NULL)
		{
			// �e�N�X�`���̔j��
			m_apShader[nCnt].pEffect->Release();
			m_apShader[nCnt].pEffect = NULL;
		}
	}
}
