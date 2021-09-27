////////////////////////////////////////////////////
//
//    雷クラスの処理[thunder.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//**********************************
// インクルード
//**********************************
#include "thunder.h"
#include "resource_texture.h"
#include "manager.h"
#include "renderer.h"
#include "rule_flygame.h"
#include "player_flygame.h"
#include "sound.h"

//**********************************
// 静的メンバ変数宣言
//**********************************

//**********************************
// マクロ定義
//**********************************
#define MAX_ANIMATION_X 3     // アニメーション数 横
#define MAX_ANIMATION_Y 4     // アニメーション数 縦
#define ANIMATION_INTERVAL 7  // アニメーション移行フレーム数
#define SIZE D3DXVECTOR3(100.0f,100.0f,0.0f)

//=============================
// コンストラクタ
//=============================
CThunder::CThunder() :CScene3d(OBJTYPE_PARTICLE)
{
	m_nCntAnim = 0;       // アニメーションカウント
	m_nAnimX = 0;         // アニメーションX軸
	m_nAnimY = 0;         // アニメーションY軸
	m_nPlayerNum = 0;
}

//=============================
// デストラクタ
//=============================
CThunder::~CThunder()
{
}

//=============================
// クリエイト
//=============================
CThunder * CThunder::Create(D3DXVECTOR3 pos , int nPlayerNum)
{
	// メモリの確保
	CThunder *pThunder = new CThunder;
	
	// プレイヤー番号
	pThunder->m_nPlayerNum = nPlayerNum;

	// 初期化
	pThunder->Init();

	// 位置の反映
	pThunder->SetPos(pos);

	return pThunder;
}

//=============================
// 初期化処理
//=============================
HRESULT CThunder::Init(void)
{
	// 初期化
	CScene3d::Init();

	// サイズの設定
	SetSize(SIZE);

	// アニメーション変数の初期化
	m_nCntAnim = 0;       // アニメーションカウント
	m_nAnimX = 0;         // アニメーションX軸
	m_nAnimY = 0;         // アニメーションY軸

	// テクスチャの
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_THUNDER_EFFECT));

	// UV座標の設定
	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / MAX_ANIMATION_X;
	float fv = 1.0f / MAX_ANIMATION_Y;

	uv[0] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY);
	uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
	uv[2] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY + fv);
	uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

	// UV座標セット
	SetTextureUV(uv);

	// SE
	CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_MISS) + m_nPlayerNum));
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CThunder::Uninit(void)
{
	CScene3d::Uninit();
}


//=============================
// 更新処理
//=============================
void CThunder::Update(void)
{
	// カウントを進める
	m_nCntAnim++;

	if (ANIMATION_INTERVAL < m_nCntAnim)
	{
		m_nCntAnim = 0;
		m_nAnimX++;
		if (m_nAnimX >= MAX_ANIMATION_X)
		{
			m_nAnimY++;
		}

		// UV座標の設定
		D3DXVECTOR2 uv[NUM_VERTEX];
		float fu = 1.0f / MAX_ANIMATION_X;
		float fv = 1.0f / MAX_ANIMATION_Y;

		uv[0] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY);
		uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
		uv[2] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY + fv);
		uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

		// UV座標セット
		SetTextureUV(uv);

		if (m_nAnimY >= MAX_ANIMATION_Y)
		{
			// スタン状態にする
			CRuleFly::GetPlayer(m_nPlayerNum)->SetState(CFlyGamePlayer::STATE_STAN);

			Uninit();
		}
	}
}

//=============================
// 描画処理
//=============================
void CThunder::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	DWORD lightEnable;
	pDevice->GetRenderState(D3DRS_LIGHTING, &lightEnable);
	// ライトオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	CScene3d::Draw();

	// ライトをもとに戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, lightEnable);
}
