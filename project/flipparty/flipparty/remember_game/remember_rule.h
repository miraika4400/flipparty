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
#include "flipper.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_FLIPPER_DATA (10)// 見本データの最大数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Crememjber_rule : public CRuleBase
{
    static Crememjber_rule* m_pinstace;// インスタンスへのポインタ

public:
    Crememjber_rule();
    ~Crememjber_rule();

    static Crememjber_rule* Create(void);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    // Get関数
    Crememjber_rule* GetInstance(void) { return m_pinstace; }// インスタンスの取得

private:
    // 見本の保存用
    CFlipper::FLIPPER_TYPE FlipperData[MAX_FLIPPER_DATA];
    int m_nTurn;                // 現在のターン数
    int m_nTurnPlayer;          // 現在自分の番のプレイヤー番号

};

#endif //!__REMEMBER_RULE_H_