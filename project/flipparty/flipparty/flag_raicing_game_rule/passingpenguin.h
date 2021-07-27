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
	CPassingPenguin();
	~CPassingPenguin();
	static CPassingPenguin *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void DrawModel(void);// モデルの描画
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model *pModelData); // シェーダープログラムに値を送る


	// メンバ変数
	static CResourceModel::Model m_model[MAX_PARTS_NUM];    // モデル構造体
	static int m_nPartsNum;	//モデルパーツ数
	static char m_achAnimPath[64];   // モーションテキストのパス格納用
	CMotion *m_pMotion;              // モーションポインタ

};
#endif 