//=============================================================================
//
// camera�w�b�_ [camera.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _CAMERA_FLY_GAME_H_
#define _CAMERA_FLY_GAME_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "camera_base.h"

//*****************************
// �N���X��`
//*****************************

// �A�ŃQ�[���̃J�����N���X
class CFlyGameCamera : public CCamera
{
public:
	//============
	// �����o�֐�
	//============
	CFlyGameCamera();
	~CFlyGameCamera();

	// static
	static CFlyGameCamera *Create(void);  // �N���X����

	HRESULT Init(void);   // ������
	void Update(void);	  // �X�V
	void SetCamera(void); // �J�����̃Z�b�g

private:
};

#endif