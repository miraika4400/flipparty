//=============================================================================
//
// flipper�w�b�_ [flipper.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _FLIPPER_H_
#define _FLIPPER_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"

//*****************************
//�N���X��`
//*****************************

// ���N���X
class CFlipper
{
public:
	//============
	// ��
	//============
	typedef enum
	{
		FLAG_TYPE_LEFT = 0,  // ��
		FLAG_TYPE_RIGHT,     // �E
		FLAG_TYPE_MAX
	}FLAG_TYPE;

	// ���������
	typedef enum
	{
		FLAG_STATE_NONE = 0, // none
		FLAG_STATE_UP,       // �オ���Ă�
		FLAG_STATE_DOWN,     // �������Ă���
		FLAG_STATE_MAX
	}FLAG_STATE;

	//============
	// �����o�֐�
	//============

	CFlipper();
	~CFlipper();
	static CFlipper *Create(void); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��

	// ���̏�Ԏ擾�E�Z�b�g
	FLAG_STATE GetState(FLAG_TYPE type) { return m_flagState[type]; } // �擾 ����:�擾�����������E������
	void SetState(FLAG_TYPE type, FLAG_STATE state) { m_flagState[type] = state; }// �Z�b�g ����:�Z�b�g�����������E������,�Z�b�g������

private:
	//============
	// �����o�ϐ�
	//============
	FLAG_STATE m_flagState[FLAG_TYPE_MAX];
};

#endif