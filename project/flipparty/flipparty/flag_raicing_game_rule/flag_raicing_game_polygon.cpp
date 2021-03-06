////////////////////////////////////////////////////
//
//    リザルトクラスの処理[resultboard.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "flag_raicing_game_polygon.h"
#include "polygon.h"
#include "resource_texture.h"
#include "result.h"
#include "number.h"
#include "flag_raicing_game_rule.h"
#include "player_flag_raicing.h"

//**********************************
// マクロ定義
//**********************************
#define SIZE_BACK D3DXVECTOR3(60.0f,30.0f,0.0f)           // ボードサイズ

#define SIZE_SCORE D3DXVECTOR3 (20.0f ,20.0f ,0.0f ) // スコアのサイズ
#define SCORE_POS_Y m_pos.y                           // スコアY座標
#define SCORE_SPACE 40.0f                           // スコア各桁の間隔
#define COLOR_1P D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)         // ボードカラー1p
#define COLOR_2P D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f)         // ボードカラー2p
#define COLOR_3P D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f)         // ボードカラー3p
#define COLOR_4P D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f)         // ボードカラー4p

//**********************************
// 静的メンバ変数宣言
//**********************************

//=============================
// コンストラクタ
//=============================
CFlagRaicingGamePolygon::CFlagRaicingGamePolygon()
{
	// 変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 座標
	m_nPlayerNum = 0;                     // プレイヤー番号
	ZeroMemory(&m_apScoreNumber, sizeof(m_apScoreNumber));   // スコアの数字ポリゴン
	m_pBack = NULL;                                          // 背景
}

//=============================
// デストラクタ
//=============================
CFlagRaicingGamePolygon::~CFlagRaicingGamePolygon()
{
}

//=============================
// クリエイト
//=============================
CFlagRaicingGamePolygon * CFlagRaicingGamePolygon::Create(int nPlayerNum, D3DXVECTOR3 pos)
{
	// メモリの確保
	CFlagRaicingGamePolygon *pPolygon = new CFlagRaicingGamePolygon;

	// プレイヤ−番号
	pPolygon->m_nPlayerNum = nPlayerNum;
	// 座標
	pPolygon->m_pos = pos;
	// 初期化
	pPolygon->Init();

	return pPolygon;
}

//=============================
// 初期化処理
//=============================
HRESULT CFlagRaicingGamePolygon::Init(void)
{
	// 背景の生成
	m_pBack = CPolygon::Create(m_pos, SIZE_BACK, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//背景のテクスチャ設定
	m_pBack->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_POINT_BACK));

	// スコアの生成
	CreateScore();

	switch (m_nPlayerNum)
	{
	case 0:
		m_pBack->SetColor(COLOR_1P);
		break;
	case 1:
		m_pBack->SetColor(COLOR_2P);
		break;
	case 2:
		m_pBack->SetColor(COLOR_3P);
		break;
	case 3:
		m_pBack->SetColor(COLOR_4P);
		break;
	default:
		break;
	}

	SetPriority(CScene::OBJTYPE_UI);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CFlagRaicingGamePolygon::Uninit(void)
{
	// 背景の解放
	if (m_pBack != NULL)
	{
		//終了処理
		m_pBack->Uninit();

		//メモリ削除
		delete m_pBack;

		//メモリクリア
		m_pBack = NULL;
	}

	// スコアの解放
	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		if (m_apScoreNumber[nCntDigit] != NULL)
		{
			//終了処理
			m_apScoreNumber[nCntDigit]->Uninit();

			//メモリ削除
			delete m_apScoreNumber[nCntDigit];

			//メモリクリア
			m_apScoreNumber[nCntDigit] = NULL;
		}
	}

	Release();
}

//=============================
// 更新処理
//=============================
void CFlagRaicingGamePolygon::Update(void)
{
	//プレイヤーのポイントを取得
	int nScore = CFlagRaicingGame_rule::GetPlayer(m_nPlayerNum)->GetPoint();

	//取得した数値をナンバークラスへ設定
	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		m_apScoreNumber[nCntDigit]->SetNumber((int)((nScore % (int)(powf(10.0f, (POINT_MAX_DIGIT - nCntDigit)))) / (float)(powf(10, (POINT_MAX_DIGIT - nCntDigit - 1)))));
	}
}

//=============================
// 描画処理
//=============================
void CFlagRaicingGamePolygon::Draw(void)
{
	// 背景描画
	if (m_pBack != NULL)
	{
		m_pBack->Draw();
	}

	// スコアの描画
	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		if (m_apScoreNumber[nCntDigit] != NULL)
		{
			m_apScoreNumber[nCntDigit]->Draw();
		}
	}
}

//=============================
// スコアポリゴンの生成
//=============================
void CFlagRaicingGamePolygon::CreateScore(void)
{
	float posX = 0 - (SCORE_SPACE * (POINT_MAX_DIGIT - 1)) / 2;
	int nScore = CFlagRaicingGame_rule::GetPlayer(m_nPlayerNum)->GetPoint();

	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		m_apScoreNumber[nCntDigit] = CNumber::Create(
			0, 
			D3DXVECTOR3(m_pos.x + posX, SCORE_POS_Y, 0.0f), 
			SIZE_SCORE, 
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		posX += SCORE_SPACE;

		m_apScoreNumber[nCntDigit]->SetNumber((int)((nScore % (int)(powf(10.0f, (POINT_MAX_DIGIT - nCntDigit)))) / (float)(powf(10, (POINT_MAX_DIGIT - nCntDigit - 1)))));
	}
}
