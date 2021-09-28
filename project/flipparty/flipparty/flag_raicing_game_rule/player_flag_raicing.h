//=============================================================================
//
// player_flag_raicingヘッダ [player_flag_raicing.h]
// Author : 山田　陵太
//
//=============================================================================

//二重インクルード防止
#ifndef _PLAYER_FLAG_RAICING_H_
#define _PLAYER_FLAG_RAICING_H_

//*****************************
// インクルード
//*****************************
#include "player.h"

class CAddPointDisplay;
class CPlayerFlagRaicing :public CPlayer
{
public:
	CPlayerFlagRaicing();
	~CPlayerFlagRaicing();

	static CPlayerFlagRaicing *Create(D3DXVECTOR3 pos, int nPlayerNum);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CAddPointDisplay *GetAddPoitDisplay(void) { return m_pAddPointDisplay; }
private:
	void ControllFlipper(void);    // 羽の操作

	CAddPointDisplay *m_pAddPointDisplay;
};
#endif // !_PLAYER_FLAG_RAICING_H_
