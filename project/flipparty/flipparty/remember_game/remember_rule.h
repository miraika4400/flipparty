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

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TARN (10)// �ő�^�[����(���{�f�[�^�̏���ɂ��Ȃ�)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;
class CPlayer;
class CCamera;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRememjber_rule : public CRuleBase
{
    static CRememjber_rule* m_pinstace;// �C���X�^���X�ւ̃|�C���^
    CRememjber_rule();

public:
    ~CRememjber_rule();

    static CRememjber_rule* Create(void);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void InputPlayer(void);// �v���C���[�̓���
    void Comparison(void);// ��r
    void Ranking(void);     // ���ʂ̐ݒ�


    // Get�֐�
    CRememjber_rule* GetInstance(void) { return m_pinstace; }// �C���X�^���X�̎擾

private:
    // ���{�̕ۑ��p
    CFlipper::FLIPPER_TYPE FlipperData[MAX_TARN];// ���{�f�[�^
    CFlipper::FLIPPER_TYPE PlayerInput[MAX_TARN];// �v���C���[�̓��͓��e

    CPlayer *m_pPlayer[4];     // �v���C���[�ւ̃|�C���^
    CCamera *m_pCamera;// �J�����ւ̃|�C���^
    int m_nNumPlayer;           // �v���C���[�̐l��
    int m_nLossPlayer;          // �E�������v���C���[�̐l��
    int m_nNumInput;            // ���͂��ꂽ��
    int m_nTurn;                // ���݂̃^�[����
    int m_nTurnPlayer;          // ���ݎ����̔Ԃ̃v���C���[�ԍ�
    unsigned int m_nInputCount;          // �ē��͂��󂯕t���鎞��
    bool m_IsinputEnd;// �v���C���[�̓��͂��I�����Ă��邩

    CPolygon *m_apAnswer[MAX_TARN];// �����̕\���p�|���S��

#ifdef _DEBUG
    // �f�o�b�O�p�ϐ�
    CPolygon *m_pPolygon;// �|���S���N���X�̃|�C���^
#endif // _DEBUG

};

#endif //!__REMEMBER_RULE_H_