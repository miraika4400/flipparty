//=============================================================================
//
// 指示ポリゴンヘッダ [orderpolygon.h]
// Author : 山田　陵太
//
//=============================================================================

//二重インクルード防止
#ifndef ORDER_POLYGON_H
#define ORDER_POLYGON_H

//*****************************
// インクルード
//*****************************
#include "scene.h"
#include "flipper.h"

//*****************************
// 前方宣言
//*****************************
class CBillboard;

//*****************************
// クラス定義
//*****************************
class COrderPolygon :public CScene
{
public:
	typedef struct
	{
		CBillboard *pOrderBillboard;
		bool bIsDraw;
	}ORDER;

	COrderPolygon();
	~COrderPolygon();

	static COrderPolygon *Crate(void);	//クリエイト処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	void SetDraw(CFlipper::FLIPPER_TYPE flipperState, CFlipper::FLIPPER_STATE state);		//描画設定処理
	static void SetUse(bool bUse) { m_bUse = bUse; }

private:
	static bool m_bUse;
	ORDER m_Order[CFlipper::FLIPPER_TYPE_MAX];
};

#endif