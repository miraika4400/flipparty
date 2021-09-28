//=============================================================================
//
// passingpenguinヘッダ [passingpenguin.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _PASSING_PENGUIN_H_
#define _PASSING_PENGUIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "model_hierarchy.h"

//*****************************
// 前方宣言
//*****************************
class CMotion;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPassingPenguin :public CModelHierarchy
{
public:
	//移動方向の列挙型
	typedef enum
	{
		MOVE_DIRECTION_LEFT = 0,	//左へ移動
		MOVE_DIRECTION_RIGHT,		//右へ移動
		MOVE_DIRECTION_MAX
	}MOVE_DIRECTION;
	
	//状態の列挙型
	typedef enum
	{
		STATE_WAIT = 0,	//待機
		STATE_MOVE,		//移動
		STATE_MAX
	}STATE;

	CPassingPenguin();
	~CPassingPenguin();
	static CPassingPenguin *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMoveDirection(MOVE_DIRECTION moveDirection);
private:
	void Move(void);
	void DrawModel(void);// モデルの描画
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model *pModelData); // シェーダープログラムに値を送る

	// メンバ変数
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // モデル構造体
	static int m_nPartsNum;	//モデルパーツ数
	static char m_achAnimPath[64];   // モーションテキストのパス格納用
	CMotion *m_pMotion;              // モーションポインタ
	int m_facePattern;
	MOVE_DIRECTION m_moveDirection;	//移動方向
	STATE m_state;	//状態
	D3DXVECTOR3 m_move;	//移動量
	int m_nSoudCounter;

};
#endif 