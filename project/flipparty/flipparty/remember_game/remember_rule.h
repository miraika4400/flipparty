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
#include"../rule_base.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Crememjber_rule : public CRuleBase
{
    static Crememjber_rule* m_pinstace;// �C���X�^���X�ւ̃|�C���^

public:
    Crememjber_rule();
    ~Crememjber_rule();

    void Input(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

private:
    // ���{�̕ۑ��p

};

#endif //!__REMEMBER_RULE_H_