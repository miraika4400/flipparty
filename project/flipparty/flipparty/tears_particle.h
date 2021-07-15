//=============================================================================
//
// tears_particleヘッダ [tears_particle.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TEARS_PARTICLE_H_
#define _TEARS_PARTICLE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// 前方宣言
//=============================
class CBillboard;

//=============================
// マクロ定義
//=============================
#define TEARS_NUM 2  // 一度の生成するの涙の量(左右に一つずつ生成する)

//*****************************
//クラス定義
//*****************************

//涙パーティクルクラス
class CTearsParticle: public CScene
{
public:
	//============
	// メンバ関数
	//============
	CTearsParticle();
	~CTearsParticle();

	static CTearsParticle *Create(D3DXVECTOR3 pos); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	//============
	// メンバ変数
	//============
	D3DXVECTOR3 m_pos;       // 座標
	D3DXVECTOR3 m_move;      // 移動量
	int m_nLife;             // 寿命
	CBillboard * m_apParticle[TEARS_NUM]; // パーティクルクラス
};

#endif