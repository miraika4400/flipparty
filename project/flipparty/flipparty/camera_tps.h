//=============================================================================
//
// camera�w�b�_ [camera.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _CAMERA_TPS_H_
#define _CAMERA_TPS_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "camera_base.h"

//*****************************
// �N���X��`
//*****************************

// �O�l�̃J�����N���X
class CTpsCamera : public CCamera
{
public:
	//============
	// �����o�֐�
	//============
	CTpsCamera();
	~CTpsCamera();

	// static
	static CTpsCamera *Create(void);  // �N���X����

	HRESULT Init(void);   // ������
	void Update(void);	  // �X�V

private:

	// ���ʍ��W
	float m_fRad;                // �ڕW����̋���
	float m_fTheta;              // �p�x�V�[�^
	float m_fPhi;                // �p�x�t�@�C
};

#endif