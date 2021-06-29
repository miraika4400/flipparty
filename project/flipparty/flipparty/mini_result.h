//=============================================================================
//
// mini_resultヘッダ [mini_result.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _MINI_RESULT_H_
#define _MINI_RESULT_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// 前方宣言
//=============================
class CPolygon;

//*****************************
//クラス定義
//*****************************

//タイトルクラス
class CMiniResult : public CScene
{
public:
	//============
	// メンバ関数
	//============
	CMiniResult();
	~CMiniResult();

	static CMiniResult *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:

};

#endif