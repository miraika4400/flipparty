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

		FLIPPER_TYPE_LEFT = 0,  // ��
		FLIPPER_TYPE_RIGHT,     // �E
		FLIPPER_TYPE_MAX
	}FLIPPER_TYPE;

	// ���������
	typedef enum
	{
		FLIPPER_STATE_NONE = 0, // none
		FLIPPERSTATE_UP,       // �オ���Ă�
		FLIPPERSTATE_DOWN,     // �������Ă���
		FLIPPER_STATE_MAX
	}FLIPPER_STATE;

	//============
	// �����o�֐�
	//============

	CFlipper();
	~CFlipper();
	static CFlipper *Create(void); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��

	// ���̏�Ԏ擾�E�Z�b�g
	FLIPPER_STATE GetState(FLIPPER_TYPE type) { return m_flagState[type]; } // �擾 ����:�擾�����������E������
	void SetState(FLIPPER_TYPE type, FLIPPER_STATE state) { m_flagState[type] = state; }// �Z�b�g ����:�Z�b�g�����������E������,�Z�b�g������

private:
	//============
	// �����o�ϐ�
	//============
	FLIPPER_STATE m_flagState[FLIPPER_TYPE_MAX];
};

#endif