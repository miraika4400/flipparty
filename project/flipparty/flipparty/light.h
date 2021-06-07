//=============================================================================
//
// light�w�b�_[light.h]
// Author :���V ����
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"

//*****************************
// �}�N����`
//*****************************
#define LIGHT_DIR  D3DXVECTOR3(0.0f, -1.0f, -0.2f)// ���C�g�̕���

//*****************************
// �O���錾
//*****************************


//*****************************
// �N���X��`
//*****************************
// ���C�g�N���X
class CLight
{
public:
	//============
	//�����o�֐�
	//============
	CLight();
	~CLight();

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V

private:
	//============
	// �����o�ϐ�
	//============
	D3DLIGHT9 m_Light;	// ���C�g
};


#endif