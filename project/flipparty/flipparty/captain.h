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
#define MAX_FLAG_TEXTURRE 2

//*****************************
// 前方宣言
//*****************************
class CFlipper;
class CMotion;
class CBillboard;
class COrderPolygon;

//*****************************
// クラス定義
//*****************************

// キャプテン(見本ペンギン)クラス
class CCaptain : public CModelHierarchy
{
public:
	// 表情パターン
	typedef enum
	{
		FACE_PATTERN_NORMAL = 0,
		FACE_PATTERN_GOOD,
		FACE_PATTERN_NO_GOOD,
		FACE_PATTERN_MAX
	}FACE_PATTERN;

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

	void ManageFlipperAngle(void); // 羽の角度管理

	CFlipper*GetFlipper(void) { return m_pFlipper; }
	CFlipper*GetFlipperMoveState(void) { return m_pFlipperMoveState; }

	// 表情のセット
	void SetFacePattern(FACE_PATTERN pattern) { m_facePattern = pattern; }

private:
	void DrawModel(void);// モデルの描画
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model *pModelData); // シェーダープログラムに値を送る
	void ChangeFlipper(void);	//羽の状態変更
	
	// メンバ変数
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // モデル構造体
	static int m_nPartsNum;	//パーツ数

	int m_facePattern;	//顔テクスチャパターン

	CFlipper * m_pFlipper;          // フリッパークラス
	CFlipper * m_pFlipperMoveState;
	float m_fFlipperDist[2];       // フリッパーの角度目標値
	COrderPolygon *m_pOrder;
	// モーション用変数
	static char m_achAnimPath[64];   // モーションテキストのパス格納用
	CMotion *m_pMotion;              // モーションポインタ
};

#endif
