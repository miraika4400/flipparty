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
#define RIGHT_FLIPPER_PARTS_NUM 5 // 右羽のパーツ番号
#define LEFT_FLIPPER_PARTS_NUM  4 // 左羽のパーツ番号
#define PLAYER_HEAD_PARTS_NUM 2
#define RIGHT_FLIPPER_DIST_ANGLE_UP   D3DXToRadian(-60.0f)           // 右羽を上げたときの角度
#define RIGHT_FLIPPER_DIST_ANGLE_DOWN D3DXToRadian(30.0f)            // 右羽を下げたときの角度
#define LEFT_FLIPPER_DIST_ANGLE_UP    -RIGHT_FLIPPER_DIST_ANGLE_UP   // 左羽を上げたときの角度
#define LEFT_FLIPPER_DIST_ANGLE_DOWN  -RIGHT_FLIPPER_DIST_ANGLE_DOWN // 左羽を下げたときの角度
#define PLAYER_SHADOW_SIZE  D3DXVECTOR3(25.0f ,0.0f, 25.0f)
#define PLAYER_SHADOW_COLOR D3DXCOLOR(1.0f ,1.0f, 1.0f,0.5f)

//*****************************
// 前方宣言
//*****************************
class CFlipper;
class CBillboard;
class CMotion;
class CScene3d;
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

	// 列挙
	//モーション
	typedef enum
	{
		MOTION_IDOL = 0,     // アイドル
		MOTION_MINIRESULT_1, // ミニリザルト1位
		MOTION_MINIRESULT_2, // ミニリザルト2位
		MOTION_MINIRESULT_3, // ミニリザルト3位
		MOTION_MINIRESULT_4, // ミニリザルト最下位
		MOTION_FLY,          // 飛び
		MOTION_THUNDER,      // 雷
		MOTION_FALL,         // 転ぶ
		MOTION_MAX
	}MOTION_TYPE;

	// 表情パターン
	typedef enum
	{
		FACE_PATTERN_NORMAL = 0,
		FACE_PATTERN_GOOD,
		FACE_PATTERN_NO_GOOD,
		FACE_PATTERN_MAX
	}FACE_PATTERN;

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
	// プレイヤー番号のセット・取得
	void SetPlayerNumber(int nNum) { m_nPlayerNum = nNum; }
	int GetPlayerNumber(void) { return m_nPlayerNum; }

	CFlipper*GetFlipper(void) { return m_pFlipper; }
	CFlipper*GetFlipperMoveState(void) { return m_pFlipperMoveState; }
	
	// モーションのセット
	void SetMotion(MOTION_TYPE type);
	bool GetMotionActive(MOTION_TYPE type);

	// 表情のセット
	void SetFacePattern(FACE_PATTERN pattern) { m_facePattern = pattern; }

	void SetPoint(int point) { m_nPoint = point; }
	void AddPoint(int point) { m_nPoint += point; }
	int GetPoint(void) { return m_nPoint; }
	// フリッパー目標値セット
	void SetFlipperDist(int nIndex, float fAngle) { m_fFlipperDist[nIndex] = fAngle; }

private:
	void DrawModel(void); // モデルの描画
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model *pModelData); // シェーダープログラムに値を送る

	virtual void ControllFlipper(void);    // 羽の操作
	void ManageFlipperAngle(void);         // 羽の角度管理

protected:
	CFlipper * m_pFlipperMoveState;                      // フリッパーの移動状態
	float m_fFlipperDist[FLIPPER_NUM];                   // フリッパーの角度目標値

	// メンバ変数
	static CResourceModel::Model m_model[MAX_PARTS_NUM]; // モデル構造体
	static int m_nPartsNum;                              // モデルパーツ数
	int m_nPlayerNum;                                    // プレイヤー番号
	CFlipper * m_pFlipper;                               // フリッパークラス
	
	CBillboard * m_pPlayerNumIcon;                       // プレイヤー番号のアイコン
	bool m_bMove;                                        // 動けるかどうかのフラグ
	int m_nRank;                                         // 順位
	FACE_PATTERN  m_facePattern;                         // 表情切り替え用
	int m_nPoint;                                        // ポイント

	// モーション用変数
	static char m_achAnimPath[MOTION_MAX][64];   // アニメーションテキストのパス格納用
	CMotion *m_apMotion[MOTION_MAX];  // アニメーションポインタ
	CMotion *m_pActiveMotion;         // 現在再生中のモーション

};

#endif#pragma once
