//=============================================================================
//
// numberヘッダ [number.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************
//インクルード
//*****************************
#include "main.h"

//*****************************
//クラス定義
//*****************************

//ナンバークラス
class CNumber
{
public:
	//============
	// メンバ関数
	//============

	CNumber();
	~CNumber();
	static CNumber *Create(const int nNum, const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col); // クラス生成
	static HRESULT Load(void);                                                                                  // テクスチャロード
	static void Unload(void);                                                                                   // テクスチャアンロード

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col); // 初期化
	void Uninit(void);                                                                // 終了
	void Update(void);                                                                // 更新
	void Draw(void);                                                                  // 描画
	void SetNumber(const int nNumber);                                                // ナンバーのセット

	// カラーのセット、取得
	void SetColor(const D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }
private:
	//============
	// メンバ変数
	//============
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;	// 頂点バッファへのポイン
	int m_nNumber;                          // ナンバー
	D3DXCOLOR m_col;                        // 色
};

#endif