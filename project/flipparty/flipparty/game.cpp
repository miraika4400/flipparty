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
#include "bg.h"
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
CRuleBase   *CGame::m_pGameRule = NULL;   // ルールクラス

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

	// ルールクラスの初期化
	if (m_pGameRule != NULL)
	{
		m_pGameRule->Uninit();
		m_pGameRule = NULL;
	}

	// ルールクラスの生成
	if (m_pGameRule == NULL)
	{
		m_pGameRule = CRuleFly::Create();
	}

	// 背景の生成
	CBg::Create();

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

	// ルールクラスの破棄
	if (m_pGameRule != NULL)
	{
		m_pGameRule->Uninit();
		delete m_pGameRule;
		m_pGameRule = NULL;
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

	// ルールクラスの更新処理
	if (m_pGameRule != NULL)
	{
		m_pGameRule->Update();
	}

#ifdef _DEBUG
	// デバッグ用画面遷移コマンド
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F1))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}

#endif // _DEBUG

}

//=============================
// 描画処理
//=============================
void CGame::Draw(void)
{
    if (m_pGameRule != NULL)
    {
        m_pGameRule->Draw();
    }

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