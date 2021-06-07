//=============================================================================
//
// tutorialヘッダ [tutorial.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
// 前方宣言
//*****************************
class CPolygon;

//*****************************
// マクロ定義
//*****************************
#define TUTORIAL_NUM 1 // チュートリアルページ数

//*****************************
//クラス定義
//*****************************

//チュートリアルクラス
class CTutorial : public CScene
{
public:
	//============
	// メンバ関数
	//===========
	CTutorial();
	~CTutorial();
	static CTutorial *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	//============
	// メンバ変数
	//===========
	static LPDIRECT3DTEXTURE9 m_pTexture[TUTORIAL_NUM]; // テクスチャへのポインタ
	CPolygon *m_pPolygon;                               // ポリゴン
	int m_nNumTutorial;                                 // チュートリアル数

};

#endif