////////////////////////////////////////////////////
//
//    ゲームクラスの処理[game.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "game.h"
#include "number.h"
#include "score.h" 
#include "mouse.h"
#include "camera_tps.h"
#include "camera_flygame.h"
#include "light.h"
#include "fade.h"
#include "keyboard.h"
#include "particle.h"
#include "time.h"
#include "joypad.h"
#include "player.h"
#include "captain.h"
#include "rule_base.h"
#include "rule_flygame.h"
#include "remember_rule.h"
#include "rule_manager.h"

//=============================
// マクロ定義
//=============================
#define RESULT_COUNT 250 // リザルトへの遷移カウント
#define INIT_POS_X 400   // キャラクター配置初期X位置
#define INIT_POS_Z 0     // キャラクター配置初期Y位置
#define SPACE_X 280      // キャラクター配置Xの間隔
#define SPACE_Z 140      // キャラクター配置Yの間隔
#define X_RESET_NUM 4    // キャラクター配置Xをリセットする間隔

//=============================
// 静的メンバ変数宣言
//=============================
CCamera *CGame::m_pCamera = {};       // カメラクラスポインタ
CLight  *CGame::m_pLight = NULL;      // ライトクラスポインタ
CRuleManager* CGame::m_pRuleManager = NULL;
//=============================
// コンストラクタ
//=============================
CGame::CGame()
{
	// 変数のクリア
}

//=============================
// デストラクタ
//=============================
CGame::~CGame()
{
}

//=============================
// クリエイト
//=============================
CGame * CGame::Create(void)
{
	// メモリの確保
	CGame *pGame = new CGame;
	// 初期化
	pGame->Init();
	return pGame;
}

//=============================
// 初期化処理
//=============================
HRESULT CGame::Init(void)
{
	// ポーズの初期化
	CManager::SetActivePause(false);

	// ライトクラスの生成
	m_pLight = new CLight;
	// ライトクラスの初期化
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// ルールクラスの生成
	if (m_pRuleManager == NULL)
	{
		m_pRuleManager = CRuleManager::Create();
		m_pRuleManager->SetRule(CRuleManager::RULE_FLY);
	}

#ifdef _DEBUG

	/////////////////////////////////////////////////////////////////
	//// 各ルールクラスで生成する者たちの仮生成
	//
	//// カメラクラスの生成
	//SetCamera(CTpsCamera::Create());
	//
	//// プレイヤーの生成
	//CPlayer::Create(D3DXVECTOR3(0.0f, -PLAYER_CENTER_HEIGHT, 0.0f), 0);
	//
	////
	/////////////////////////////////////////////////////////////////
	//CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CResourceModel::MODEL_CLOUD, D3DXVECTOR3(0.0000001f, 0.0000001f, 0.0000001f))->SetPriority(OBJTYPE_MAP);
#endif
	
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CGame::Uninit(void)
{
	// カメラクラスの解放処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		m_pCamera = NULL;
	}
	
	// ライト
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CGame::Update(void)
{

	// カメラクラス更新処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}


#ifdef _DEBUG
	// デバッグ用画面遷移コマンド
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F1))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}

	// デバッグ用ルール遷移コマンド

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_1))
	{
		ReConnection();
		m_pRuleManager->ReConnection();
		ReleaseAll();

		SetPriority(OBJTYPE_NONE);
		m_pRuleManager->SetPriority(OBJTYPE_SYSTEM);
		m_pRuleManager->SetRule(CRuleManager::RULE_FLAG_RACING);
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_2))
	{
		ReConnection();
		m_pRuleManager->ReConnection();
		ReleaseAll();

		SetPriority(OBJTYPE_NONE);
		m_pRuleManager->SetPriority(OBJTYPE_SYSTEM);
		m_pRuleManager->SetRule(CRuleManager::RULE_FLY);
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_3))
	{
		ReConnection();
		m_pRuleManager->ReConnection();
		ReleaseAll();

		SetPriority(OBJTYPE_NONE);
		m_pRuleManager->SetPriority(OBJTYPE_SYSTEM);
		m_pRuleManager->SetRule(CRuleManager::RULE_REMENBER);
	}

#endif // _DEBUG

}

//=============================
// 描画処理
//=============================
void CGame::Draw(void)
{
    // カメラのセット
    if (m_pCamera != NULL)
    {
        m_pCamera->SetCamera();
    }
}

//=============================
// カメラクラスのセット処理
//=============================
void CGame::SetCamera(CCamera * pCamera)
{
	// カメラクラスの解放処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		m_pCamera = NULL;
	}

	// セット
	m_pCamera = pCamera;
}