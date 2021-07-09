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
#define MAX_TARN (10)// �ő�^�[����(���{�f�[�^�̏���ɂ��Ȃ�)
#define MAX_UI_REMEMBER (2)     // �g�p����UI�̐�

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;
class CPlayerRemember;
class CCamera;

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

    // Get�֐�
    CRememjber_rule* GetInstance(void) { return m_pinstace; }// �C���X�^���X�̎擾

private:
    // ���{�̕ۑ��p
    static UI_DATA UIData[MAX_UI_REMEMBER];     // UI�̏��
    CFlipper::FLIPPER_TYPE FlipperData[MAX_TARN];// ���{�f�[�^
    CFlipper::FLIPPER_TYPE PlayerInput[MAX_TARN];// �v���C���[�̓��͓��e

    CPlayerRemember *m_pPlayer[MAX_PLAYER_NUM];     // �v���C���[�ւ̃|�C���^
    CCamera *m_pCamera;         // �J�����ւ̃|�C���^
    int m_nNumPlayer;           // �v���C���[�̐l��
    int m_nLossPlayer;          // �E�������v���C���[�̐l��
    int m_nNumInput;            // ���͂��ꂽ��
    int m_nTurn;                // ���݂̃^�[����
    int m_aTurn[MAX_PLAYER_NUM];                // �^�[���Ǘ��p�ϐ�
    int m_nTurnPlayer;          // ���ݎ����̔Ԃ̃v���C���[�ԍ�
    unsigned int m_nInputCount; // �ē��͂��󂯕t���鎞��
    bool m_IsinputEnd;          // �v���C���[�̓��͂��I�����Ă��邩
    bool m_IsPlay;              // �Q�[�����v���C�����ǂ���

    CPolygon *m_pPolygon[MAX_UI_REMEMBER];// �|���S���N���X�̃|�C���^
#ifdef _DEBUG
    // �f�o�b�O�p�ϐ�
    CPolygon *m_apAnswer[MAX_TARN];// �����̕\���p�|���S��
#endif // _DEBUG

};

#endif //!__REMEMBER_RULE_H_