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
	// 列挙
	// 状態
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_STAN,
		STATE_MAX
	}STATE;

	// メンバ関数
	CFlyGamePlayer();
	~CFlyGamePlayer();
	static CFlyGamePlayer *Create(D3DXVECTOR3 pos, int nPlayerNum);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 状態の取得・セット
	STATE GetState(void) { return m_state; }
	void SetState(STATE state) { m_state = state; }

private:
	void Fly(CFlipper::FLIPPER_STATE stateNow, CFlipper::FLIPPER_STATE stateOld); // 飛ぶ処理
	void ManageState(void);
	//void ControllFlipper(void);    // 羽の操作

	// メンバ変数
	float m_fHeightDist; // 高さの目標値
	STATE m_state; // 状態
	int m_nCntState;// 状態カウント
};

#endif
