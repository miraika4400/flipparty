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
#include "resource_texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TARN (10)// 最大ターン数(見本データの上限にもなる)
#define MAX_UI_REMEMBER (2)     // 使用するUIの数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;
class CPlayerRemember;
class CCamera;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRememjber_rule : public CRuleBase
{
    static CRememjber_rule* m_pinstace;// インスタンスへのポインタ
    CRememjber_rule();

public:
    // UIの情報をまとめた構造体
    typedef struct
    {
        D3DXVECTOR3 pos;                // 位置
        D3DXVECTOR3 size;               // サイズ
        CResourceTexture::TEXTURE_TYPE pTexture;    // テクスチャへのポインタ
    }UI_DATA;

    ~CRememjber_rule();

    static CRememjber_rule* Create(void);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void InputPlayer(void);     // プレイヤーの入力
    void ChangeTurnUI(void);    // プレイヤー番号UIの変更処理
    void TurnChange(void);      // ターンの変更
    void PlayerChange(int nPlayerNum);    // プレイヤー番号の並び替え
    void Comparison(void);      // 入力内容の比較
    void Ranking(void);         // 順位の設定

    // Get関数
    CRememjber_rule* GetInstance(void) { return m_pinstace; }// インスタンスの取得

private:
    // 見本の保存用
    static UI_DATA UIData[MAX_UI_REMEMBER];     // UIの情報
    CFlipper::FLIPPER_TYPE FlipperData[MAX_TARN];// 見本データ
    CFlipper::FLIPPER_TYPE PlayerInput[MAX_TARN];// プレイヤーの入力内容

    CPlayerRemember *m_pPlayer[MAX_PLAYER_NUM];     // プレイヤーへのポインタ
    CCamera *m_pCamera;         // カメラへのポインタ
    int m_nNumPlayer;           // プレイヤーの人数
    int m_nLossPlayer;          // 脱落したプレイヤーの人数
    int m_nNumInput;            // 入力された回数
    int m_nTurn;                // 現在のターン数
    int m_aTurn[MAX_PLAYER_NUM];                // ターン管理用変数
    int m_nTurnPlayer;          // 現在自分の番のプレイヤー番号
    unsigned int m_nInputCount; // 再入力を受け付ける時間
    bool m_IsinputEnd;          // プレイヤーの入力が終了しているか
    bool m_IsPlay;              // ゲームをプレイ中かどうか

    CPolygon *m_pPolygon[MAX_UI_REMEMBER];// ポリゴンクラスのポインタ
#ifdef _DEBUG
    // デバッグ用変数
    CPolygon *m_apAnswer[MAX_TARN];// 答えの表示用ポリゴン
#endif // _DEBUG

};

#endif //!__REMEMBER_RULE_H_