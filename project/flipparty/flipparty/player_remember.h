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

    static CPlayerRemember* Create(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

private:
    bool IsLoss;        // 脱落したかどうか
};


#endif _PLAYER_REMEMBER_H_