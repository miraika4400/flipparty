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
	"./data/Textures/tutorial_0.png",   // �`���[�g���A��
    "./data/Textures/tutorial_1.png",   // �`���[�g���A��
    "./data/Textures/tutorial_2.png",   // �`���[�g���A��
    "./data/Textures/tutorial_3.png",   // �`���[�g���A��
	"./data/Textures/particle001.png",  // �p�[�e�B�N��*��
	"./data/Textures/Tears.png",        // �p�[�e�B�N��*��
	"./data/Textures/particle004.png",  // �p�[�e�B�N��*�~
	"./data/Textures/number.png",       // �i���o�[
	"./data/Textures/debug_left.png",   // ��
	"./data/Textures/debug_right.png",  // �E
	"./data/Textures/debug_up.png",     // ��
	"./data/Textures/debug_down.png",   // ��
	"./data/Textures/1p_ui.png",        // 1p�A�C�R��
	"./data/Textures/2p_ui.png",        // 2p�A�C�R��
	"./data/Textures/3p_ui.png",        // 3p�A�C�R��
	"./data/Textures/4p_ui.png",        // 4p�A�C�R��
	"./data/Textures/select2.png",      // �l���I��UI2�l
	"./data/Textures/select3.png",      // �l���I��UI3�l
	"./data/Textures/select4.png",      // �l���I��UI4�l
	"./data/Textures/Toon_Shadow.png",  // �g�D�[���V���h�E
	"./data/Textures/Toon_Shadow_Cloud.png",  // �g�D�[���V���h�E*�_
	"./data/Textures/Toon_Shadow_Iceberg.png",  // �g�D�[���V���h�E*�X�R
    "./data/Textures/remenber_right_flag_up.png",        // UI �E����グ���Ƃ��i�L���Q�[���Ŏg�p�j
    "./data/Textures/remenber_left_flag_up.png",      // UI ������������Ƃ��i�L���Q�[���Ŏg�p�j
    "./data/Textures/UI_maru.png",      // UI�u�Z�v
    "./data/Textures/UI_batu.png",      // UI�u�~�v
    "./data/Textures/UI000.png",        // UI �v���C���[�ԍ��i�L���Q�[���Ŏg�p�j
    "./data/Textures/UI001.png",        // UI�u�̂΂�ł��v�i�L���Q�[���Ŏg�p�j
	"./data/Textures/ranking.png",      // UI�u����]
	"./data/Textures/blind.jpg",		// �u���C���h
	"./data/Textures/right_flag_up.png",	// UI�@�E�グ
	"./data/Textures/right_flag_down.png",	// UI�@�E����
	"./data/Textures/left_flag_up.png", 	// UI�@���グ
	"./data/Textures/left_flag_down.png",	// UI�@������
	"./data/Textures/thunder.png",         // ���G�t�F�N�g
	"./data/Textures/snow.png",            // ����G�t�F�N�g
	"./data/Textures/Icon_FlagRacing.png", // ���g���Q�[���A�C�R��
	"./data/Textures/Icon_Fly.png",        // �A�ŃQ�[���A�C�R��
	"./data/Textures/Icon_Remenber.png",   // �L���Q�[���A�C�R��
	"./data/Textures/resultboard_back.png", // ���U���g�{�[�h�w�i
	"./data/Textures/warning.png",          // �x��
	"./data/Textures/penguin_shadow.png",   // �y���M���̉e
	"./data/Textures/strat_icon.png",       // START�A�C�R��
	"./data/Textures/result.png",           // ���U���g���S
	"./data/Textures/end_icon.png",          // END�A�C�R��
	"./data/Textures/answer_polygon.png",          // ���_�\��
	"./data/Textures/mini_result.png",          // �~�j���U���g���S
	"./data/Textures/penguin_shadow.png",          // �~�j���U���g���S
	"./data/Textures/point_ui.png",          // �~�j���U���g���S
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
	int n = 0;
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
