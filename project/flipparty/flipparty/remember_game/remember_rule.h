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
#define MAX_TARN (10)// 最大ターン数(見本データの上限にもなる)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;
class CPlayer;
class CCamera;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRememjber_rule : public CRuleBase
{
    static CRememjber_rule* m_pinstace;// インスタンスへのポインタ
    CRememjber_rule();

public:
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
    CFlipper::FLIPPER_TYPE FlipperData[MAX_TARN];// 見本データ
    CFlipper::FLIPPER_TYPE PlayerInput[MAX_TARN];// プレイヤーの入力内容

    CPlayer *m_pPlayer[4];     // プレイヤーへのポインタ
    CCamera *m_pCamera;// カメラへのポインタ

    int m_nNumInput;            // 入力された回数
    int m_nTurn;                // 現在のターン数
    int m_nTurnPlayer;          // 現在自分の番のプレイヤー番号
    unsigned int m_nInputCount;          // 再入力を受け付ける時間
    bool m_IsinputEnd;// プレイヤーの入力が終了しているか

    CPolygon *m_apAnswer[MAX_TARN];// 答えの表示用ポリゴン

#ifdef _DEBUG
    // デバッグ用変数
    CPolygon *m_pPolygon;// ポリゴンクラスのポインタ
#endif // _DEBUG

};

#endif //!__REMEMBER_RULE_H_