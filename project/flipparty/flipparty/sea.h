//=============================================================================
//
// seaヘッダ [sea.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _SEA_H_
#define _SEA_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "object3d_shader.h"

//*****************************
// マクロ定義
//*****************************

//*****************************
// 前方宣言
//*****************************

//*****************************
// クラス定義
//*****************************

// 海クラス
class CSea : public CObject3dShader
{
public:
	//==========================
	// 列挙
	//==========================
	typedef enum
	{
		TYPE_DIRTY = 0, // 汚染
		TYPE_NORMAL,    // 通常
		TYPE_EVENING,   // 夕方
		TYOE_MAX,
	}SEA_TYPE;

	//==========================
	//メンバ関数
	//==========================
	CSea();
	~CSea();

	static CSea *Create(const D3DXVECTOR3 pos, const float fWaveSpeed, SEA_TYPE seaType); // クラス生成
	static HRESULT Load(void); // ロード
	static void Unload(void);  // アンロード

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	void SetShaderValue(void); // HLSLに値を送る

	//==========================
	//メンバ変数
	//==========================
	static Shader m_shader;              // シェーダー構造体
	static LPDIRECT3DTEXTURE9 m_apBmpTex[2]; // バンプマップテクスチャ
	float m_fWaveaRate; // 波の係数
	float m_fWaveSpeed; // 波の速度
	SEA_TYPE m_seaType; // 海タイプ
};
#endif