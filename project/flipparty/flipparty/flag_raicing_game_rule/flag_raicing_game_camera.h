//=============================================================================
//
// camera�w�b�_ [camera.h]
// Author : ���� �r�H
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _FLAG_RAICING_GAME_CAMERA_H_
#define _FLAG_RAICING_GAME_CAMERA_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "camera_base.h"

//*****************************
// �N���X��`
//*****************************

// �A�ŃQ�[���̃J�����N���X
class CFlagRaicingGameCamera : public CCamera
{
public:
	//============
	// �����o�֐�
	//============
	CFlagRaicingGameCamera();
	~CFlagRaicingGameCamera();

	// static
	static CFlagRaicingGameCamera *Create(void);  // �N���X����

	HRESULT Init(void);   // ������
	void Update(void);	  // �X�V
	void SetCamera(void); // �J�����̃Z�b�g

private:
};

#endif#pragma once
#pragma once
