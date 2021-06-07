//===================================================
//
//    フェードクラスの処理[fade.cpp]
//    Author:増澤 未来
//
//====================================================

//**********************************
//インクルード
//**********************************
#include "fade.h"
#include "polygon.h"

//**********************************
//マクロ定義
//**********************************
#define FADE_RATE 0.06f


//==================================
// コンストラクタ
//==================================
CFade::CFade()
{
	m_col = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_pPolygon = NULL;
	m_modeNext = CManager::MODE_GAME;
	m_fade = FADE_NONE;
}

//==================================
// デストラクタ
//==================================
CFade::~CFade()
{
}

//==================================
// クリエイト
//==================================
CFade * CFade::Create(void)
{
	// メモリの確保
	CFade *pFade = new CFade;
	// 初期化
	pFade->Init();

	return pFade;
}

//==================================
// 初期化処理
//==================================
HRESULT CFade::Init(void)
{
	// ポリゴンの生成
	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		m_col);

	return S_OK;
}


//==================================
// 終了処理
//==================================
void CFade::Uninit(void)
{
	// ポリゴンの終了処理
	m_pPolygon->Uninit();
	// メモリの解放
	delete m_pPolygon;
	m_pPolygon = NULL;
}

//==================================
// 更新処理
//==================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		//フェードイン
		if (m_fade == FADE_IN)
		{
			m_col.a -= FADE_RATE;

			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}

		//フェードアウト
		else if (m_fade == FADE_OUT)
		{
			m_col.a += FADE_RATE;
			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				m_fade = FADE_IN;

				// モードの切り替え
				CManager::SetMode(m_modeNext);
			}
		}

		// カラーのセット
		m_pPolygon->SetColor(m_col);
	}
}

//==================================
// 描画処理
//==================================
void CFade::Draw(void)
{
	// ポリゴンの描画
	m_pPolygon->Draw();
}


//==================================
// フェードのセット
//==================================
void CFade::SetFade(CManager::MODE mode)
{
	m_fade = FADE_OUT;
	m_modeNext = mode;
}
