////////////////////////////////////////////////////
//
//    scene3d�N���X�̏���[scene3d.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "resource_texture.h"
#include "renderer.h"
#include "manager.h"

//******************************
// �}�N����`
//******************************

//******************************
// �ÓI�����o�ϐ��錾
//******************************
CResourceTexture *CResourceTexture::m_pSingleTex = NULL; // �e�N�X�`���N���X�̃|�C���^*�V���O���g���p
// �e�N�X�`���̃p�X
const std::string CResourceTexture::m_aTexPath[CResourceTexture::TEXTURE_MAX]
{
	"./data/Textures/title.png",        // �^�C�g���w�i
	"./data/Textures/tutorial_1.png",   // �`���[�g���A��
	"./data/Textures/particle001.png",  // �p�[�e�B�N��*��
	"./data/Textures/particle000.png",  // �p�[�e�B�N��*��
	"./data/Textures/particle004.png",  // �p�[�e�B�N��*�~

};

//===================================
// �R���X�g���N�^
//===================================
CResourceTexture::CResourceTexture()
{
	memset(&m_apTexture, 0, sizeof(m_apTexture));
}

//===================================
// �f�X�g���N�^
//===================================
CResourceTexture::~CResourceTexture()
{
}

//=============================================================================
//���f���N���X�̃N���G�C�g����
//=============================================================================
CResourceTexture * CResourceTexture::Create(void)
{
	if (m_pSingleTex == NULL)
	{
		// �������m��
		m_pSingleTex = new CResourceTexture;

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
void CResourceTexture::Release(void)
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
LPDIRECT3DTEXTURE9 CResourceTexture::GetTexture(TEXTURE_TYPE type)
{
	if (m_pSingleTex != NULL)
	{
		return m_pSingleTex->m_apTexture[type];
	}
	else
	{
		return NULL;
	}
}

//===================================
// �e�N�X�`���ǂݍ���
//===================================
void CResourceTexture::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���������[�v
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		// �e�N�X�`���̐���
		D3DXCreateTextureFromFile(pDevice, m_aTexPath[nCnt].c_str(), &m_apTexture[nCnt]);
	}
}

//===================================
// �e�N�X�`���j��
//===================================
void CResourceTexture::Unload(void)
{
	// �e�N�X�`���������[�v
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			// �e�N�X�`���̔j��
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
