//=============================================================================
//
// captainヘッダ [captain.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CAPTAIN_H_
#define _CAPTAIN_H_

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

//*****************************
// クラス定義
//*****************************

// キャプテン(見本ペンギン)クラス
class CCaptain : public CModelHierarchy
{
public:

	//メンバ関数
	CCaptain();
	~CCaptain();
	static CCaptain *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	// メンバ変数
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // モデル構造体
	static int m_nPartsNum;

};

#endif#pragma once
