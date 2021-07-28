//=============================================================================
//
// ����w�b�_ [snow.h]
// Author : AYANO KUDO
//
//=============================================================================
//��d�C���N���[�h�h�~
#ifndef _SNOW_H_
#define _SNOW_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSnow : CScene2d
{
    static CSnow * m_pInstance;// �C���X�^���X�ւ̃|�C���^
    CSnow();
public:
    ~CSnow();

    static CSnow* Create(void);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void Scroll(void);

    // Get�֐�
    static CSnow* GetInstancce(void) { return m_pInstance; }        // �C���X�^���X�̃Q�b�^

private:
    D3DXVECTOR2 m_Speed;            // uv�̈ړ��X�s�[�h
    D3DXVECTOR2 m_vtx[NUM_VERTEX];  // UV���W

};

#endif // _SNOW_H_
