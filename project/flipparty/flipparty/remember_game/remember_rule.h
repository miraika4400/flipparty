//=============================================================================
//
// 記憶ゲームルールヘッダ [remember_rule.h]
// Author : AYANOKUDO
//
//=============================================================================
//二重インクルード防止
#ifndef _REMEMBER_RULE_H_
#define _REMEMBER_RULE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"rule_base.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Crememjber_rule : public CRuleBase
{
    static Crememjber_rule* m_pinstace;// インスタンスへのポインタ

public:
    Crememjber_rule();
    ~Crememjber_rule();

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

private:
    // 見本の保存用

};

#endif //!__REMEMBER_RULE_H_