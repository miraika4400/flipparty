//=============================================================================
//
// cloudヘッダ [cloud.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CLOUD_H_
#define _CLOUD_H_

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

//雲クラス
class CCloud : public CModel
{
public:
	//============
	// メンバ関数
	//============
	CCloud();
	~CCloud();

	static CCloud *Create(int nPlayerNum); // クラス生成
	
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
	D3DXVECTOR3 m_size; // サイズ
	D3DXCOLOR m_color;  // 色
	int m_nCntAction;   // アクションカウント
	float m_fAlpha;
	int m_nPlayerNum;   // プレイヤー番号
	D3DXVECTOR3 m_playerPosSave; // プレイヤー座標の保存用
	bool m_bThunder; // 雷を落としたか判定用
};

#endif