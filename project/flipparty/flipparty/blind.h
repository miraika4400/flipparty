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

	typedef enum
	{
		BLIND_STATE_MOVE = 0,
		BLIND_STATE_NORMAL,
		BLIND_STATE_MAX
	}BLIND_STATE;

	CBlind();
	~CBlind();

	static CBlind *Create(int nTime,int nStartTime);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTime(int nTime) { m_nTime = nTime; }
	BLIND_STATE GetState(void) { return m_state; }
private:
	int m_nTime;	//タイマー
	int m_nMoveStartTime;	//移動開始タイム
	BLIND_STATE m_state;	//ブラインドの状態
	CScene3d *m_pBlackPolygon;	//黒ポリゴン
};

#endif