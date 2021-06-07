//=============================================================================
//
// scene3dヘッダ [scene3d.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//クラス定義
//*****************************

//2dポリゴンクラス
class CScene3d : public CScene
{
public:
	// メンバ関数
	CScene3d(int nPliority = OBJTYPE_NONE);
	~CScene3d();
	static CScene3d *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DTEXTURE9 GetTexture(void) { return m_pTexture; }
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }

	// 中心座標のセット、取得
	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	// 中心座標のセット、取得
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	// 回転角度のセット、取得
	void SetAngle(const float fAngle);
	float GetAngle(void) { return m_fAngle; }
	// サイズのセット、取得
	void SetSize(const D3DXVECTOR3 size);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	// カラーのセット、取得
	void SetColor(const D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }

	void SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX]); // テクスチャのUV座標のセット

	void SetAddMode(bool bBool) { m_bAddMode = bBool; }
private:
	// メンバ変数
	LPDIRECT3DTEXTURE9		m_pTexture;	 // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	 // 頂点バッファへのポインタ
	D3DXVECTOR3	m_pos;                   // ポリゴンの位置
	D3DXVECTOR3	m_rot;                   // ポリゴン回転
	D3DXVECTOR3 m_size;                  // ポリゴンのサイズ
	float m_fAngle;                      // ポリゴンの回転角度
	D3DXCOLOR m_col;                     // 色
	D3DXMATRIX m_mtxWorld;               // ワールドマトリックス
	bool m_bAddMode;                     // 加算合成か
	LPDIRECT3DINDEXBUFFER9 m_pldxBuff = NULL;
};

#endif