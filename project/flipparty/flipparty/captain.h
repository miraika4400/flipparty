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

//*****************************
// クラス定義
//*****************************

// キャプテン(見本ペンギン)クラス
class CCaptain : public CModelHierarchy
{
public:
	typedef enum
	{
		RED_FLAG_UP = 0,	// 赤上がっている状態
		BLUE_FLAG_UP,		// 青上がっている状態
		RED_FLAG_DOWN,		// 赤下がっている状態
		BLUE_FLAG_DOWN,		// 青下がっている状態
		FLAG_END
	}FLAG;

	typedef enum
	{
		FLAG_TEX_RIGHT,
		FLAG_TEX_LEFT,
		FLAG_TEX_MAX
	}FLAG_TEX;

	typedef struct
	{
		bool bFlagRight;
		bool bFlagLeft;
		CBillboard * apFlagTex[MAX_FLAG_TEXTURRE];		// 右左どちらを上げるかのテクスチャを表示させる変数
	}FLAG_TEX_VARIABLE;

	typedef enum
	{
		COLOR_NORMAL = 0,
		BLUE_UP,			// 青上がっている状態
		BLUE_DOWN,			// 青下がっている状態
		RED_UP,				// 赤上がっている状態
		RED_DOWN,			// 赤下がっている状態
		COLOR_END
	}COLOR;

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

	void Judge(FLAG ColorFlagRed, FLAG ColorFlagWhite, COLOR ColorRed, COLOR ColorWhite);	// 色判別処理
	void JudgeColor(FLAG ColorFlagRed, FLAG ColorFlagWhite, COLOR ColorRed, COLOR ColorWhite);
	void FlagJudge();

	void ManageFlipperAngle(void); // 羽の角度管理
	void Choice(int choice) { m_nChoice = choice; }

	CFlipper*GetFlipper(void) { return m_pFlipper; }
	CFlipper*GetFlipperMoveState(void) { return m_pFlipperMoveState; }

	// 表情のセット
	void SetFacePattern(FACE_PATTERN pattern) { m_facePattern = pattern; }

private:
	void DrawModel(void);// モデルの描画
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model *pModelData); // シェーダープログラムに値を送る

	// メンバ変数
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // モデル構造体
	static int m_nPartsNum;

	int m_nCntTime;
	int m_nColor;
	int m_nCount;
	int m_nChoice;
	int m_facePattern;

	bool m_bJudgRed;				// 赤上げてるか下げてるかの判別
	bool m_bJudgWhite;				// 白上げてるか下げてるかの判別


	FLAG m_eColorRed;
	FLAG m_eColorWhite;

	FLAG_TEX_VARIABLE m_falgTexVal;	//指示テクスチャの構造体変数

	CFlipper * m_pFlipper;          // フリッパークラス
	CFlipper * m_pFlipperMoveState;
	float m_fFlipperDist[2];       // フリッパーの角度目標値

	// モーション用変数
	static char m_achAnimPath[64];   // モーションテキストのパス格納用
	CMotion *m_pMotion;              // モーションポインタ
};

#endif
