//=============================================================================
//
// sceneヘッダ [scene.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _SCENE_H_
#define _SCENE_H_

//インクルード
#include "main.h"

//***********************************
//マクロ定義
//***********************************
#define MAX_SCENE 1280   // ポリゴンの最大数
#define PRIORITY_NUM OBJTYPE_MAX
#define MAX_TEHNIQUENAME_LENGTH 64

//=============================
//クラス定義
//=============================

//シーンクラス
class CScene
{
public:
	//============
	// 構造体定義
	//============
	// シェーダー構造体
	typedef struct
	{
		LPD3DXEFFECT pEffect;                             // エフェクトファイル
		char achTechniqueName[MAX_TEHNIQUENAME_LENGTH];   // HLSLテクニックネーム
		LPDIRECT3DCUBETEXTURE9 pCubeTex;                  // キューブテクスチャポインタ
	}Shader;

	//============
	// 状態列挙
	//============
	// オブジェクトタイプ列挙
	// 更新・描画順
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,         // 背景
		OBJTYPE_ITEM,       // アイテム
		OBJTYPE_ATTACK,     // 攻撃
		OBJTYPE_PLAYER,     // プレイヤー
		OBJTYPE_CPU,        // CPU
		OBJTYPE_CHECKPOINT, // チェックポイント
		OBJTYPE_MAP,        // マップ
		OBJTYPE_PARTICLE,   // パーティクル
		OBJTYPE_MOTION,     // モーション
		OBJTYPE_UI,         // UI
		OBJTYPE_COLLISION,  // コリジョン
		OBJTYPE_SYSTEM,     // システム
		OBJTYPE_MAX,        // タイプの最大数
	}OBJTYPE;

	//============
	// メンバ関数
	//============
	CScene(int nPriority = OBJTYPE_NONE);
	virtual ~CScene();
	static void ReleaseAll(void);                   // すべて解放
	static void UpdateAll(void);                    // すべて更新
	static void DrawAll(void);                      // すべて描画
	static int GetNumAll(void) { return m_nIDAll; } // これまで生成されたオブジェクトの数
	 
	void SetPriority(const int  nPriority);   // プライオリティの設定
	OBJTYPE GetType(void) { return m_type; }  // オブジェクトタイプの取得
	int GetID(void) { return m_nNumID; }      // 配列番号の取得

	static CScene*GetTop(int nIndex) { return m_pTop[nIndex]; }  // リスト構造トップの取得
	static CScene*GetCur(int nIndex) { return m_pCur[nIndex]; }  // リスト構造カレントの取得
	CScene*GetNext(void) { return m_pNext; }                     // リスト構造ネクストの取得
	CScene*GetPrev(void) { return m_pPrev; }                     // リスト構造プレビューの取得

	// 純粋仮想関数
	virtual HRESULT Init(void) = 0; // 初期化
	virtual void Uninit(void) = 0;  // 終了
	virtual void Update(void) = 0;  // 更新
	virtual void Draw(void) = 0;    // 描画

protected:
	void Release(void);      // 解放処理
private:
	void ReConnection(void); // リスト構造から自身を消してつなぎなおす

	//============
	// メンバ変数
	//============
	static int m_nIDAll;                   // 生成したポリゴン数
	int     m_nNumID;                      // 生成したポリゴンの配列
	OBJTYPE m_type;                        // オブジェクトタイプ
	int     m_nPriority;                   // プライオリティ
	bool    m_bReleasFlag;                 // 削除フラグ

	// リスト構造
	static CScene * m_pTop[PRIORITY_NUM];  // 先頭
	static CScene * m_pCur[PRIORITY_NUM];  // 最後
	CScene * m_pNext;                      // 次 
	CScene * m_pPrev;                      // 前
};

#endif