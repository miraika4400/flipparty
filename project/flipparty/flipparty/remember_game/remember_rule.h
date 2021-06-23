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
// �N���X��`
//*****************************************************************************
class Crememjber_rule : public CRuleBase
{
    static Crememjber_rule* m_pinstace;// �C���X�^���X�ւ̃|�C���^

public:
    Crememjber_rule();
    ~Crememjber_rule();

    static Crememjber_rule* Create(void);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    // Get�֐�
    Crememjber_rule* GetInstance(void) { return m_pinstace; }// �C���X�^���X�̎擾

private:
    // ���{�̕ۑ��p
    CFlipper::FLIPPER_TYPE FlipperData[MAX_FLIPPER_DATA];
    int m_nTurn;                // ���݂̃^�[����
    int m_nTurnPlayer;          // ���ݎ����̔Ԃ̃v���C���[�ԍ�

};

#endif //!__REMEMBER_RULE_H_