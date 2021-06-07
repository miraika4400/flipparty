//=============================================================================
//
// fadeヘッダ [fade.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _FADE_H_
#define _FADE_H_
//***********************************
//インクルード
//***********************************
#include "main.h"
#include "manager.h"

//***********************************
// 前方宣言
//***********************************
class CPolygon;

//=============================
//クラス定義
//=============================

//フェードクラス
class CFade
{
public:
	//============
	// 列挙定義
	//============
	// フェード状態
	typedef enum
	{
		FADE_NONE = 0, // 何でもない状態
		FADE_IN,       // フェードイン
		FADE_OUT,      // フェードアウト
		FADE_MAX,      // 状態の最大数
	}FADE;

	//============
	// メンバ関数
	//============
	CFade();
	~CFade();

	static CFade*Create(void); //クラス生成

	HRESULT Init(void);                // 初期化
	void Uninit(void);                 // 終了
	void Update(void);                 // 更新
	void Draw(void);                   // 描画
	void SetFade(CManager::MODE mode); // フェードのセット
private:
	//============
	// メンバ変数
	//============
	CPolygon*      m_pPolygon;  // フェードポリゴン
	D3DXCOLOR      m_col;       // カラー
	CManager::MODE m_modeNext;  // ネクストモード
	FADE           m_fade;      // フェード状態
};

#endif