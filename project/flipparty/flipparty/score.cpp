//===================================================
//
//    スコアクラスの処理[score.cpp]
//    Author:増澤 未来
//
//====================================================

//**********************************
//インクルード
//**********************************
#include "score.h"
#include "number.h"

//==============================
//静的メンバ変数宣言
//==============================
int CScore::m_nScore = 0;

//==================================
// コンストラクタ
//==================================
CScore::CScore()
{
	// ナンバーのクリア
	memset(m_apNumber, 0, sizeof(m_apNumber));
}

//==================================
// デストラクタ
//==================================
CScore::~CScore()
{
}

//==================================
// クリエイト
//==================================
CScore * CScore::Create(void)
{
	// メモリの確保
	CScore *pScore = new CScore;

	// 初期化処理
	pScore->Init();

	// オブジェクトタイプの設定
	pScore->SetPriority(OBJTYPE_UI);

	return pScore;
}

//==================================
// 初期化処理
//==================================
HRESULT CScore::Init(void)
{
	// 最大桁数分ループ
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(0,
			D3DXVECTOR3((float)(1000 + nCntDigit * 40), 50.0f, 0.0f),
			D3DXVECTOR3(20, 20, 0),
			D3DXCOLOR(0.8f, 0.3f, 0.8f, 1.0f));
	}
	// スコアの初期化
	m_nScore = 0;

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CScore::Uninit(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{
			m_apNumber[nCntDigit]->Uninit();
			delete m_apNumber[nCntDigit];
			m_apNumber[nCntDigit] = NULL;
		}
	}

	// 開放処理
	Release();
}

//==================================
// 更新処理
//==================================
void CScore::Update(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Update();

		m_apNumber[nCntDigit]->SetNumber((int)((m_nScore % (int)(powf(10.0f, (MAX_SCORE_DIGIT - nCntDigit)))) / (float)(powf(10, (MAX_SCORE_DIGIT - nCntDigit - 1)))));
	}
}

//==================================
// 描画処理
//==================================
void CScore::Draw(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Draw();
	}
}
