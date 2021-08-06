//=============================================================================
//
// resultboardヘッダ [resultboard.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _RESULT_BOARD_H_
#define _RESULT_BOARD_H_

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
class CResultBoard : public CScene
{
public:
	//============
	// メンバ関数
	//============
	CResultBoard();
	~CResultBoard();

	static CResultBoard *Create(int nPlayerNum, D3DXVECTOR3 pos); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	D3DXCOLOR ReturnBackColor(void); // プレイヤー番号に応じたカラーを返す
	void CreatePlayerNumber(void);   // プレイヤー番号の生成
	void CreateGameIcon(void);       // ゲームアイコンの生成
	void CreateGameRank(void);       // ゲーム順位ポリゴンの生成
	void CreateScore(void);          // スコアポリゴンの生成

	//============
	// メンバ変数
	//============
	D3DXVECTOR3 m_pos;  // 座標
	int m_nPlayerNum;
	CNumber *m_apScoreNumber[POINT_MAX_DIGIT];           // スコアの数字ポリゴン
	CPolygon * m_pBack;                                  // 背景
	CPolygon * m_pPlayerNumPolygon;                      // プレイヤー番号ポリゴン
	CPolygon * m_apMinigameIcon[CRuleManager::RULE_MAX]; // ミニゲームのアイコン
	CPolygon * m_apMinigameRank[CRuleManager::RULE_MAX]; // ミニゲームの順位
};

#endif