//=============================================================================
//
// stratcountヘッダ [stratcount.h]
// Author : 山田陵太
//
//=============================================================================

//二重インクルード防止
#ifndef _STRATCOUNT_H_
#define _STRATCOUNT_H_


//*****************************
//インクルード
//*****************************
#include "scene.h"

class CNumber;
class CScene2d;

class CStratCount :public CScene
{
public:
	CStratCount();
	~CStratCount();

	static CStratCount *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CNumber *m_pNumber;	//ナンバークラスのポインタ変数
	CScene2d *m_pScene2D;
	int m_nCntTime;		//タイムカウント
	int m_nLimitTime;	//制限時間
};
#endif 