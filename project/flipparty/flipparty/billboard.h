//=============================================================================
//
// billboard�w�b�_ [billboard.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//�N���X��`
//*****************************

// �r���{�[�h�N���X
class CBillboard : public CScene
{
public:
	// �����o�֐�
	CBillboard(int nPliority = OBJTYPE_NONE);
	~CBillboard();
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DTEXTURE9 GetTexture(void) { return m_pTexture; }
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }

	// ���S���W�̃Z�b�g�A�擾
	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	// ��]�p�x�̃Z�b�g�A�擾
	void SetAngle(const float fAngle);
	float GetAngle(void) { return m_fAngle; }
	// �T�C�Y�̃Z�b�g�A�擾
	void SetSize(const D3DXVECTOR3 size);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	// �J���[�̃Z�b�g�A�擾
	void SetColor(const D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }

	void SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX]); // �e�N�X�`����UV���W�̃Z�b�g

	void SetAddMode(bool bBool) { m_bAddMode = bBool; }
private:
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture;	 // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	 // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;                   // �|���S���̈ʒu
	D3DXVECTOR3 m_size;                  // �|���S���̃T�C�Y
	float m_fAngle;                      // �|���S���̉�]�p�x
	D3DXCOLOR m_col;                     // �F
	D3DXMATRIX m_mtxWorld;               // ���[���h�}�g���b�N�X
	bool m_bAddMode;                     // ���Z������
	LPDIRECT3DINDEXBUFFER9 m_pldxBuff;
};

#endif