//=============================================================================
//
// resource_modelヘッダ [resource_model.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _RESOURCEMODEL_H_
#define _RESOURCEMODEL_H_

//*****************************
//インクルード
//*****************************
#include "main.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_MATERIAL 64 // テクスチャ最大数

//*****************************
//クラス定義
//*****************************

// モデルリソースクラス
class CResourceModel
{
public:

	//============
	//構造体
	//============
	// モデルデータ
	typedef struct
	{
		LPDIRECT3DTEXTURE9 apTexture[MAX_MATERIAL]; // テクスチャ
		LPD3DXMESH pMesh;                           // メッシュ情報へのポインタ
		LPD3DXBUFFER pBuffMat;                      // マテリアル情報へのポインタ
		DWORD nNumMat;                              // マテリアル情報の数
		D3DXVECTOR3 pos;                            // 位置
		D3DXVECTOR3 size;                           // 大きさ
		D3DXVECTOR3 rot;                            // 向き
		D3DXMATRIX mtxWorld;                        // ワールドマトリックス
		D3DXMATERIAL defMat[MAX_MATERIAL];          // マテリアル保管用
		D3DXCOLOR diffuseCol[MAX_MATERIAL];         // カラー*拡散
		int nParent;                                // 親のインデックス
	}Model;

	// 列挙
	// モデル種類
	typedef enum
	{
		MODEL_GENERAL_SPHERE = 0, // 汎用モデル球
		MODEL_GENERAL_BOX,        // 汎用モデルボックス
		MODEL_TEST,               // テストモデル
		MODEL_MAX        // モデル数
	}MODEL_TYPE;

	// メンバ関数
	static CResourceModel * Create(void);                  // クラス生成
	static void Release(void);                               // クラス破棄
	static Model* GetModel(MODEL_TYPE type); // モデルの取得処理*引数：取得したいモデル

private:
	CResourceModel();//隠しコンストラクタ
public:
	~CResourceModel();

private:
	void Load(void); // モデル読み込み
	void Unload(void); // モデル破棄

	// メンバ変数
	static const std::string m_aModelPath[MODEL_MAX]; // モデルのパス
	static CResourceModel *m_pSingle;              // モデルクラスのポインタ*シングルトン用
	Model m_apModel[MODEL_MAX];               // モデルのポインタ
};

#endif