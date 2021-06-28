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
class CRememjber_rule : public CRuleBase
{
    static CRememjber_rule* m_pinstace;// インスタンスへのポインタ

public:
    CRememjber_rule();
    ~CRememjber_rule();

    static CRememjber_rule* Create(void);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void InputPlayer(void);// プレイヤーの入力
    void Comparison(void);// 比較

    // Get関数
    CRememjber_rule* GetInstance(void) { return m_pinstace; }// インスタンスの取得

private:
    // 見本の保存用
    CFlipper::FLIPPER_TYPE FlipperData[MAX_FLIPPER_DATA];// 見本データ
    CFlipper::FLIPPER_TYPE PlayerInput[MAX_FLIPPER_DATA];// プレイヤーの入力内容
    int m_nNumInput;            // 入力された回数
    int m_nTurn;                // 現在のターン数
    int m_nTurnPlayer;          // 現在自分の番のプレイヤー番号

};

#endif //!__REMEMBER_RULE_H_