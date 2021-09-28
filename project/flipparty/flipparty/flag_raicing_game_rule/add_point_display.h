//=============================================================================
//
// add_point_displayヘッダ [add_point_display.h]
// Author : 山田　陵太
//
//=============================================================================

//二重インクルード防止
#ifndef _ADD_POINT_DISPLAY_H_
#define _ADD_POINT_DISPLAY_H_

//=============================================================================
//インクルード
//=============================================================================
#include "scene.h"
#include "scene2d.h"

//=============================================================================
//クラス定義
//=============================================================================
class CAddPointDisplay :public CScene2d
{
public:
	//=========================================================================
	//表示するテクスチャの種類の列挙
	//=========================================================================
	typedef enum
	{
		POINT_DISPLAY_TYPE_3PT = 0,
		POINT_DISPLAY_TYPE_2PT,
		POINT_DISPLAY_TYPE_1PT,
		POINT_DISPLAY_TYPE_0PT,
		POINT_DISPLAY_TYPE_MISS,
		POINT_DISPLAY_TYPE_MAX
	}POINT_DISPLAY_TYPE;

	CAddPointDisplay();
	~CAddPointDisplay();

	static CAddPointDisplay *Create(int nPlayerNumber);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetDisplay(POINT_DISPLAY_TYPE displayType);
private:
	POINT_DISPLAY_TYPE m_displayType;	//表示するテクスチャのタイプ
	int m_nPlayerNumber;				//プレイヤー番号
	bool m_IsDraw;						//描画するかどうか
	int m_nShoeCounter;					//描画する時間のカウンター
};
#endif // !_ADD_POINT_DISPLAY_H_
