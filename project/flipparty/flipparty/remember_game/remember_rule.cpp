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
#include "bg.h"
#include "player_remember.h"
#include "camera_tps.h"
#include "mini_result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_SPACE (150.0f) //�@�v���C���[�ʒu�̊Ԋu
#define INPUT_COUNT (5)        // ���͂��Ă���ē��͂ł���܂ł̑҂�����

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRememjber_rule* CRememjber_rule::m_pinstace = nullptr;// �C���X�^���X�ւ̃|�C���^
CRememjber_rule::UI_DATA CRememjber_rule::UIData[MAX_UI_REMEMBER] = 
{
    { D3DXVECTOR3(500, 100.0f, 0.0f), D3DXVECTOR3(64.f, 16.f, 0.0f) ,CResourceTexture::TEXTURE_UI_000 },
    { D3DXVECTOR3(700, 100.0f, 0.0f), D3DXVECTOR3(128.f, 32.f, 0.0f) ,CResourceTexture::TEXTURE_UI_001 }
};
//=============================================================================
// [CRememjber_rule]�R���X�g���N�^
//=============================================================================
CRememjber_rule::CRememjber_rule()
{
    m_nNumPlayer = 0;       // �v���C���[�̐l��
    m_nLossPlayer = 0;      // �E�������v���C���[�̐l��
    m_nTurn = 0;            // �^�[����������
    m_nTurnPlayer = 0;      // �ǂ̃v���C���[�̃^�[����
    m_nNumInput = 0;        //  �v���C���[�����͂�����
    m_nInputCount = 0;
    ZeroMemory(&m_pPolygon, sizeof(m_pPolygon));        // �|���S���ւ̃|�C���^
    m_IsinputEnd = false;                               // �v���C���[�����͂��I��������̃t���O
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
    m_nLossPlayer = 0;      // �E�������v���C���[�̐l��
    m_nTurn = 0;            // �^�[����������

    // �^�[�����̊Ǘ�
    for (int nCnt = 0; nCnt < MAX_PLAYER_NUM; nCnt++)
    {
        m_aTurn[nCnt] = nCnt; // �����Ă���ԍ����v���C���[�̔ԍ��ɂȂ�
    }

    m_nTurnPlayer = 0;      // �ǂ̃v���C���[�̃^�[����
    m_nNumInput = 0;        // �v���C���[�����͂�����
    m_IsinputEnd = false;   // �v���C���[�����͂��I��������̃t���O
    m_nInputCount = 0;
    ZeroMemory(&FlipperData, sizeof(FlipperData));      // ���{�f�[�^�̔z��
    ZeroMemory(&PlayerInput, sizeof(PlayerInput));      // �v���C���[�̓��͏��
    ZeroMemory(&m_apAnswer, sizeof(m_apAnswer));        // �񓚂̃|���S���\��
    m_IsPlay = true;                // �Q�[�����v���C�����ǂ���

    //-----------------------------
    // �e�I�u�W�F�N�g����
    //-----------------------------
    // �w�i�̐���
    CBg::Create();

    // �J�����̐���
    CGame::SetCamera(CTpsCamera::Create());

    // �v���C���[�̐l���擾
    m_nNumPlayer = CCountSelect::GetPlayerNum();

    // �v���C���[�̐l�����v���C���[����
    for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
    {
        float posX = 0 + ((float)(nCntPlayer)*PLAYER_SPACE) / 2;// �ʒu�̒���
        // �v���C���[�̐���
        m_pPlayer[nCntPlayer] = CPlayerRemember::Create(D3DXVECTOR3(posX, -35.0f, 0.0f), nCntPlayer);
    }

    // UI�̐���
    for (int nCntUI = 0; nCntUI < MAX_TARN; nCntUI++)
    {
        float posX = 100 + ((float)(nCntUI)* 100) / 2;// �ʒu�̒���
        m_apAnswer[nCntUI] = CPolygon::Create(D3DXVECTOR3(posX, 200.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// �|���S���N���X�̃|�C���^
    }

    for (int nCntUI = 0; nCntUI < MAX_UI_REMEMBER; nCntUI++)
    {
        m_pPolygon[nCntUI] = CPolygon::Create(UIData[nCntUI].pos, UIData[nCntUI].size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// �|���S���N���X�̃|�C���^
        m_pPolygon[nCntUI]->BindTexture(CResourceTexture::GetTexture(UIData[nCntUI].pTexture));
    }

    ChangeTurnUI();

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
    for (int nCntUI = 0; nCntUI < MAX_UI_REMEMBER; nCntUI++)
    {
        if (m_pPolygon != nullptr)
        {
            m_pPolygon[nCntUI]->Uninit();
            delete m_pPolygon[nCntUI];
            m_pPolygon[nCntUI] = nullptr;
        }
    }
#ifdef _DEBUG
        // �|���S���̉��
        for (int nCntUI = 0; nCntUI < MAX_TARN; nCntUI++)
        {
            m_apAnswer[nCntUI]->Uninit();
            delete m_apAnswer[nCntUI];
            m_apAnswer[nCntUI] = nullptr;
        }

        m_pinstace = nullptr;
#endif // _DEBUG
}

//=============================================================================
// [Uninit]�X�V����
//=============================================================================
void CRememjber_rule::Update(void)
{
    if (m_IsPlay)
    {
    // �v���C���[�̓���
    InputPlayer();
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
    // UI�̕`��
    for (int nCntUI = 0; nCntUI < MAX_UI_REMEMBER; nCntUI++)
    {
        m_pPolygon[nCntUI]->Draw();
    }

#ifdef _DEBUG
    for (int nCntUI = 0; nCntUI < MAX_TARN; nCntUI++)
    {
        m_apAnswer[nCntUI]->Draw();
    }
#endif // _DEBUG
}

//=============================================================================
// [InputPlayer]�v���C���[�̓���
//=============================================================================
void CRememjber_rule::InputPlayer(void)
{
    // ���͑҂����Ԃ��c���Ă���Ƃ��͏������s��Ȃ�
    if (m_nInputCount > 0)
    {
        // �v���C���[�̓��͂ł���܂ł̃J�E���g�����炷
        m_nInputCount--;
        return;
    }

    //�v���C���[�̓��͓��e���r�p�f�[�^�ɕۑ�
    // �E���������Ƃ�
    if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lRz <= -10 ||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_UP))
    {
        PlayerInput[m_nNumInput] = CFlipper::FLIPPER_TYPE_RIGHT;
        m_nNumInput++;
        m_nInputCount = INPUT_COUNT;
    }
    // �����������Ƃ�
    else if (CManager::GetJoypad()->GetStick(m_nTurnPlayer).lY <= -10 ||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_W))
    {
        PlayerInput[m_nNumInput] = CFlipper::FLIPPER_TYPE_LEFT;
        m_nNumInput++;
        m_nInputCount = INPUT_COUNT;
    }

    // �v���C���[���^�[�����Ɠ��������͂�����
    if (m_nNumInput == m_nTurn + 1)
    {
        FlipperData[m_nTurn] = PlayerInput[m_nTurn];    // �v���C���[�̓��͂����{�f�[�^�ɕۑ�
        Comparison();                                   // ���͓��e�̔�r
        m_nTurn++;                                      // �^�[�����𑝂₷
        m_nNumInput = 0;                                // ���͉񐔂����Z�b�g
        TurnChange();                                   // �v���C���[�̃^�[���ύX
    }
}

//=============================================================================
// [ChangeTurnUI]�v���C���[�ԍ�UI�̕ύX����
//=============================================================================
void CRememjber_rule::ChangeTurnUI(void)
{
    D3DXVECTOR2 Vtx[NUM_VERTEX];
    float fv = 1.0/ MAX_PLAYER_NUM;

    Vtx[0] = {0.0,fv * m_nTurnPlayer};
    Vtx[1] = {1.0,fv * m_nTurnPlayer};
    Vtx[2] = {0.0,fv * m_nTurnPlayer+ fv };
    Vtx[3] = {1.0,fv * m_nTurnPlayer+ fv };

    // uv���W�̃Z�b�g
    m_pPolygon[0]->SetTextureUV(Vtx);
}

//=============================================================================
// [TurnChange]�^�[���̕ύX
//=============================================================================
void CRememjber_rule::TurnChange(void)
{
    // �^�[�����Ɛ����c���Ă���v���C���[�������������܂�̃v���C���[�ԍ�
    m_nTurnPlayer = m_aTurn[(m_nTurn) % (m_nNumPlayer- m_nLossPlayer)];

   // �e�N�X�`���ύX
   ChangeTurnUI();
}

//=============================================================================
// [PlayerChange]�v���C���[�ԍ��̕��ёւ�
// ����: �E�������v���C���[�̔ԍ�
//=============================================================================
void CRememjber_rule::PlayerChange(int nPlayerNum)
{
   // �E�������v���C���[�̔ԍ���z��̍Ō�Ɉړ�
   // �o�u���\�[�g�œ���ւ���΍ŏI�I�ɏ��ʂƓ������ԂɂȂ�
    for (int nData = nPlayerNum; nData < m_nNumPlayer- m_nLossPlayer; nData++)
    {

        int nSwap = m_aTurn[nData];// ����ւ��p�ϐ�

        m_aTurn[nData] = m_aTurn[nData + 1];
        m_aTurn[nData + 1] = nSwap;
    }

}

//=============================================================================
// [Comparison]���͂��ꂽ�f�[�^�̔�r
//=============================================================================
void CRememjber_rule::Comparison(void)
{
    // �v���C���[�̓��̓t���O���I�t�ɂ���
    m_IsinputEnd = false;

    // �f�[�^�̔�r
    for (int nCnt = 0; nCnt < m_nTurn; nCnt++)
    {
        if (FlipperData[nCnt] != PlayerInput[nCnt])
        {
            // �O�ꂽ�ꍇ�~��\��
            m_apAnswer[nCnt]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_BATU));

            // �~�X�����v���C���[�̏��ʂ�����
            Ranking();
            return;
        }
        else
        {
            m_apAnswer[nCnt]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_MARU));
        }
    }

}

//=============================================================================
// [Ranking]���ʂ̐ݒ�
//=============================================================================
void CRememjber_rule::Ranking(void)
{
    m_nLossPlayer++;// �E�������v���C���[�̐l�����J�E���g
    PlayerChange(m_nTurnPlayer);
    m_pPlayer[m_nTurnPlayer]->SetIsLoss(true);// �E���t���O�����Ă�

    // �v���C���[���Ō��1�l�ɂȂ����烊�U���g����
    if (m_nNumPlayer - m_nLossPlayer == 1)
    {
        // ���ʂ̐ݒ�
        for (int nRank = 0; nRank < m_nNumPlayer; nRank++)
        {
            m_pPlayer[nRank]->SetRank(m_aTurn[nRank]);
        }

        CMiniResult::Create();
        m_IsPlay = false;
    }

}
