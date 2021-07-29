//=============================================================================
//
// icebergヘッダ [iceberg.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _ICEBERG_H_
#define _ICEBERG_H_

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
class CIceberg : public CModel
{
public:
	//============
	// 列挙
	//============

	// 氷山タイプ
	typedef enum
	{
		ICEBERG_Y = 0, // 山田
		ICEBERG_M,     // 増澤
		ICEBERG_K,     // 工藤
		ICEBERG_MAX
	}ICEBERG_TYPE;
	//============
	// メンバ関数
	//============
	CIceberg();
	~CIceberg();

	static CIceberg *Create(D3DXVECTOR3 pos, ICEBERG_TYPE type); // クラス生成

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
	ICEBERG_TYPE m_type;
};

#endif