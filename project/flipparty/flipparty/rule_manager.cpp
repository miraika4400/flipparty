////////////////////////////////////////////////////
//
//    ゲームクラスの処理[game.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "rule_manager.h"
#include "polygon.h"
#include "rule_base.h"
#include "rule_flygame.h"
#include "remember_rule.h"
#include "flag_raicing_game_rule.h"

//=============================
// マクロ定義
//=============================
#define FADE_RATE 0.1f  // フェードレート

//=============================
// 静的メンバ変数宣言
//=============================

//=============================
// コンストラクタ
//=============================
CRuleManager::CRuleManager() : CScene(OBJTYPE_SYSTEM)
{
	// 変数のクリア
	m_pGameRule    = NULL;                       // ルール
	m_pFadePolygon = NULL;                       // フェード用ポリゴン
	m_ruleNext     = RULE_FLAG_RACING;           // ネクストルール
	m_fadeState    = FADE_NONE;                  // フェード状態
	m_polygonCol   = { 1.0f, 1.0f, 1.0f, 1.0f};  // カラー
}

//=============================
// デストラクタ
//=============================
CRuleManager::~CRuleManager()
{
}

//=============================
// クリエイト
//=============================
CRuleManager * CRuleManager::Create(void)
{
	// メモリの確保
	CRuleManager *pRuleManager = new CRuleManager;
	// 初期化
	pRuleManager->Init();
	return pRuleManager;
}

//=============================
// 初期化処理
//=============================
HRESULT CRuleManager::Init(void)
{
	// ルールクラスの初期化
	if (m_pGameRule != NULL)
	{
		m_pGameRule->Uninit();
		delete m_pGameRule;
		m_pGameRule = NULL;
	}

	// ポリゴンの生成
	m_pFadePolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), // 座標　
		                              D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), // サイズ
		                              m_polygonCol);                                          // 色

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CRuleManager::Uninit(void)
{
	// ルールクラスの破棄
	if (m_pGameRule != NULL)
	{
		m_pGameRule->Uninit();
		delete m_pGameRule;
		m_pGameRule = NULL;
	}

	// ポリゴンの破棄
	if (m_pFadePolygon != NULL)
	{
		m_pFadePolygon->Uninit();
		delete m_pFadePolygon;
		m_pFadePolygon = NULL;
	}

	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CRuleManager::Update(void)
{
	if (m_fadeState == FADE_NONE)
	{
		// ルールクラスの更新処理
		if (m_pGameRule != NULL)
		{
			m_pGameRule->Update();
		}
	}
	else
	{
		//フェードイン
		if (m_fadeState == FADE_IN)
		{
			m_polygonCol.a -= FADE_RATE;

			if (m_polygonCol.a <= 0.0f)
			{
				m_polygonCol.a = 0.0f;
				m_fadeState = FADE_NONE;
			}
		}

		//フェードアウト
		else if (m_fadeState == FADE_OUT)
		{
			m_polygonCol.a += FADE_RATE;
			if (m_polygonCol.a >= 1.0f)
			{
				m_polygonCol.a = 1.0f;
				m_fadeState = FADE_IN;

				// ルールクラスの初期化
				if (m_pGameRule != NULL)
				{
					m_pGameRule->Uninit();
					delete m_pGameRule;
					m_pGameRule = NULL;
				}

				// ルールの生成
				switch (m_ruleNext)
				{
				case RULE_FLAG_RACING: 
					// 旗揚げ
					m_pGameRule = CFlagRaicingGame_rule::Create();
					break;
				case RULE_FLY:
					// フライ
					m_pGameRule = CRuleFly::Create();
					break;
				case RULE_REMENBER:
					// 記憶
					m_pGameRule = CRememjber_rule::Create();
					break;
				default:
					break;
				}
				
			}
		}

		// カラーのセット
		m_pFadePolygon->SetColor(m_polygonCol);
	}
	
}

//=============================
// 描画処理
//=============================
void CRuleManager::Draw(void)
{
	m_pFadePolygon->Draw();
}

//=============================
//ルールのセット処理
//=============================
void CRuleManager::SetRule(RULE_TYPE ruleNext)
{
	m_fadeState = FADE_OUT;
	m_ruleNext = ruleNext;
}
