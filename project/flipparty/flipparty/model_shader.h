//=============================================================================
//
// model_shader�w�b�_ [model_shader.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _MODEL_SHADER_H_
#define _MODEL_SHADER_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "model.h"

//*****************************
// �}�N����`
//*****************************

//*****************************
// �O���錾
//*****************************

//*****************************
// �N���X��`
//*****************************

// �L�����N�^�[�N���X
class CModelShader : public CModel
{
public:
	//==========================
	// ��
	//==========================


	//==========================
	// �����o�֐�
	//==========================
	CModelShader(int nPliority = OBJTYPE_NONE);
	~CModelShader();

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

	// �Z�b�^�[�E�Q�b�^�[
	// �V�F�[�_�[�\����
	void SetShader(Shader shader) { m_shader = shader; }
	Shader GetShader(void) { return m_shader; }

private:

	//==========================
	// �����o�ϐ�
	//==========================
	Shader m_shader;    // �V�F�[�_�[�\����
};
#endif