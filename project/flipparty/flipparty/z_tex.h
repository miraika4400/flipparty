//=============================================================================
//
// z_tex�w�b�_ [z_tex.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _ZTEX_H_
#define _ZTEX_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
//*****************************
// �}�N����`
//*****************************

//*****************************
// �O���錾
//*****************************

//*****************************
// �N���X��`
//*****************************

// X�l�e�N�X�`���[�N���X
class CZTex
{
public:
	// �����o�֐�
	CZTex();
	~CZTex();

	static CZTex*Create(void); // �N���X����
	HRESULT Init(void);        // ������
	void Uninit(void);         // �I��
	void Begin(void);          // �e�N�X�`���������݊J�n
	void End(void);            // �������ݏI��

private:
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pZBufTex; // Z�l�e�N�X�`��
	LPDIRECT3DSURFACE9 m_pZTexSurf;  // Z�l�e�N�X�`���T�[�t�F�C�X
	LPDIRECT3DSURFACE9 m_pZTexZBuf;  // �[�x�o�b�t�@�T�[�t�F�C�X
};

#endif
