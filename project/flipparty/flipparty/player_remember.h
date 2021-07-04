//=============================================================================
//
// 記憶ゲームのプレイヤーヘッダ [player_remember.h]
// Author : AYANO KUDO
//
//=============================================================================
//二重インクルード防止
#ifndef _PLAYER_REMEMBER_H_
#define _PLAYER_REMEMBER_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "player.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayerRemember : public CPlayer
{
public:
    // メンバ関数
    CPlayerRemember();
    ~CPlayerRemember();

    static CPlayerRemember* Create(D3DXVECTOR3 pos, int nPlayerNum);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    // Set関数
    void SetIsLoss(bool IsLoss) { m_IsLoss = IsLoss; }

    // Get関数
    bool GetIsLoss(void) { return m_IsLoss;}      // 脱落したかどうか
private:
    bool m_IsLoss;        // 脱落したかどうか
};


#endif _PLAYER_REMEMBER_H_