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
#include "remember_rule.h"
#include "keyboard.h"

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
    m_nNumInput = 0;        //  �v���C���[�����͂��ꂽ��
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
    m_nTurn = 0;            // �^�[����������
    m_nTurnPlayer = 0;      // �x�̃v���C���[�̃^�[����
    m_nNumInput = 0;        //  �v���C���[�����͂��ꂽ��

    return S_OK;
}

//=============================================================================
// [Uninit]�I������
//=============================================================================
void CRememjber_rule::Uninit(void)
{

}

//=============================================================================
// [Uninit]�X�V����
//=============================================================================
void CRememjber_rule::Update(void)
{
    // �v���C���[�̓���
    InputPlayer();

    // ���͂��ꂽ�����^�[�����Ɠ����ɂȂ���
    if (m_nNumInput == m_nTurn + 1)
    {
        Comparison();   // ��r
    }
}

//=============================================================================
// [Draw]�`�揈��
//=============================================================================
void CRememjber_rule::Draw(void)
{

}

//=============================================================================
// [InputPlayer]�v���C���[�̓���
//=============================================================================
void CRememjber_rule::InputPlayer(void)
{
    // �^�[����������
    for (int nCnt = 0; nCnt < m_nTurn + 1; nCnt++)
    {
        //�v���C���[�̓��͓��e���r�p�f�[�^�ɕۑ�
        // �E
        if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lRz <= -10 ||
            CManager::GetKeyboard()->GetKeyPress(DIK_UP))
        {
            PlayerInput[nCnt] = CFlipper::FLIPPER_TYPE_RIGHT;
            m_nNumInput++;
        }
        // ��
        else if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lY <= -10 ||
            CManager::GetKeyboard()->GetKeyPress(DIK_W))
        {
            PlayerInput[nCnt] = CFlipper::FLIPPER_TYPE_LEFT;
            m_nNumInput++;
        }
    }

    // �v���C���[�̍Ō�̓��͂����{�ɒǉ�
    if (m_nNumInput == m_nTurn + 1)
    {
        FlipperData[m_nTurn] = PlayerInput[m_nTurn];
    }
}

//=============================================================================
// [Comparison]���͂��ꂽ�f�[�^�̔�r
//=============================================================================
void CRememjber_rule::Comparison(void)
{
    for (int nCnt = 0; nCnt < m_nTurn + 1; nCnt++)
    {
        if (FlipperData[nCnt] != PlayerInput[nCnt])
        {
            // �O�ꂽ�ꍇ�̏���
            CManager::SetMode(CManager::MODE_TITLE);
        }
    }

    m_nTurn++;// �^�[�����𑝂₷
    m_nNumInput = 0;// ���͉񐔂����Z�b�g
}