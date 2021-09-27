//=============================================================================
//
// scene3d_shaderヘッダ [scene3d_shader.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _SCENE3D_SHADER_H_
#define _SCENE3D_SHADER_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
// マクロ定義
//*****************************
#define MAX_TEHNIQUENAME_LENGTH_OBJ 64

//*****************************
//クラス定義
//*****************************

//3dポリゴンクラス
class CObject3dShader : public CScene
{
public:
	//============
	// 構造体定義
	//============
	// 頂点情報
	typedef struct
	{
		D3DXVECTOR3 pos; // 座標
		D3DXVECTOR3 nor; // 法線
		D3DXVECTOR2 tex; // テクスチャuv
		D3DXVECTOR3 tangent;// 接線
		D3DCOLOR    col; // 色
	}VERTEX_3D_SHADER;

	// シェーダー構造体
	typedef struct
	{
		LPD3DXEFFECT pEffect;                             // エフェクトファイル
		char achTechniqueName[MAX_TEHNIQUENAME_LENGTH_OBJ];   // HLSLテクニックネーム
		LPDIRECT3DCUBETEXTURE9 pCubeTex;                  // キューブテクスチャポインタ
	}Shader;

	//============
	// メンバ関数
	//============
	CObject3dShader(int nPriority = 3);
	~CObject3dShader();

	static CObject3dShader *Create(void); // クラス生成

	HRESULT Init(void);                                                            // 初期化
	void Uninit(void);                                                             // 終了
	void Update(void);                                                             // 更新
	void Draw(void);                                                               // 描画
	LPDIRECT3DTEXTURE9 GetTexture(void) { return m_pTexture; }                     // テクスチャの取得
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; } // テクスチャの割り当て

																				   // 中心座標のセット、取得
	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	// 回転のセット、取得
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	// サイズのセット、取得
	void SetSize(const D3DXVECTOR3 size);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	// カラーのセット、取得
	void SetColor(const D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }

	void SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX]); // テクスチャのUV座標のセット
	void SetAddMode(bool bBool) { m_bAddMode = bBool; }  // 加算モードの切り替え

	Shader GetShader(void) { return m_shader; }
	void SetShader(Shader shader) { m_shader = shader; }  // シェーダーのセット

private:
	virtual void SetShaderValue(void); // シェーダーの値セット処理

									   //============
									   // メンバ変数
									   //============
	Shader m_shader;    // シェーダー構造体
	LPDIRECT3DTEXTURE9		m_pTexture;         // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;         // 頂点バッファへのポインタ
	D3DXVECTOR3	m_pos;                          // ポリゴンの位置
	D3DXVECTOR3	m_rot;                          // ポリゴンの回転
	D3DXVECTOR3 m_size;                         // ポリゴンのサイズ
	D3DXCOLOR   m_col;                          // 色
	D3DXMATRIX  m_mtxWorld;                     // ワールドマトリックス
	bool        m_bAddMode;                     // 加算合成か
	LPDIRECT3DINDEXBUFFER9 m_pldxBuff = NULL;   // テクスチャ
	LPDIRECT3DVERTEXDECLARATION9 m_pDecl;       // 頂点宣言
};

#endif