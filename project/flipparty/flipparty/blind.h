//=============================================================================
//
// blindヘッダ [blind.h]
// Author : 増澤 未来
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

//2dポリゴンクラス
class CBlind : public CScene3d
{
public:
	CBlind();
	~CBlind();

	static CBlind *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};

#endif