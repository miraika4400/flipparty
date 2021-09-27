//=============================================================================
//
// enddisplayヘッダ [enddisplay.h]
// Author : 山田陵太
//
//=============================================================================

//二重インクルード防止
#ifndef _ENDDISPLAY_H_
#define _ENDDISPLAY_H_


//*****************************
//インクルード
//*****************************
#include "scene2d.h"

//=============================================================================
//終了表示
//=============================================================================
class CEndDisplay :public CScene2d
{
public:
	CEndDisplay();
	~CEndDisplay();

	static CEndDisplay *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nCntTime;		//タイムカウント
};
#endif 