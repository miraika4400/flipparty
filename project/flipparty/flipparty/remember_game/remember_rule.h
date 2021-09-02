//=============================================================================
//
// �L���Q�[�����[���w�b�_ [remember_rule.h]
// Author : AYANOKUDO
//
//=============================================================================
//��d�C���N���[�h�h�~
#ifndef _REMEMBER_RULE_H_
#define _REMEMBER_RULE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"rule_base.h"
#include "flipper.h"
#include "resource_texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TARN (128)// �ő�^�[����(���{�f�[�^�̏���ɂ��Ȃ�)
#define MAX_UI_REMEMBER (2)     // �g�p����UI�̐�

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;
class CPlayerRemember;
class CCamera;
class CNumber;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRememjber_rule : public CRuleBase
{
    static CRememjber_rule* m_pinstace;// �C���X�^���X�ւ̃|�C���^
    CRememjber_rule();

public:
    // UI�̏����܂Ƃ߂��\����
    typedef struct
    {
        D3DXVECTOR3 pos;                // �ʒu
        D3DXVECTOR3 size;               // �T�C�Y
        CResourceTexture::TEXTURE_TYPE pTexture;    // �e�N�X�`���ւ̃|�C���^
    }UI_DATA;

    //---------------------
    // �����o�֐�
    //---------------------
    ~CRememjber_rule();

    static CRememjber_rule* Create(void);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void InputPlayer(void);     // �v���C���[�̓���
    void ChangeTurnUI(void);    // �v���C���[�ԍ�UI�̕ύX����
    void TurnChange(void);      // �^�[���̕ύX
    void PlayerChange(int nPlayerNum);    // �v���C���[�ԍ��̕��ёւ�
    void Comparison(void);      // ���͓��e�̔�r
    void Ranking(void);         // ���ʂ̐ݒ�

    void SetRememberData(CFlipper::FLIPPER_TYPE type);


    // Get�֐�
    CRememjber_rule* GetInstance(void) { return m_pinstace; }// �C���X�^���X�̎擾

private:

    //---------------------
    // �����o�֐�
    //---------------------
    void ControllFlipper(CFlipper::FLIPPER_TYPE type, CFlipper::FLIPPER_STATE state);
    bool IsSnowstormTurn(void);

    //---------------------
    // �����o�ϐ�
    //---------------------
    // ���{�̕ۑ��p
    static UI_DATA m_UIData[MAX_UI_REMEMBER];     // UI�̏��
    CFlipper::FLIPPER_TYPE m_FlipperData[MAX_TARN];// ���{�f�[�^
    CFlipper::FLIPPER_TYPE m_PlayerInput[MAX_TARN];// �v���C���[�̓��͓��e

    std::vector<CPlayerRemember*> m_pPlayer;     // �v���C���[�ւ̃|�C���^
    CCamera *m_pCamera;         // �J�����ւ̃|�C���^
    int m_nNumPlayer;           // �v���C���[�̐l��
    int m_nLossPlayer;          // �E�������v���C���[�̐l��
    int m_nNumInput;            // ���͂��ꂽ��
    int m_nTurn;                // ���݂̃^�[����
    int m_aTurn[MAX_PLAYER_NUM];// ���ʗp
    int m_nTurnPlayer;          // ���ݎ����̔Ԃ̃v���C���[�ԍ�
    unsigned int m_nInputCount; // ���͂��󂯕t���Ȃ��J�E���g
    unsigned int m_nInputTime;  // ���͂̐�������
    bool m_IsinputEnd;          // �v���C���[�̓��͂��I�����Ă��邩
    bool m_IsPlay;              // �Q�[�����v���C�����ǂ���

    bool m_IsSnow;              // ���Ⴊ�o�Ă��邩�ǂ���

    CPolygon *m_pPolygon[MAX_UI_REMEMBER];// �|���S���N���X�̃|�C���^
    CPolygon *m_apAnswer;                 // �����̕\���p�|���S��
    CNumber *m_pNumber;                   // �������Ԃ̕b���|�C���^

};

#endif //!__REMEMBER_RULE_H_