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

	//メンバ関数
	CPlayer();
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, int nPlayerNum);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void ControllFlipper(void);    // 羽の操作
	void ManageFlipperAngle(void); // 羽の角度管理

	// メンバ変数
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // モデル構造体
	static int m_nPartsNum;        // モデルパーツ数
	int m_nPlayerNum;              // プレイヤー番号
	CFlipper * m_pFlieer;          // フリッパークラス
	float m_fFlipperDist[2];       // フリッパーの角度目標値
	CBillboard * m_pPlayerNumIcon; // プレイヤー番号のアイコン

#ifdef _DEBUG
	// デバッグ用変数
	CPolygon * m_pPolygon[2];// ポリゴンクラスのポインタ
#endif // _DEBUG

};

#endif#pragma once
