//=============================================================================
//
// stageヘッダ [stage.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _STAGE_H_
#define _STAGE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "model.h"

//=============================
// 前方宣言
//=============================

//*****************************
//クラス定義
//*****************************

//氷山クラス
class CStage : public CModel
{
public:
	//============
	// 列挙
	//============

	// ステージタイプ
	typedef enum
	{
		STAGE_TYPE_NORMAL = 0, // ノーマル
		STAGE_TYPE_LARGE,      // 大きい
		STAGE_TYPE_MAX         // タイプ最大数
	}STAGE_TYPE;

	//============
	// メンバ関数
	//============
	CStage();
	~CStage();

	static CStage *Create(D3DXVECTOR3 pos , STAGE_TYPE type); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	void DrawModel(void);   // モデル描画処理
	void SetWorldmtx(void); // ワールドマトリックスの設定
	void SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData);// シェーダに値を送る

	//============
	// メンバ変数
	//============
	STAGE_TYPE m_type;
};

#endif