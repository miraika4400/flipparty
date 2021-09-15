//=============================================================================
//
// �e�Q�[���̃`���[�g���A���N���X [mini_tutorial.cpp]
// Author : AYANO KUDO
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "mini_tutorial.h"
#include "manager.h"
#include "joypad.h"
#include "keyboard.h"
#include "renderer.h"
#include "mouse.h"
#include "resource_texture.h"
#include "polygon.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CMini_Tutorial::m_pTexture = nullptr;    // �e�N�X�`���ւ̃|�C���^
CResourceTexture::TEXTURE_TYPE CMini_Tutorial::m_TextureData = CResourceTexture::TEXTURE_TUTORIAL;

//=============================================================================
// [CMini_Tutorial]�R���X�g���N�^
//=============================================================================
CMini_Tutorial::CMini_Tutorial() : CScene(OBJTYPE_SYSTEM)
{
    m_pPolygon = NULL;
    m_IsTutorialEnd = false;
}

//=============================================================================
// [~CMini_Tutorial]�f�X�g���N�^
//=============================================================================
CMini_Tutorial::~CMini_Tutorial()
{
}

//=============================================================================
// [Create]�I�u�W�F�N�g�̐���
//=============================================================================
CMini_Tutorial *CMini_Tutorial::Create(CResourceTexture::TEXTURE_TYPE texture)
{
    CMini_Tutorial *pMiniTutorial = new CMini_Tutorial;

    m_TextureData = texture;

    // ����������
    pMiniTutorial->Init();

    return pMiniTutorial;
}

//=============================================================================
// [Init]����������
//=============================================================================
HRESULT CMini_Tutorial::Init(void)
{
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    // �e�N�X�`���̐���
    m_pTexture = CResourceTexture::GetTexture(m_TextureData);

    m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
        D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
        D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

    m_pPolygon->BindTexture(m_pTexture);
    return S_OK;
}

//=============================================================================
// [Uninit]�I������
//=============================================================================
void CMini_Tutorial::Uninit(void)
{
    if (m_pPolygon != NULL)
    {
        // �|���S���̏I������
        m_pPolygon->Uninit();

        // �������̉��
        delete m_pPolygon;
        m_pPolygon = NULL;
    }

    // �J������
    Release();
}

//=============================================================================
// [Update]�X�V����
//=============================================================================
void CMini_Tutorial::Update(void)
{
    // ENTER�L�[�����ŃQ�[���J�n�t���O
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
        CManager::GetMouse()->GetMouseTrigger(0) ||
        CManager::GetJoypad()->GetJoystickTrigger(3, 0))
    {
        m_IsTutorialEnd = true;// �`���[�g���A���I���t���O��true�ɂ���
    }

}

//=============================================================================
// [Draw]�`�揈��
//=============================================================================
void CMini_Tutorial::Draw(void)
{
    // �|���S���̕`�揈��
    m_pPolygon->Draw();
}
