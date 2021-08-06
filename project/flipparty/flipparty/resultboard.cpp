////////////////////////////////////////////////////
//
//    リザルトクラスの処理[resultboard.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "resultboard.h"
#include "polygon.h"
#include "resource_texture.h"
#include "result.h"
#include "number.h"

//**********************************
// マクロ定義
//**********************************
#define SIZE D3DXVECTOR3(320.0f/2,720.0f/2,0.0f)           // ボードサイズ
#define COLOR_1P D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f)         // ボードカラー1p
#define COLOR_2P D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f)         // ボードカラー2p
#define COLOR_3P D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f)         // ボードカラー3p
#define COLOR_4P D3DXCOLOR(1.5f, 1.5f, 0.5f, 1.0f)         // ボードカラー4p

#define PLAYER_NUMBER_POS_Y 100.0f                       // プレイヤーナンバーY座標
#define SIZE_PLAYER_NUMBER D3DXVECTOR3(80.0f,70.0f,0.0f) // プレイヤーナンバーサイズ

#define SIZE_GAME_ICON D3DXVECTOR3(40.0f,40.0f,0.0f) // ミニゲームアイコンのサイズ
#define GAME_ICON_POS_X -78    // ミニゲームアイコンのX座標
#define GAME_ICON_POS_Y 230.0f // ミニゲームアイコンのY座標
#define GAME_ICON_SPACE 120.0f  // ミニゲームアイコンの間隔

#define SIZE_GAME_RANK D3DXVECTOR3(60.0f,60.0f,0.0f) // 順位ポリゴンのサイズ
#define RANK_POS_X 50                                // 順位ポリゴンX座標
#define RANK_TEX_ANIM_MAX_X 4  // 順位テクスチャ分割数*横
#define RANK_TEX_ANIM_MAX_Y 4  // 順位テクスチャ分割数*縦

#define SIZE_SCORE D3DXVECTOR3 (45.0f ,45.0f ,0.0f ) // スコアのサイズ
#define SCORE_POS_Y 620.0f                           // スコアY座標
#define SCORE_SPACE 80.0f                           // スコア各桁の間隔

//**********************************
// 静的メンバ変数宣言
//**********************************

//=============================
// コンストラクタ
//=============================
CResultBoard::CResultBoard():CScene(OBJTYPE_UI)
{
	// 変数のクリア
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);  // 座標
	m_nPlayerNum = 0;                     // プレイヤー番号
	ZeroMemory(&m_apScoreNumber, sizeof(m_apScoreNumber));   // スコアの数字ポリゴン
	m_pBack = NULL;                                          // 背景
	m_pPlayerNumPolygon = NULL;                              // プレイヤー番号ポリゴン
	ZeroMemory(&m_apMinigameIcon, sizeof(m_apMinigameIcon)); // ミニゲームのアイコン
}

//=============================
// デストラクタ
//=============================
CResultBoard::~CResultBoard()
{
}

//=============================
// クリエイト
//=============================
CResultBoard * CResultBoard::Create(int nPlayerNum, D3DXVECTOR3 pos)
{
	// メモリの確保
	CResultBoard *pResult = new CResultBoard;

	// プレイヤ－番号
	pResult->m_nPlayerNum = nPlayerNum;
	// 座標
	pResult->m_pos = pos;
	// 初期化
	pResult->Init();

	return pResult;
}

//=============================
// 初期化処理
//=============================
HRESULT CResultBoard::Init(void)
{
	// 背景の生成
	m_pBack = CPolygon::Create(m_pos, SIZE, ReturnBackColor());
	m_pBack->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_RESULTBOARD_BACK));

	// プレイヤー番号の生成
	CreatePlayerNumber();

	// ミニゲームアイコンの生絵師
	CreateGameIcon();

	// ミニゲーム順位の生成
	CreateGameRank();

	// スコアの生成
	CreateScore();
	
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CResultBoard::Uninit(void)
{
	// 背景の解放
	if (m_pBack != NULL)
	{
		m_pBack->Uninit();
		delete m_pBack;
		m_pBack = NULL;
	}
	// プレイヤーナンバーの解放
	if (m_pPlayerNumPolygon != NULL)
	{
		m_pPlayerNumPolygon->Uninit();
		delete m_pPlayerNumPolygon;
		m_pPlayerNumPolygon = NULL;
	}

	for (int nCntGame = 0; nCntGame < CRuleManager::RULE_MAX; nCntGame++)
	{
		// ミニゲームアイコンの解放
		if (m_apMinigameIcon[nCntGame] != NULL)
		{
			m_apMinigameIcon[nCntGame]->Uninit();
			delete m_apMinigameIcon[nCntGame];
			m_apMinigameIcon[nCntGame] = NULL;
		}

		// ミニゲーム順位の解放
		if (m_apMinigameRank[nCntGame] != NULL)
		{
			m_apMinigameRank[nCntGame]->Uninit();
			delete m_apMinigameRank[nCntGame];
			m_apMinigameRank[nCntGame] = NULL;
		}
	}

	// スコアの解放
	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		if (m_apScoreNumber[nCntDigit] != NULL)
		{
			m_apScoreNumber[nCntDigit]->Uninit();
			delete m_apScoreNumber[nCntDigit];
			m_apScoreNumber[nCntDigit] = NULL;
		}
	}

	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CResultBoard::Update(void)
{
}

//=============================
// 描画処理
//=============================
void CResultBoard::Draw(void)
{
	// 背景描画
	if (m_pBack != NULL)
	{
		m_pBack->Draw();
	}

	// プレイヤーナンバーの描画
	if (m_pPlayerNumPolygon != NULL)
	{
		m_pPlayerNumPolygon->Draw();
	}

	for (int nCntGame = 0; nCntGame < CRuleManager::RULE_MAX; nCntGame++)
	{
		// ミニゲームアイコンの描画
		if (m_apMinigameIcon[nCntGame] != NULL)
		{
			m_apMinigameIcon[nCntGame]->Draw();
		}

		// ミニゲーム順位の描画
		if (m_apMinigameRank[nCntGame] != NULL)
		{
			m_apMinigameRank[nCntGame]->Draw();
		}
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
// プレイヤーナンバーに応じたカラー
//=============================
D3DXCOLOR CResultBoard::ReturnBackColor(void)
{
	switch (m_nPlayerNum)
	{
	case 0:

		return COLOR_1P;
		break;
	case 1:
		
		return COLOR_2P;
		break;
	case 2:
		
		return COLOR_3P;
		break;
	case 3:

		return COLOR_4P;
		break;
	default:
		return D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		break;
	}
	
}

//=============================
// プレイヤー番号の生成
//=============================
void CResultBoard::CreatePlayerNumber(void)
{
	// プレイヤーナンバーの生成
	m_pPlayerNumPolygon = CPolygon::Create(D3DXVECTOR3(m_pos.x, PLAYER_NUMBER_POS_Y, 0.0f), SIZE_PLAYER_NUMBER);
	// テクスチャの設定
	switch (m_nPlayerNum)
	{
	case 0:
		m_pPlayerNumPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_1P));
		break;
	case 1:
		m_pPlayerNumPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_2P));
		break;
	case 2:
		m_pPlayerNumPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_3P));
		break;
	case 3:
		m_pPlayerNumPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_4P));
		break;
	default:
		break;
	}
}

//=============================
// ミニゲームアイコンの生成
//=============================
void CResultBoard::CreateGameIcon(void)
{
	// アイコンの生成
	for (int nCntGame = 0; nCntGame < CRuleManager::RULE_MAX; nCntGame++)
	{
		m_apMinigameIcon[nCntGame] = CPolygon::Create(D3DXVECTOR3(m_pos.x + GAME_ICON_POS_X, GAME_ICON_POS_Y + (GAME_ICON_SPACE*nCntGame),0.0f) , SIZE_GAME_ICON);
	}

	// テクスチャの割り当て
	m_apMinigameIcon[CRuleManager::RULE_FLAG_RACING]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_ICON_FLAGRACING));
	m_apMinigameIcon[CRuleManager::RULE_FLY]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_ICON_FLY));
	m_apMinigameIcon[CRuleManager::RULE_REMENBER]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_ICON_REMENBER));
}

//=============================
// ゲーム順位ポリゴンの生成
//=============================
void CResultBoard::CreateGameRank(void)
{
	// アイコンの生成
	for (int nCntGame = 0; nCntGame < CRuleManager::RULE_MAX; nCntGame++)
	{
		m_apMinigameRank[nCntGame] = CPolygon::Create(D3DXVECTOR3(m_pos.x + RANK_POS_X, GAME_ICON_POS_Y + (GAME_ICON_SPACE*nCntGame), 0.0f), SIZE_GAME_RANK);
		m_apMinigameRank[nCntGame]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_RANK));
		
		int nRank = CResult::GetResultPoint(m_nPlayerNum).nMiniGameRank[nCntGame];
		// UVの設定
		D3DXVECTOR2 uv[NUM_VERTEX];
		float fu = 1.0f / RANK_TEX_ANIM_MAX_X;
		float fv = 1.0f / RANK_TEX_ANIM_MAX_X;

		uv[0] = D3DXVECTOR2(fu*0.0f     , fv*nRank);
		uv[1] = D3DXVECTOR2(fu*0.0f + fu, fv*nRank);
		uv[2] = D3DXVECTOR2(fu*0.0f     , fv*nRank + fv);
		uv[3] = D3DXVECTOR2(fu*0.0f + fu, fv*nRank + fv);

		// UV座標セット
		m_apMinigameRank[nCntGame]->SetTextureUV(uv);
	}
}

//=============================
// スコアポリゴンの生成
//=============================
void CResultBoard::CreateScore(void)
{
	float posX = 0 - (SCORE_SPACE*(POINT_MAX_DIGIT - 1)) / 2;
	int nScore = nScore = CResult::GetResultPoint(m_nPlayerNum).nPoint;

	for (int nCntDigit = 0; nCntDigit < POINT_MAX_DIGIT; nCntDigit++)
	{
		m_apScoreNumber[nCntDigit] = CNumber::Create(0, D3DXVECTOR3(m_pos.x + posX, SCORE_POS_Y, 0.0f), SIZE_SCORE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		posX += SCORE_SPACE;

		m_apScoreNumber[nCntDigit]->SetNumber((int)((nScore % (int)(powf(10.0f, (POINT_MAX_DIGIT - nCntDigit)))) / (float)(powf(10, (POINT_MAX_DIGIT - nCntDigit - 1)))));
	}
}
