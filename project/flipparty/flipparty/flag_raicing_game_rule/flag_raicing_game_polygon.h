//=============================================================================
//
// resultboardヘッダ [resultboard.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _FLAG_RAICING_GAME_POLYGON_
#define _FLAG_RAICING_GAME_POLYGON_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"
#include "rule_manager.h"

//=============================
// 前方宣言
//=============================
class CPolygon;
class CNumber;

//=============================
// マクロ定義
//=============================
#define POINT_MAX_DIGIT 2 // スコア最大桁数

//=============================
//クラス定義
//=============================

//リザルトボードクラス
class CFlagRaicingGamePolygon
{
public:
	//============
	// メンバ関数
	//============
	CFlagRaicingGamePolygon();
	~CFlagRaicingGamePolygon();

	static CFlagRaicingGamePolygon *Create(int nPlayerNum, D3DXVECTOR3 pos); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	void CreateScore(void);          // スコアポリゴンの生成

	//============
	// メンバ変数
	//============
	D3DXVECTOR3 m_pos;  // 座標
	int m_nPlayerNum;
	CNumber *m_apScoreNumber[POINT_MAX_DIGIT];           // スコアの数字ポリゴン
	CPolygon * m_pBack;                                  // 背景
};

#endif