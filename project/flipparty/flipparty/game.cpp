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
#include "light.h"
#include "fade.h"
#include "keyboard.h"
#include "particle.h"
#include "time.h"
#include "joypad.h"
#include "player.h"
#include "captain.h"
#include "rule_base.h"

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
	// カーソルを消す
	ShowCursor(FALSE);

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

	// カメラクラスの生成
	if (m_pCamera == NULL)
	{
		m_pCamera = CTpsCamera::Create();
	}

	// ルールクラスの初期化
	if (m_pGameRule != NULL)
	{
		m_pGameRule->Uninit();
		m_pGameRule = NULL;
	}

	CBg::Create();
#ifdef _DEBUG
	CPlayer::Create(D3DXVECTOR3(0.0f, -35.0f, 0.0f), 0);
	//CModel::Create(D3DXVECTOR3(0.0f, 35.0f, -20.0f), CResourceModel::MODEL_GENERAL_SPHERE,D3DXVECTOR3(10.0f,10.0f,10.0f));
	
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
	// カメラのセット
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

