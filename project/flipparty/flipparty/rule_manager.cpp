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
#include "fade.h"
#include "game.h"
#include "mini_tutorial.h"
#include "sound.h"

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
    m_MiniTutorial = nullptr;
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

	// ルールネクスト
	//m_ruleNext = RULE_FLAG_RACING;           // ネクストルール
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

        if (m_MiniTutorial)
        {
            //チュートリアル終了フラグがたったら
            if (m_MiniTutorial->GetIsTutorialEnd())
            {
                // チュートリアル破棄
                m_MiniTutorial->Uninit();
                m_MiniTutorial = nullptr;

				// BGM停止
				CManager::GetSound()->Stop(CSound::LABEL_BGM_TUTORIAL);
				// SEの再生
				CManager::GetSound()->Play(CSound::LABEL_SE_ENTER);

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

				// ルールクラスの初期化
				if (m_pGameRule != NULL)
				{
					m_pGameRule->Uninit();
					delete m_pGameRule;
					m_pGameRule = NULL;
				}

                // 次のルールに合わせてチュートリアル生成
                switch (m_ruleNext)
                {
                case RULE_FLAG_RACING:
                    // 旗揚げ
                    m_MiniTutorial = CMini_Tutorial::Create(CResourceTexture::TEXTURE_TUTORIAL_FLAG);
                    break;
                case RULE_FLY:
                    // フライ
                    m_MiniTutorial = CMini_Tutorial::Create(CResourceTexture::TEXTURE_TUTORIAL_FRY);
                    break;
                case RULE_REMENBER:
                    // 記憶
                    m_MiniTutorial = CMini_Tutorial::Create(CResourceTexture::TEXTURE_TUTORIAL_REMEMBER);
                    break;
                default:
                    break;
                }

				// BGM再生
				CManager::GetSound()->Play(CSound::LABEL_BGM_TUTORIAL);
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
    if (m_pGameRule != NULL)
    {
        m_pGameRule->Draw();
    }

	m_pFadePolygon->Draw();
}

//=============================
//ルールのセット処理
//=============================
void CRuleManager::SetRule(RULE_TYPE ruleNext)
{
	ReConnection();
	CManager::GetGame()->ReConnection();
	CManager::SetCamera(NULL);
	ReleaseAll();

	SetPriority(OBJTYPE_SYSTEM);
	if (CManager::GetGame() != NULL) CManager::GetGame()->SetPriority(OBJTYPE_NONE);

	m_fadeState = FADE_OUT;
	m_ruleNext = ruleNext;
}

//=============================
// ルール遷移
//=============================
void CRuleManager::TransitionRule(void)
{
	switch (m_ruleNext)
	{
	case RULE_FLAG_RACING:// 旗揚げ
		SetRule(RULE_FLY);
		break;
	case RULE_FLY:           // フライ
		SetRule(RULE_REMENBER);
		break;
	case RULE_REMENBER:       // 記憶
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);

	default:
		break;
	}
}
