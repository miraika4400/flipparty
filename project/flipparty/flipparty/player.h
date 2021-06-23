//=============================================================================
//
// playerヘッダ [player.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "model_hierarchy.h"
#include "game.h"

//*****************************
// マクロ定義
//*****************************
#define PLAYER_CENTER_HEIGHT 35.0f
#define FLIPPER_NUM 2 // 手の数
//*****************************
// 前方宣言
//*****************************
class CFlipper;
class CBillboard;
#ifdef _DEBUG
class CPolygon;
#endif // _DEBUG

//*****************************
// クラス定義
//*****************************

// プレイヤークラス
class CPlayer : public CModelHierarchy
{
public:

	// メンバ関数
	CPlayer();
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, int nPlayerNum);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ムーブフラグのセット・取得
	void SetMoveFlag(bool bMove) { m_bMove = bMove; }
	bool GetMoveFlag(void) { return m_bMove; }
	// 順位のセット・取得
	void SetRank(int nRank) { m_nRank = nRank; }
	int GetRank(void) { return m_nRank; }

	CFlipper*GetFlipper(void) { return m_pFlipper; }
	CFlipper*GetFlipperMoveState(void) { return m_pFlipperMoveState; }
	
private:
	void ControllFlipper(void);    // 羽の操作
	void ManageFlipperAngle(void); // 羽の角度管理

	// メンバ変数
	static CResourceModel::Model m_model[MAX_PARTS_NUM];  // モデル構造体
	static int m_nPartsNum;             // モデルパーツ数
	int m_nPlayerNum;                   // プレイヤー番号
	CFlipper * m_pFlipper;              // フリッパークラス
	CFlipper * m_pFlipperMoveState;     // フリッパーの移動状態
	float m_fFlipperDist[FLIPPER_NUM];  // フリッパーの角度目標値
	CBillboard * m_pPlayerNumIcon;      // プレイヤー番号のアイコン
	bool m_bMove;                       // 動けるかどうかのフラグ
	int m_nRank;                        // 順位

#ifdef _DEBUG
	// デバッグ用変数
	CPolygon * m_pPolygon[2];// ポリゴンクラスのポインタ
#endif // _DEBUG

};

#endif#pragma once
