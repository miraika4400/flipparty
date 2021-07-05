//=============================================================================
//
// モデル処理 [model.h]
// Author : 増澤 未来
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene.h"
#include "resource_model.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_MATERIAL 64 // テクスチャ最大数

//=============================================================================
//モデルクラス
//=============================================================================
class CModel : public CScene
{
public:
	//============
	//列挙
	//============
	
	//============
	//構造体
	//============


	//============
	// メンバ関数
	//============
	CModel(int nPliority = OBJTYPE_NONE);
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos , CResourceModel::MODEL_TYPE modelType  ,D3DXVECTOR3 size = D3DXVECTOR3(1.0f, 1.0f, 1.0f)); // クラス生成*座標,汎用モデルタイプ,サイズ

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画
	LPD3DXMESH GetMesh(void)const; // メッシュの取得処理

	void BindModel(CResourceModel::Model* modelData); // モデルの割り当て

	// ゲッター・セッター
	// 座標
	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)const;
	// サイズ
	void SetSize(const D3DXVECTOR3 size);
	D3DXVECTOR3 GetSize(void)const;
	// 回転
	void SetRot(const D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRot(void)const;
	// ワールドマトリックス
	void SetxWorldMatrix(D3DXMATRIX mtxWorld);
	CResourceModel::Model *GetModelData(void);

private:
	virtual void SetWorldmtx(void); // ワールドマトリックスの設定
	virtual void DrawModel(void);   // モデル描画処理

	//============
	// メンバ変数
	//============
	CResourceModel::Model m_model;                                   // モデルデータ

	D3DXMATRIX  m_mtxRot;   // 回転行列
	D3DXMATRIX	m_mtxTrans; // 位置行列
	D3DXMATRIX	m_mtxScail; // サイズ行列
};
#endif 