//=============================================================================
//
// texture�w�b�_ [texture.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"

//*****************************
//�N���X��`
//*****************************

//�e�N�X�`���N���X
class CResourceTexture
{
public:
	// ��
	// �e�N�X�`�����
	typedef enum
	{
		TEXTURE_TITLE = 0,       // �^�C�g��
		TEXTURE_TUTORIAL,        // �`���[�g���A��
		TEXTURE_PARTICLE_BOX,    // �p�[�e�B�N��*��
		TEXTURE_PARTICLE_STAR,   // �p�[�e�B�N��*��
		TEXTURE_PARTICLE_CIRCLE, // �p�[�e�B�N��*�~
		TEXTURE_MAX        // �e�N�X�`����
	}TEXTURE_TYPE;
	
	// �����o�֐�
	static CResourceTexture * Create(void);                          // �N���X����
	static void Release(void);                               // �N���X�j��
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE type); // �e�N�X�`���̎擾����*�����F�擾�������e�N�X�`��
	
private:
	CResourceTexture();//�B���R���X�g���N�^
public:
	~CResourceTexture();

private:
	void Load(void); // �e�N�X�`���ǂݍ���
	void Unload(void); // �e�N�X�`���j��

	// �����o�ϐ�
	static const std::string m_aTexPath[TEXTURE_MAX]; // �e�N�X�`���̃p�X
	static CResourceTexture *m_pSingleTex;                    // �e�N�X�`���N���X�̃|�C���^*�V���O���g���p
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];      // �e�N�X�`���̃|�C���^
};

#endif