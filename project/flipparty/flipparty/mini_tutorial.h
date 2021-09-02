//=============================================================================
//
// �e�Q�[���̃`���[�g���A���w�b�_ [mini_tutorial.h]
// Author : AYANO KUDO
//
//=============================================================================
//��d�C���N���[�h�h�~
#ifndef _MINI_TUTORIAL_H_
#define _MINI_TUTORIAL_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "resource_texture.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMini_Tutorial : public CScene
{
public:
    // �����o�֐�
    CMini_Tutorial();
    ~CMini_Tutorial();

    static CMini_Tutorial* Create(CResourceTexture::TEXTURE_TYPE texture);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    // Get�֐�
    bool GetIsTutorialEnd(void) { return m_IsTutorialEnd;}

private:
    // �����o�ϐ�
    static LPDIRECT3DTEXTURE9 m_pTexture;                   // �e�N�X�`���ւ̃|�C���^
    CPolygon *m_pPolygon;                                   // �|���S���ւ̃|�C���^
    static CResourceTexture::TEXTURE_TYPE m_TextureData;    // �ǂݍ��ރe�N�X�`���̃f�[�^
    bool m_IsTutorialEnd;// �`���[�g���A�����I�������
};
#endif //!_MINI_TUTORIAL_H_