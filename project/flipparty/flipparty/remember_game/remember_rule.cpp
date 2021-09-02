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
#include "camera_remember.h"
#include "remember_rule.h"
#include "resource_texture.h"
#include "count_selection.h"
#include "bg.h"
#include "player_remember.h"
#include "camera_tps.h"
#include "mini_result.h"
#include "snow.h"
#include "number.h"
#include "stage.h"
#include "sea.h"
#include "sound.h"
#include "tutorial.h"
#include "result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_SPACE (300.0f)             //�@�v���C���[�ʒu�̊Ԋu
#define INPUT_COUNT  (30)                 // ���͂��Ă���ē��͂ł���܂ł̑҂�����

#define CAMERA_POS (150)                        // �J�����̊�ʒu
#define SNOWSTORM_TURN (m_nNumPlayer * 2)       // ����̓o��^�[��

// �H�̊p�x�̐ݒ�
#define FLIPPER_NONE D3DXToRadian(0.0f)         // �f�t�H���g�̂Ƃ�
#define FLIPPER_UP_RIGHT D3DXToRadian(-70.0f)   // �E���グ�Ă���Ƃ�
#define FLIPPER_UP_LEFT D3DXToRadian(70.0f)     // ���������Ă���Ƃ�

// ������UI�̐ݒ�
#define ANSWER_UI_POS  D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 600.0f, 0.0f)    // �ʒu
#define ANSWER_UI_SIZE D3DXVECTOR3(128,64,0.0f)                     // �T�C�Y

// �������Ԃ̐ݒ�
#define TIME_LIMIT (3)                                    // ��������
#define MAX_INPUT_TIME (TIME_LIMIT * 60)                  // ��������(�t���[��)
#define TIME_LIMIT_UI_POS {SCREEN_WIDTH / 2.0f,200,0}     // UI�̈ʒu
#define TIME_LIMIT_UI_SIZE {50,50,0}                      // UI�̃T�C�Y
#define TIME_LIMIT_UI_COLOR {1.0,1.0,1.0,1.0}             // UI�̐F

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRememjber_rule* CRememjber_rule::m_pinstace = nullptr;// �C���X�^���X�ւ̃|�C���^
CRememjber_rule::UI_DATA CRememjber_rule::m_UIData[MAX_UI_REMEMBER] = 
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
    m_nInputCount = 0;      // ���͂��󂯕t���Ȃ��J�E���g
    m_nInputTime = 0;       // ���͂̐�������
    ZeroMemory(&m_pPolygon, sizeof(m_pPolygon));        // �|���S���ւ̃|�C���^
    m_IsinputEnd = false;                               // �v���C���[�����͂��I��������̃t���O
    ZeroMemory(&m_FlipperData, sizeof(m_FlipperData));      // ���{�f�[�^�̔z��
    ZeroMemory(&m_PlayerInput, sizeof(m_PlayerInput));      // �v���C���[�̓��͏��
    m_pNumber = nullptr;
    m_pPlayer.clear();// �v���C���[�̏�����
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
CRememjber_rule *CRememjber_rule::Create(void)
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
    m_nInputCount = 0;      // �v���C���[�����͂ł���悤�ɂȂ�܂ł̃J�E���g
    m_nInputTime = MAX_INPUT_TIME;                   // ���͂ł��鐧�����Ԃ̉�
    ZeroMemory(&m_FlipperData, sizeof(m_FlipperData));      // ���{�f�[�^�̔z��
    ZeroMemory(&m_PlayerInput, sizeof(m_PlayerInput));      // �v���C���[�̓��͏��
    ZeroMemory(&m_apAnswer, sizeof(m_apAnswer));        // �񓚂̃|���S���\��
    m_IsPlay = true;                // �Q�[�����v���C�����ǂ���
    m_IsSnow = false;       // ���Ⴊ�o�Ă��邩�ǂ���

    //-----------------------------
    // �e�I�u�W�F�N�g����
    //-----------------------------
    // �w�i�̐���
    CBg::Create();

    // �J�����̐���
	CManager::SetCamera(CCameraRemember::Create());

    // �v���C���[�̐l���擾
    m_nNumPlayer = CCountSelect::GetPlayerNum();

    // �v���C���[�̐l�����v���C���[����
    for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
    {
        float posX = 0 + ((float)(nCntPlayer)*PLAYER_SPACE) / 2 * -1;// �ʒu�̒���
        // �v���C���[�̐���
        CPlayerRemember* pPlayer;
        pPlayer = CPlayerRemember::Create(D3DXVECTOR3(posX, -35.0f, 0.0f), nCntPlayer);

		CStage::Create(D3DXVECTOR3(posX, -35.0f, 0.0f), CStage::STAGE_TYPE_NORMAL);
        m_pPlayer.push_back(pPlayer);
    }

    m_pPlayer.at(m_nTurnPlayer)->SetMoveFlag(true); // �ŏ��̃v���C���[�̑���t���O�I��

    // UI�̐���
        m_apAnswer = CPolygon::Create(ANSWER_UI_POS, ANSWER_UI_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// �|���S���N���X�̃|�C���^

    for (int nCntUI = 0; nCntUI < MAX_UI_REMEMBER; nCntUI++)
    {
        m_pPolygon[nCntUI] = CPolygon::Create(m_UIData[nCntUI].pos, m_UIData[nCntUI].size, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));// �|���S���N���X�̃|�C���^
        m_pPolygon[nCntUI]->BindTexture(CResourceTexture::GetTexture(m_UIData[nCntUI].pTexture));
    }

    m_pNumber = CNumber::Create(TIME_LIMIT, TIME_LIMIT_UI_POS, TIME_LIMIT_UI_SIZE, TIME_LIMIT_UI_COLOR);

    ChangeTurnUI();
    CManager::GetSound()->Play(CSound::LABEL_BGM_REMEMBER_GAME);

	// �C�̐���
	CSea::Create(D3DXVECTOR3(0.0f, -PLAYER_CENTER_HEIGHT - 14.0f, 0.0f), 0.001f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -PLAYER_CENTER_HEIGHT - 12.0f, 0.0f), 0.0025f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, -PLAYER_CENTER_HEIGHT - 10.0f, 0.0f), 0.004f, CSea::TYPE_NORMAL);

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

    // �|���S���̉��
    m_apAnswer->Uninit();
    delete m_apAnswer;
    m_apAnswer = nullptr;

    m_pinstace = nullptr;

    if (m_pNumber)
    {
        m_pNumber->Uninit();
        delete m_pNumber;
        m_pNumber = nullptr;
    }

    CManager::GetSound()->Stop();
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

    // ����̐���
    if (IsSnowstormTurn())
    {
        m_IsSnow = true;// �t���O���I���ɂ���
        CSnow::Create();// ����
    }

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
        // �����Ă��邩��UI�`��
    if (m_nInputCount)
    {
        m_apAnswer->Draw();
    }

    // �������Ԃ̕`��
    if (m_pNumber)
    {
    m_pNumber->Draw();
    }

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

    // ��̏�Ԃ����Z�b�g
    ControllFlipper(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPER_STATE_NONE);
    ControllFlipper(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPER_STATE_NONE);

    // �v���C���[���^�[�����Ɠ��������͂�����
    if (m_nNumInput == m_nTurn + 1)
    {
        m_nNumInput = 0;                                // ���͉񐔂����Z�b�g
        m_nTurn++;                                      // �^�[�����𑝂₷
        TurnChange();                                   // �v���C���[�̃^�[���ύX
    }
    else if (m_pPlayer[m_nTurnPlayer]->GetIsLoss())
    {
        TurnChange();                                   // �v���C���[�̃^�[���ύX
    }

    // �����̒�`
    // �E����グ�����
    bool IsRight = CManager::GetJoypad()->GetStick(m_nTurnPlayer).lRz <= -10 || CManager::GetKeyboard()->GetKeyTrigger(DIK_UP);
    // ��������������
    bool IsLeft = CManager::GetJoypad()->GetStick(m_nTurnPlayer).lY <= -10 || CManager::GetKeyboard()->GetKeyTrigger(DIK_W);

    if (IsRight)
    {    // �E���グ���Ƃ�
        SetRememberData(CFlipper::FLIPPER_TYPE_LEFT);
    }
    else if (IsLeft)
    {    // �����グ���Ƃ�
        
        SetRememberData(CFlipper::FLIPPER_TYPE_RIGHT);
    }

    // ���͂ł��鐧�����Ԃ��߂�����E��
    m_nInputTime--;
    m_pNumber->SetNumber(((int)m_nInputTime / 60)+1);

    if ((m_nInputTime == 0))
    {
        Ranking();
        m_nInputTime = MAX_INPUT_TIME;                   // ���͂ł��鐧�����Ԃ̉�
    }
}

//=============================================================================
// [ChangeTurnUI]�v���C���[�ԍ�UI�̕ύX����
//=============================================================================
void CRememjber_rule::ChangeTurnUI(void)
{
    D3DXVECTOR2 Vtx[NUM_VERTEX];
    float fv = 1.0/ MAX_PLAYER_NUM;// 1��������̑傫��

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
// ���݂̃^�[���̃v���C���[�̑���t���O�I�t
    m_pPlayer[m_nTurnPlayer]->SetMoveFlag(false);

    // �^�[���ύX
    if (m_nTurnPlayer == m_pPlayer.size() - 1)
    {
        m_nTurnPlayer = 0;
    }
    else
    {
        m_nTurnPlayer++;
    }

    // �ύX��̃^�[���̃v���C���[�̑���t���O�I��
    m_pPlayer[m_nTurnPlayer]->SetMoveFlag(true);

    // �J�����̈ʒu�ύX
    CCameraRemember::GetInsutance()->SetDest(CAMERA_POS * m_nTurnPlayer*-1);

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
    for (int nData = nPlayerNum; nData < m_nNumPlayer - m_nLossPlayer; nData++)
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
    // ���{�Ɠ��͂����f�[�^�̔�r
        if (m_FlipperData[m_nNumInput] != m_PlayerInput[m_nNumInput])
        {
            // �O�ꂽ�ꍇ�~��\��
            m_apAnswer->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_BATU));
            CManager::GetSound()->Play(CSound::LABEL_SE_MISS);
            // �~�X�����v���C���[�̏��ʂ�����
            Ranking();
        }
        else
        {   // �����̏ꍇ�Z��\��
            m_apAnswer->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_MARU));
            CManager::GetSound()->Play(CSound::LABEL_SE_OK);
        }
}

//=============================================================================
// [Ranking]���ʂ̐ݒ�
//=============================================================================
void CRememjber_rule::Ranking(void)
{
    m_nLossPlayer++;                // �E�������v���C���[�̐l�����J�E���g
    PlayerChange(m_nTurnPlayer);    // �v���C���[�̏��ԕύX
    m_pPlayer[m_nTurnPlayer]->SetIsLoss(true);// �E���t���O�����Ă�

    // �v���C���[���Ō��1�l�ɂȂ����烊�U���g����
    if (m_nNumPlayer - m_nLossPlayer == 1)
    {
        // ���ʂ̐ݒ�
        for (int nRank = 0; nRank < m_nNumPlayer; nRank++)
        {
            m_pPlayer[m_aTurn[nRank]]->SetRank(nRank);

			// �~�j�Q�[���ɏ��ʂ𑗂�
			CResult::SetMiniGameRank(CRuleManager::RULE_FLY, m_pPlayer[m_aTurn[nRank]]->GetPlayerNumber(), m_pPlayer[m_aTurn[nRank]]->GetRank());
        }

        m_IsPlay = false;
        CSnow::GetInstancce()->CSnow::Uninit();

        CMiniResult::Create();
    }
}

//=============================================================================
// [SetRememberData] ���͂�����̏���
//=============================================================================
void CRememjber_rule::SetRememberData(CFlipper::FLIPPER_TYPE type)
{
    m_PlayerInput[m_nNumInput] = type;                 // ���͂�������ۑ�

    // ���͂����񐔂��^�[���Ɠ����Ƃ�
    if (m_nNumInput == m_nTurn)
        m_FlipperData[m_nTurn] = m_PlayerInput[m_nTurn];    // �v���C���[�̓��͂����{�f�[�^�ɕۑ�

    Comparison();                                   // ���͓��e�̔�r

    m_nInputCount = INPUT_COUNT;                     // �ē��͂ł���܂ł̎��Ԃ��Z�b�g
    m_nInputTime = MAX_INPUT_TIME;                   // ���͂ł��鐧�����Ԃ̉�
    ControllFlipper(type, CFlipper::FLIPPERSTATE_UP);// ��������郂�[�V�����ɂ���
    m_nNumInput++;                                   // ���͂����񐔂̒ǉ�
}

//=============================================================================
// [ControllFlipper] �H�𓮂�������
//=============================================================================
void CRememjber_rule::ControllFlipper(CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state)
{
    m_pPlayer[m_nTurnPlayer]->GetFlipper()->SetState(type, state);
    float fAngle = 0;

    switch (state)
    {
    case CFlipper::FLIPPER_STATE_NONE:
            fAngle = FLIPPER_NONE;
            break;
    case CFlipper::FLIPPERSTATE_UP:
        if (type== CFlipper::FLIPPER_TYPE_LEFT)
        {
            fAngle = FLIPPER_UP_LEFT;
        }
        else
        {
            fAngle = FLIPPER_UP_RIGHT;
        }

        break;
    }
        m_pPlayer[m_nTurnPlayer]->SetFlipperDist(type, fAngle);
}

//=============================================================================
// [IsSnowstormTurn] ����𔭐������邩�ǂ����̔���
// �Ԃ�l: ���茋�ʂ�Ԃ�
//=============================================================================
bool CRememjber_rule::IsSnowstormTurn(void)
{
    // ���ᐶ���p����
    // �����F���Ⴊ�o�Ă��Ȃ��A������o���^�[���ɂȂ�����
    bool IsSnowstormTurn = !m_IsSnow && m_nTurn == SNOWSTORM_TURN;

    return IsSnowstormTurn;
}
