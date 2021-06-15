//=============================================================================
//
// camera�w�b�_ [camera.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene2d.h"

//*****************************
// �N���X��`
//*****************************

//�J�����N���X
class CCamera
{
public:
	//============
	// �����o�֐�
	//============
	CCamera();
	~CCamera();

	// static
	static CCamera *Create(void);  // �N���X����

	virtual HRESULT Init(void);   // ������
	virtual void Uninit(void);	  // �I��
	virtual void Update(void);	  // �X�V
	virtual void SetCamera(void); // �J�����̃Z�b�g

	// �擾
	D3DXVECTOR3 GetPos(void) { return m_posV; }                    // ���W�̎擾
	D3DXMATRIX *GetViewMtx(void) { return &m_mtxView; }              // �r���[�}�g���b�N�X�̎擾
	D3DXMATRIX *GetProjectionMtx(void) { return &m_mtxProjection; }  // �v���W�F�N�V�����}�g���b�N�X�̎擾

	void SetFov(float fFov) { m_fFov = fFov; } // ����p�̃Z�b�g

protected:
	//============
	// �����o�ϐ�
	//============
	D3DXVECTOR3 m_posV;          // �J�����̍��W
	D3DXVECTOR3 m_posR;          // �����_
private:

	D3DXVECTOR3 m_vecU;          // ������x�N�g��
	D3DXMATRIX  m_mtxProjection; // �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX  m_mtxView;       // �r���[�}�g���b�N�X
	float m_fFov;                // ����p
};

#endif