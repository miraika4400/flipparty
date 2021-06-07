//=============================================================================
//
// motionヘッダ [motion.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _MOTION_H_
#define _MOTION_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "model_hierarchy.h"

//*****************************
// 前方宣言
//*****************************
class CCollision;

//*****************************
// マクロ定義
//*****************************
#define MAX_KEYFRAME 10       // キーフレームの最大数

//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CMotion :CScene
{
public:

	//============
	// メンバ関数
	//============
	CMotion();
	~CMotion();

	static CMotion *Create(int nNumParts, const char *pPath, CResourceModel::Model*pModel); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	// モデルデータのセット
	void SetModel(CResourceModel::Model*pModel) { m_pModel = pModel; }
	// 現在キーの取得
	int GetKey(void) { return m_nCntKey; }
	// 現在フレームの取得
	int GetFrame(void) { return m_nCntFrame; }

	// アニメーション状態のセット・取得
	void SetActiveMotion(bool bActive);
	bool GetActiveMotion(void) { return m_bMotion; }
private:
	void Load(const char *pPath); // モーションテキストの読み込み

	//============
	// メンバ変数
	//============
	CResourceModel::Model *m_pModel; // モデル情報
	D3DXVECTOR3 m_pos[MAX_KEYFRAME][MAX_PARTS_NUM];// 座標の目標値
	D3DXVECTOR3 m_rot[MAX_KEYFRAME][MAX_PARTS_NUM];// 回転の目標値
	D3DXVECTOR3 m_addPos[MAX_PARTS_NUM];     // 座標の加算値
	D3DXVECTOR3 m_addRot[MAX_PARTS_NUM];     // 回転の加算値

	int m_nNumKey;                   // キーフレームの数
	int m_nNumParts;                 // パーツ数
	int m_nNumFrame[MAX_KEYFRAME];   // フレーム数
	int m_nCntKey;                   // キーカウント
	int m_nCntFrame;                 // フレームカウント
	bool m_bMotion;                  // モーションしているか
	bool m_bLoop;                    // ループするか
};

#endif