//=============================================================================
//
// �L���Q�[���̃J�����w�b�_ [camera_remember.h]
// Author : AYANO KUDO
//
//=============================================================================
//��d�C���N���[�h�h�~
#ifndef _CAMERA_REMEMBER_H_
#define _CAMERA_REMEMBER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "camera_base.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCameraRemember : public CCamera
{
    static CCameraRemember* m_pInsutance;// �I�u�W�F�N�g�̃|�C���^
public:

    //============
    // �����o�֐�
    //============
    CCameraRemember();
    ~CCameraRemember();

    static CCameraRemember *Create(void);

    HRESULT Init(void);
    void Update(void);
    void SetCamera(void);

    void CameraMove(void);

    // Get�֐�
    static CCameraRemember* GetInsutance(void) { return m_pInsutance; }// �I�u�W�F�N�g�̃|�C���^���擾

    // Set�֐�
    void SetDest(float fDest);
private:
    int m_nDist;// �ړ������ǂ���
    float m_fCameraDest;// �J�����̈ړ��W��

};

#endif //_CAMERA_REMEMBER_H_