//=============================================================================
//
// z_texヘッダ [z_tex.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _ZTEX_H_
#define _ZTEX_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
//*****************************
// マクロ定義
//*****************************

//*****************************
// 前方宣言
//*****************************

//*****************************
// クラス定義
//*****************************

// X値テクスチャークラス
class CZTex
{
public:
	// メンバ関数
	CZTex();
	~CZTex();

	static CZTex*Create(void); // クラス生成
	HRESULT Init(void);        // 初期化
	void Uninit(void);         // 終了
	void Begin(void);          // テクスチャ書き込み開始
	void End(void);            // 書き込み終了

private:
	// メンバ変数
	LPDIRECT3DTEXTURE9 m_pZBufTex; // Z値テクスチャ
	LPDIRECT3DSURFACE9 m_pZTexSurf;  // Z値テクスチャサーフェイス
	LPDIRECT3DSURFACE9 m_pZTexZBuf;  // 深度バッファサーフェイス
};

#endif
