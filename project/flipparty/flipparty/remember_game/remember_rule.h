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
#define MAX_FLIPPER_DATA (10)// ���{�f�[�^�̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

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

    // Get�֐�
    CRememjber_rule* GetInstance(void) { return m_pinstace; }// �C���X�^���X�̎擾

private:
    // ���{�̕ۑ��p
    CFlipper::FLIPPER_TYPE FlipperData[MAX_FLIPPER_DATA];// ���{�f�[�^
    CFlipper::FLIPPER_TYPE PlayerInput[MAX_FLIPPER_DATA];// �v���C���[�̓��͓��e
    int m_nNumInput;            // ���͂��ꂽ��
    int m_nTurn;                // ���݂̃^�[����
    int m_nTurnPlayer;          // ���ݎ����̔Ԃ̃v���C���[�ԍ�

    bool m_IsinputEnd;// �v���C���[�̓��͂��I�����Ă��邩

#ifdef _DEBUG
    // �f�o�b�O�p�ϐ�
    CPolygon *m_pPolygon;// �|���S���N���X�̃|�C���^
#endif // _DEBUG

};

#endif //!__REMEMBER_RULE_H_