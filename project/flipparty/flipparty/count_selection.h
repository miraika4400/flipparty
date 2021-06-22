//=============================================================================
//
// count_slectionヘッダ [count_slection.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _COUNT_SELECTION_H_
#define _COUNT_SELECTION_H_

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

// 人数選択クラス
class CCountSelect : public CScene
{
public:
	//============
	// 列挙
	//============
	// 人数セレクトUIタイプ
	typedef enum
	{
		SELECT_2_PLAYER = 0,
		SELECT_3_PLAYER,
		SELECT_4_PLAYER,
		SELECT_COUNT_MAX
	}SELECT_UI_TYPE;

	//============
	// メンバ関数
	//============
	CCountSelect();
	~CCountSelect();

	static CCountSelect *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	int GetPlayerNum(void) { return m_nPlayerNum; }// プレイヤー人数の取得処理

private:
	void SelectUi(void);      // UIの選択処理
	void ManageUiColor(void); // UIカラーの管理
	
							  //============
	// メンバ変数
	//============
	static int m_nPlayerNum;                // ゲームに参加しているプレイヤーの人数
	CPolygon *m_pPolygon[SELECT_COUNT_MAX]; // UIポリゴン
	int  m_nSelectUi;                       // 選んでいるUIのタイプ
};

#endif#pragma once
