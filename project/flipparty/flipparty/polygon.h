//=============================================================================
//
// polygon�w�b�_ [polygon.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"

//*****************************
//�N���X��`
//*****************************

//�|���S���N���X
class CPolygon
{
public:

	//============
	// �����o�֐�
	//============
	CPolygon();
	~CPolygon();
	static CPolygon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// �N���X����

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col);  // ������
	void Uninit(void);                                                                 // �I��
	void Update(void);                                                                 // �X�V
	void Draw(void);                                                                   // �`��

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }  // �e�N�X�`���̊��蓖��
	LPDIRECT3DTEXTURE9 GetTexture(void) { return m_pTexture ; }               // �e�N�X�`���̎擾����
	void SetVertexPos(D3DXVECTOR3 pos[NUM_VERTEX]);                           // ���_���W�̐ݒ�
	void SetColor(const D3DXCOLOR col);                                       // �F�̐ݒ�
	void SetAddMode(bool bBool) { m_bAddMode = bBool; }  // ���Z���[�h�̃Z�b�g

private:
	//============
	// �����o�ϐ�
	//============
	LPDIRECT3DTEXTURE9        m_pTexture;  // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;  // ���_�o�b�t�@�ւ̃|�C��
	bool m_bAddMode;                     // ���Z������
};

#endif