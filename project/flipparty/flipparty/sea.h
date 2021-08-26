//=============================================================================
//
// sea�w�b�_ [sea.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _SEA_H_
#define _SEA_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "object3d_shader.h"

//*****************************
// �}�N����`
//*****************************

//*****************************
// �O���錾
//*****************************

//*****************************
// �N���X��`
//*****************************

// �C�N���X
class CSea : public CObject3dShader
{
public:
	//==========================
	// ��
	//==========================
	typedef enum
	{
		TYPE_DIRTY = 0, // ����
		TYPE_NORMAL,    // �ʏ�
		TYPE_EVENING,   // �[��
		TYOE_MAX,
	}SEA_TYPE;

	//==========================
	//�����o�֐�
	//==========================
	CSea();
	~CSea();

	static CSea *Create(const D3DXVECTOR3 pos, const float fWaveSpeed, SEA_TYPE seaType); // �N���X����
	static HRESULT Load(void); // ���[�h
	static void Unload(void);  // �A�����[�h

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:
	void SetShaderValue(void); // HLSL�ɒl�𑗂�

	//==========================
	//�����o�ϐ�
	//==========================
	static Shader m_shader;              // �V�F�[�_�[�\����
	static LPDIRECT3DTEXTURE9 m_apBmpTex[2]; // �o���v�}�b�v�e�N�X�`��
	float m_fWaveaRate; // �g�̌W��
	float m_fWaveSpeed; // �g�̑��x
	SEA_TYPE m_seaType; // �C�^�C�v
};
#endif