//=============================================================================
//
// particleヘッダ [particle.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "billboard.h"

//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CParticle : public CBillboard
{
public:
	//============
	// 状態列挙
	//============
	// パーティクルタイプ
	typedef enum
	{
		PARTICLE_BOX = 0, // 四角
		PARTICLE_TEARS,   // 涙
		PARTICLE_CIRCLE,  // 丸
		PARTICLE_MAX,     // タイプの最大数
	}PARTICLE_TYPE;

	//============
	//メンバ関数
	//============
	CParticle();
	~CParticle();

	// static
	static CParticle *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 size, const int nLife,
		const D3DCOLOR col, const PARTICLE_TYPE type = PARTICLE_BOX); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	// 移動量の取得・セット
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:
	//============
	// メンバ変数
	//============
	LPDIRECT3DTEXTURE9 m_apTexture[PARTICLE_MAX]; // テクスチャ
	D3DXVECTOR3   m_move;  // 移動量
	int           m_nLife; // 寿命
	PARTICLE_TYPE m_type;  // パーティクルの種類
};

#endif