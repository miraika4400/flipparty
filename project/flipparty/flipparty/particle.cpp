////////////////////////////////////////////////////
//
//    particleクラスの処理[particle.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "resource_texture.h"

//*****************************
// マクロ定義
//*****************************

//******************************
// 静的メンバ変数宣言
//*****************************

//******************************
// コンストラクタ
//******************************
CParticle::CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_type = PARTICLE_BOX;
}

//******************************
// デストラクタ
//******************************
CParticle::~CParticle()
{
}

//******************************
// クリエイト
//******************************
CParticle * CParticle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 size, const int nLife, const D3DCOLOR col,const PARTICLE_TYPE type)
{
	// メモリの確保
	CParticle *pParticle;
	pParticle = new CParticle;

	// タイプの設定
	pParticle->m_type = type;

	// 初期化
	pParticle->Init();

	// 各値の代入・セット
	pParticle->SetPos(pos);                  // 座標
	pParticle->m_move = move;                // 移動量
	pParticle->SetSize(size);                // サイズ
	pParticle->m_nLife = nLife;              // 寿命
	pParticle->SetColor(col);                // カラー
	pParticle->SetAngle((float)(rand() % 360));       // 回転角度をランダム
	pParticle->SetAddMode(true);             // 加算合成
	return pParticle;
}

//******************************
// 初期化処理
//******************************
HRESULT CParticle::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{
		return E_FAIL;
	}

	m_apTexture[PARTICLE_BOX] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_BOX);
	m_apTexture[PARTICLE_TEARS] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_TEARS);
	m_apTexture[PARTICLE_CIRCLE] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_CIRCLE);
	// テクスチャ割り当て
	BindTexture(m_apTexture[m_type]);

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CParticle::Uninit(void)
{
	CBillboard::Uninit();
}

//******************************
// 更新処理
//******************************
void CParticle::Update(void)
{
	// 移動
	SetPos(GetPos() + m_move);

	// 寿命
	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//******************************
// 描画処理
//******************************
void CParticle::Draw(void)
{
	CBillboard::Draw();
}
