//=============================================================================
//
// �L���Q�[�����[���N���X [remember_rule.cpp]
// Author : AYANOKUDO
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include "joypad.h"
#include "keyboard.h"
#include "polygon.h"
#include "remember_rule.h"
#include "resource_texture.h"
#include "count_selection.h"
#include "player.h"
#include "camera_tps.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_SPACE 150.0f //�@�v���C���[�ʒu�̊Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRememjber_rule* CRememjber_rule::m_pinstace = nullptr;// �C���X�^���X�ւ̃|�C���^

//=============================================================================
// [CRememjber_rule]�R���X�g���N�^
//=============================================================================
CRememjber_rule::CRememjber_rule()
{
    m_nTurn = 0;            // �^�[����������
    m_nTurnPlayer = 0;      // �x�̃v���C���[�̃^�[����
    m_nNumInput = 0;        //  �v���C���[�����͂�����
    m_pPolygon = nullptr;   // �|���S���ւ̃|�C���^
    m_IsinputEnd = false;   // �v���C���[�����͂��I��������̃t���O
    ZeroMemory(&FlipperData, sizeof(FlipperData));      // ���{�f�[�^�̔z��
    ZeroMemory(&PlayerInput, sizeof(PlayerInput));      // �v���C���[�̓��͏��
}

//=============================================================================
// [~CRememjber_rule]�f�X�g���N�^
//=============================================================================
CRememjber_rule::~CRememjber_rule()
{

}

//=============================================================================
// [Create]�C���X�^���X����
//=============================================================================
CRememjber_rule * CRememjber_rule::Create(void)
{
    if (!m_pinstace)
    {
        m_pinstace = new CRememjber_rule;
        m_pinstace->Init();
    }
    return m_pinstace;
}

//=============================================================================
// [Init]����������
//=============================================================================
HRESULT CRememjber_rule::Init(void)
{
    //-----------------------------
    // �����o�ϐ��̏�����
    //-----------------------------
    m_nTurn = 0;            // �^�[����������
    m_nTurnPlayer = 0;      // �x�̃v���C���[�̃^�[����
    m_nNumInput = 0;        // �v���C���[�����͂�����
    m_IsinputEnd = false;   // �v���C���[�����͂��I��������̃t���O
    ZeroMemory(&FlipperData, sizeof(FlipperData));      // ���{�f�[�^�̔z��
    ZeroMemory(&PlayerInput, sizeof(PlayerInput));      // �v���C���[�̓��͏��
    ZeroMemory(&m_apAnswer, sizeof(m_apAnswer));        // �񓚂̃|���S���\��

    //-----------------------------
    // �e�I�u�W�F�N�g����
    //-----------------------------
    // �J�����̐���
     CGame::SetCamera(CTpsCamera::Create());

    // �v���C���[�̐l���擾
     int nPlayerNum = CCountSelect::GetPlayerNum();

     // �v���C���[�̐l�����v���C���[����
     for (int nCnt = 0; nCnt < nPlayerNum; nCnt++)
     {
         float posX = 0 + ((float)(nPlayerNum - 1)*PLAYER_SPACE) / 2;// �ʒu�̒���
         // �v���C���[�̐���
         CPlayer::Create(D3DXVECTOR3(posX, -35.0f, 0.0f), 0);
     }

    // UI�̐���
     for (int nCnt = 0; nCnt < MAX_TARN; nCnt++)
     {
         float posX = 100 + ((float)(nCnt)*PLAYER_SPACE) / 2;// �ʒu�̒���
         m_apAnswer[nCnt] = CPolygon::Create(D3DXVECTOR3(posX, 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// �|���S���N���X�̃|�C���^
     }
    m_pPolygon = CPolygon::Create(D3DXVECTOR3(500.0f, 100.0f, 0.0f), D3DXVECTOR3(32.0f, 32.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// �|���S���N���X�̃|�C���^
    m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_UP));
    return S_OK;
}

//=============================================================================
// [Uninit]�I������
//=============================================================================
void CRememjber_rule::Uninit(void)
{
    //-----------------------------
    // �e�I�u�W�F�N�g�̉��
    //-----------------------------
    // �|���S���̉��
#ifdef _DEBUG
        if (m_pPolygon != NULL)
        {
            m_pPolygon->Uninit();
            delete m_pPolygon;
            m_pPolygon = NULL;
        }
#endif // _DEBUG

        m_pinstace = nullptr;
}

//=============================================================================
// [Uninit]�X�V����
//=============================================================================
void CRememjber_rule::Update(void)
{
    // �v���C���[�̓���
    InputPlayer();

    // ���͂��ꂽ�����^�[�����Ɠ����ɂȂ���
    if (m_IsinputEnd)
    {
        Comparison();   // ���͓��e�̔�r
    }

    // ���U���g�J��
    if (m_nTurn== MAX_TARN)
        CManager::SetMode(CManager::MODE_TITLE);

}

//=============================================================================
// [Draw]�`�揈��
//=============================================================================
void CRememjber_rule::Draw(void)
{
#ifdef _DEBUG
    m_pPolygon->Draw();
#endif // _DEBU

    for (int nCnt = 0; nCnt < MAX_TARN; nCnt++)
    {
        m_apAnswer[nCnt]->Draw();
    }
}

//=============================================================================
// [InputPlayer]�v���C���[�̓���
//=============================================================================
void CRememjber_rule::InputPlayer(void)
{
    // �e�N�X�`���̐ݒ�
    m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_UP));

    //�v���C���[�̓��͓��e���r�p�f�[�^�ɕۑ�
    // �E���������Ƃ�
    if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lRz <= -10 ||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_UP))
    {
        PlayerInput[m_nNumInput] = CFlipper::FLIPPER_TYPE_RIGHT;
        m_nNumInput++;
    }
    // �����������Ƃ�
    else if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lY <= -10 ||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_W))
    {
        PlayerInput[m_nNumInput] = CFlipper::FLIPPER_TYPE_LEFT;
        m_nNumInput++;
    }

// �v���C���[�̍Ō�̓��͂����{�ɒǉ�
    if (m_nNumInput == m_nTurn + 1)
    {
        m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_UP));
        FlipperData[m_nTurn] = PlayerInput[m_nTurn];    // �v���C���[�̓��͂����{�f�[�^�ɕۑ�
        m_IsinputEnd = true;                            // �v���C���[�̓��͊����t���O�I��
        m_nTurn++;                                      // �^�[�����𑝂₷
        m_nNumInput = 0;                                // ���͉񐔂����Z�b�g
    }
}

//=============================================================================
// [Comparison]���͂��ꂽ�f�[�^�̔�r
//=============================================================================
void CRememjber_rule::Comparison(void)
{
    // �v���C���[�̓��̓t���O���I�t�ɂ���
    m_IsinputEnd = false;

    // �e�N�X�`���̐ݒ�
    m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_DOWN));

    for (int nCnt = 0; nCnt < m_nTurn; nCnt++)
    {
        if (FlipperData[nCnt] != PlayerInput[nCnt])
        {
            // �O�ꂽ�ꍇ�~��\��
            m_apAnswer[nCnt]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_BATU));
        }
        else
        {
            m_apAnswer[nCnt]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_MARU));
        }
    }

}
