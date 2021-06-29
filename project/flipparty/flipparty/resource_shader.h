//=============================================================================
//
// Resource_Shader�w�b�_ [Resource_Shader.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _RESOURCE_SHADER_H_
#define _RESOURCE_SHADER_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"

//*****************************
//�}�N����`
//*****************************
#define MAX_TEHNIQUENAME_LENGTH 32// �e�N�j�b�N�������ő�

//*****************************
//�N���X��`
//*****************************

//�e�N�X�`���N���X
class CResourceShader
{
public:
	// ��
	// �e�N�X�`�����
	typedef enum
	{
		SHADER_PLAYER = 0,  // �v���C���[
		SHADER_MAX          // �e�N�X�`����
	}SHADER_TYPE;

	// �V�F�[�_�[�\����
	typedef struct
	{
		LPD3DXEFFECT pEffect;                             // �G�t�F�N�g�t�@�C��
		char achTechniqueName[MAX_TEHNIQUENAME_LENGTH];   // HLSL�e�N�j�b�N�l�[��
		LPDIRECT3DCUBETEXTURE9 pCubeTex;                  // �L���[�u�e�N�X�`���|�C���^
	}Shader;

	// �����o�֐�
	static CResourceShader * Create(void);                          // �N���X����
	static void Release(void);                               // �N���X�j��
	static Shader GetShader(SHADER_TYPE type); // �e�N�X�`���̎擾����*�����F�擾�������e�N�X�`��

private:
	CResourceShader();//�B���R���X�g���N�^
public:
	~CResourceShader();

private:
	void Load(void); // �e�N�X�`���ǂݍ���
	void Unload(void); // �e�N�X�`���j��

	// �����o�ϐ�
	static const std::string m_aEffectPath[SHADER_MAX];    // �e�N�X�`���̃p�X
	static const std::string m_aTechniqueName[SHADER_MAX]; // �e�N�X�`���̃p�X
	static CResourceShader *m_pSingleTex;                    // �e�N�X�`���N���X�̃|�C���^*�V���O���g���p
	Shader m_apShader[SHADER_MAX];      // �e�N�X�`���̃|�C���^
};

#endif