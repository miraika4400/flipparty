//=============================================================================
//
// blindヘッダ [blind.h]
// Author : 山田 陵太
//
//=============================================================================

//二重インクルード防止
#ifndef _BLIND_H_
#define _BLIND_H_

//*****************************
//インクルード
//*****************************
#include "scene3d.h"

//*****************************
//クラス定義
//*****************************

//ブラインドクラス
class CBlind : public CScene3d
{
public:
	CBlind();
	~CBlind();

	static CBlind *Create(int nTime);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTime(int nTime) { m_nTime = nTime; }
private:
	int m_nTime;	//タイマー
	bool m_bMoving;	//移動可能かどうか
};

#endif