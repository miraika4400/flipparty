////////////////////////////////////////////////////
//
//    涙パーティクルクラスの処理[tears_paticle.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "tears_particle.h"
#include "billboard.h"
#include "resource_texture.h"

//**********************************
// 静的メンバ変数宣言
//**********************************

//**********************************
// マクロ定義
//**********************************
#define LIFE  60                                  // 寿命
#define MOVE_Y_DIST -2                           // 移動量Y軸の目標値
#define MOVE_Y_RATE 0.05f                         // 移動量Y軸の係数
#define SPEED_MIN 1                              // 速度の最小
#define SPEED_AMPLITUDE 10                        // 速度の振幅
#define SPEED_ADJUST 10.0f                        // スピード調整値
#define SIZE_MIN 3                               // サイズの最少
#define SIZE_AMPLITUDE 3                         // サイズの振幅

#define MOVE D3DXVECTOR3(0.8f ,4.0f ,0.0f )
#define SIZE D3DXVECTOR3(5.0f ,5.0f ,0.0f )
#define SIZE_DIST D3DXVECTOR3(0.0f ,0.0f ,0.0f )
#define SIZE_RATE 0.01f
#define ALPHA_DIST 0.0f
#define ALPHA_RATE 0.02f

//=============================
// コンストラクタ
//=============================
CTearsParticle::CTearsParticle():CScene(OBJTYPE_SYSTEM)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_nLife = LIFE;
	ZeroMemory(&m_apParticle, sizeof(m_apParticle));
}

//=============================
// デストラクタ
//=============================
CTearsParticle::~CTearsParticle()
{
}

//=============================
// クリエイト
//=============================
CTearsParticle * CTearsParticle::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CTearsParticle *pTears = new CTearsParticle;

	//　座標
	pTears->m_pos = pos;
	// 初期化
	pTears->Init();
	return pTears;
}

//=============================
// 初期化処理
//=============================
HRESULT CTearsParticle::Init(void)
{
	// 飛んでく速度
	float fSpeed = (float)((rand() % SPEED_AMPLITUDE + SPEED_MIN)) / SPEED_ADJUST;

	// 上記の情報から移動量の生成*Y軸は別で乱数生成
	m_move = MOVE;

	// サイズをランダムに設定
	float fSize = (float)(rand() % SIZE_AMPLITUDE + SIZE_MIN);
	D3DXVECTOR3 randSize;
	randSize.x = 4;
	randSize.y = 4;
	randSize.z = 0.0f;
	
	// 寿命
	m_nLife = LIFE;

	for (int nCntTears = 0; nCntTears < TEARS_NUM; nCntTears++)
	{
		// パーティクル生成
		m_apParticle[nCntTears] = CBillboard::Create(m_pos, randSize);
		// テクスチャ
		m_apParticle[nCntTears]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_TEARS));
	}
	
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CTearsParticle::Uninit(void)
{

	for (int nCntTears = 0; nCntTears < TEARS_NUM; nCntTears++)
	{
		if (m_apParticle[nCntTears] != NULL)
		{
			// ポリゴンの終了処理
			m_apParticle[nCntTears]->Uninit();

			// メモリの解放
			delete m_apParticle[nCntTears];
			m_apParticle[nCntTears] = NULL;
		}
	}

	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CTearsParticle::Update(void)
{

	// 移動量
	m_move.y += (MOVE_Y_DIST - m_move.y)*MOVE_Y_RATE;

	// パーティクルの座標に移動量を足す
	D3DXVECTOR3 pos = m_apParticle[0]->GetPos();
	pos += m_move;
	m_apParticle[0]->SetPos(pos);
	// 移動量のX軸の反転
	m_move.x *= -1;

	// パーティクルの座標に移動量を足す
	pos = m_apParticle[1]->GetPos();
	pos += m_move;
	m_apParticle[1]->SetPos(pos);
	// X軸を戻す
	m_move.x *= -1;

	// サイズ
	D3DXVECTOR3 size = m_apParticle[0]->GetSize();
	size += (SIZE_DIST - size)*SIZE_RATE;
	m_apParticle[0]->SetSize(size);
	m_apParticle[1]->SetSize(size);

	// カラー
	//D3DXCOLOR col = m_apParticle[0]->GetColor();
	//col.a += (ALPHA_DIST - col.a)*ALPHA_RATE;
	//m_apParticle[0]->SetColor(col);
	//m_apParticle[1]->SetColor(col);

	// 寿命
	m_nLife--;
	if (m_nLife <= 0)
	{
		// 消す
		Uninit();
	}
}


//=============================
// 描画処理
//=============================
void CTearsParticle::Draw(void)
{
	for (int nCntTears = 0; nCntTears < TEARS_NUM; nCntTears++)
	{
		if (m_apParticle[nCntTears] != NULL)
		{
			// ポリゴンの描画処理
			m_apParticle[nCntTears]->Draw();
		}
	}
}
