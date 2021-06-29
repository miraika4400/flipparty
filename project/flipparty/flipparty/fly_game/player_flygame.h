//=============================================================================
//
// player_flygameヘッダ [player_flygame.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _PLAYER_FLYGAME_H_
#define _PLAYER_FLYGAME_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "player.h"
#include "flipper.h"

//*****************************
// マクロ定義
//*****************************

//*****************************
// 前方宣言
//*****************************

//*****************************
// クラス定義
//*****************************

// プレイヤークラス
class CFlyGamePlayer : public CPlayer
{
public:

	// メンバ関数
	CFlyGamePlayer();
	~CFlyGamePlayer();
	static CFlyGamePlayer *Create(D3DXVECTOR3 pos, int nPlayerNum);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Fly(CFlipper::FLIPPER_STATE stateNow, CFlipper::FLIPPER_STATE stateOld); // 飛ぶ処理

	// メンバ変数
	float m_fHeightDist; // 高さの目標値

};

#endif
