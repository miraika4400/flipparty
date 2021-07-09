////////////////////////////////////////////////////
//
//    ゲームクラスの処理[game.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "rank_ui.h"
#include "billboard.h"
#include "resource_texture.h"

//=============================
// マクロ定義
//=============================
#define UI_SIZE D3DXVECTOR3(30.0f,30.0f,0.0f)
#define MAX_ANIMATION_X 4      // アニメーション数 横
#define MAX_ANIMATION_Y 4      // アニメーション数 縦
#define ANIMATION_INTERVAL 10  // アニメーション移行フレーム数

//=============================
// 静的メンバ変数宣言
//=============================

//=============================
// コンストラクタ
//=============================
CRankUI::CRankUI() :CScene(OBJTYPE_MINIRESULT)
{
	// 変数のクリア
	m_pBillboard = NULL;  // ビルボードポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 座標
	m_nRank = 0;          // 順位
	m_nCntAnim = 0;       // アニメーションカウント
	m_nAnimX = 0;         // アニメーションX軸
}

//=============================
// デストラクタ
//=============================
CRankUI::~CRankUI()
{
}

//=============================
// クリエイト
//=============================
CRankUI * CRankUI::Create(D3DXVECTOR3 pos, int nRank)
{
	// メモリの確保
	CRankUI *pRankUi = new CRankUI;

	// 引数の代入
	pRankUi->m_pos = pos; 
	pRankUi->m_nRank = nRank;

	// 初期化
	pRankUi->Init();

	return pRankUi;
}

//=============================
// 初期化処理
//=============================
HRESULT CRankUI::Init(void)
{
	m_pBillboard = CBillboard::Create(m_pos, UI_SIZE);
	m_nCntAnim = 0;       // アニメーションカウント
	m_nAnimX = 0;         // アニメーションX軸

	// テクスチャの設定
	m_pBillboard->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_RANK));
	
	// UV座標の設定
	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / MAX_ANIMATION_X;
	float fv = 1.0f / MAX_ANIMATION_Y;

	uv[0] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nRank);
	uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nRank);
	uv[2] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nRank + fv);
	uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nRank + fv);

	// UV座標セット
	m_pBillboard->SetTextureUV(uv);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CRankUI::Uninit(void)
{
	if (m_pBillboard != NULL)
	{
		m_pBillboard->Uninit();
		delete m_pBillboard;
		m_pBillboard = NULL;
	}

	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CRankUI::Update(void)
{
	m_nCntAnim++;

	if (ANIMATION_INTERVAL < m_nCntAnim )
	{
		m_nCntAnim = 0;
		m_nAnimX++;
		if (m_nAnimX >= 2)
		{
			m_nAnimX = 0;
		}

		// UV座標の設定
		D3DXVECTOR2 uv[NUM_VERTEX];
		float fu = 1.0f / MAX_ANIMATION_X;
		float fv = 1.0f / MAX_ANIMATION_Y;

		uv[0] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nRank);
		uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nRank);
		uv[2] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nRank + fv);
		uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nRank + fv);

		// UV座標セット
		m_pBillboard->SetTextureUV(uv);
	}
}

//=============================
// 描画処理
//=============================
void CRankUI::Draw(void)
{
	if (m_pBillboard!=NULL)
	{
		m_pBillboard->Draw();
	}
}
