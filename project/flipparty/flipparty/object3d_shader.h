//=============================================================================
//
// scene3d_shader�w�b�_ [scene3d_shader.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _SCENE3D_SHADER_H_
#define _SCENE3D_SHADER_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
// �}�N����`
//*****************************
#define MAX_TEHNIQUENAME_LENGTH_OBJ 64

//*****************************
//�N���X��`
//*****************************

//3d�|���S���N���X
class CObject3dShader : public CScene
{
public:
	//============
	// �\���̒�`
	//============
	// ���_���
	typedef struct
	{
		D3DXVECTOR3 pos; // ���W
		D3DXVECTOR3 nor; // �@��
		D3DXVECTOR2 tex; // �e�N�X�`��uv
		D3DXVECTOR3 tangent;// �ڐ�
		D3DCOLOR    col; // �F
	}VERTEX_3D_SHADER;

	// �V�F�[�_�[�\����
	typedef struct
	{
		LPD3DXEFFECT pEffect;                             // �G�t�F�N�g�t�@�C��
		char achTechniqueName[MAX_TEHNIQUENAME_LENGTH_OBJ];   // HLSL�e�N�j�b�N�l�[��
		LPDIRECT3DCUBETEXTURE9 pCubeTex;                  // �L���[�u�e�N�X�`���|�C���^
	}Shader;

	//============
	// �����o�֐�
	//============
	CObject3dShader(int nPriority = 3);
	~CObject3dShader();

	static CObject3dShader *Create(void); // �N���X����

	HRESULT Init(void);                                                            // ������
	void Uninit(void);                                                             // �I��
	void Update(void);                                                             // �X�V
	void Draw(void);                                                               // �`��
	LPDIRECT3DTEXTURE9 GetTexture(void) { return m_pTexture; }                     // �e�N�X�`���̎擾
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; } // �e�N�X�`���̊��蓖��

																				   // ���S���W�̃Z�b�g�A�擾
	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	// ��]�̃Z�b�g�A�擾
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	// �T�C�Y�̃Z�b�g�A�擾
	void SetSize(const D3DXVECTOR3 size);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	// �J���[�̃Z�b�g�A�擾
	void SetColor(const D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }

	void SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX]); // �e�N�X�`����UV���W�̃Z�b�g
	void SetAddMode(bool bBool) { m_bAddMode = bBool; }  // ���Z���[�h�̐؂�ւ�

	Shader GetShader(void) { return m_shader; }
	void SetShader(Shader shader) { m_shader = shader; }  // �V�F�[�_�[�̃Z�b�g

private:
	virtual void SetShaderValue(void); // �V�F�[�_�[�̒l�Z�b�g����

									   //============
									   // �����o�ϐ�
									   //============
	Shader m_shader;    // �V�F�[�_�[�\����
	LPDIRECT3DTEXTURE9		m_pTexture;         // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;         // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;                          // �|���S���̈ʒu
	D3DXVECTOR3	m_rot;                          // �|���S���̉�]
	D3DXVECTOR3 m_size;                         // �|���S���̃T�C�Y
	D3DXCOLOR   m_col;                          // �F
	D3DXMATRIX  m_mtxWorld;                     // ���[���h�}�g���b�N�X
	bool        m_bAddMode;                     // ���Z������
	LPDIRECT3DINDEXBUFFER9 m_pldxBuff = NULL;   // �e�N�X�`��
	LPDIRECT3DVERTEXDECLARATION9 m_pDecl;       // ���_�錾
};

#endif