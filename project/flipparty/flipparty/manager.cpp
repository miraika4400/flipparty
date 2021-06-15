

//=============================
// インクルード
//=============================
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "game.h"
#include "scene.h"
#include "input.h"
#include "keyboard.h"
#include "joypad.h"
#include "mouse.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "game.h"
#include "bg.h"
#include "number.h"
#include "score.h" 
#include "mouse.h"
#include "fade.h"
#include "particle.h"
#include "tutorial.h"
#include "pause.h"
#include "debug_log.h"
#include "model.h"
#include "resource_texture.h"
#include "resource_model.h"
#include "player.h"
#include "Captain.h"

//=============================
// 静的メンバ変数宣言
//=============================
CManager::MODE   CManager::m_mode = MODE_TITLE;      // ゲームモード
CRenderer       *CManager::m_pRenderer = NULL;       // レンダラーポインタ
CInputKeyboard  *CManager::m_pInputKeyboard = NULL;  // キーボード
CInputJoypad    *CManager::m_pJoypad = NULL;         // ジョイパッド
CInputMouse     *CManager::m_pInputMouse = NULL;     //　マウス
CSound          *CManager::m_pSound = NULL;          // サウンド
CGame           *CManager::m_pGame = NULL;           // ゲーム
CTitle          *CManager::m_pTitle = NULL;          // タイトル
CResult         *CManager::m_pResult = NULL;         // リザルト
CFade           *CManager::m_pFade = NULL;           // フェード
CTutorial       *CManager::m_pTutorial = NULL;       // チュートリアル
CPause          *CManager::m_pPause = NULL;            // ポーズポインタ
bool             CManager::m_bPause = false;         // ポーズフラグ

//=============================
// コンストラクタ
//=============================
CManager::CManager()
{
	
}

//=============================
// デストラクタ
//=============================
CManager::~CManager()
{
}

//=============================
// 初期化処理
//=============================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	
	// メモリの確保・初期化

	// キーボード
	m_pInputKeyboard = new CInputKeyboard;
	// キーボード初期化
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ジョイパッド
	m_pJoypad = new CInputJoypad;
	// ジョイパッドの初期化
	if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// マウス
	m_pInputMouse = new CInputMouse;
	// マウス初期化
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// レンダラー
	m_pRenderer = new CRenderer;
	// レンダラークラスの初期化
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return E_FAIL;
	}

	// サウンド
	m_pSound = new CSound;
	// サウンドクラスの初期化
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
	}

	// デバッグログ
	CDebugLog::Init();
	
	// フェードの生成
	m_pFade = CFade::Create();
	m_pFade->SetFade(m_mode);

	// テクスチャクラスの生成
	CResourceTexture::Create();
	// モデルリソースクラスの生成
	CResourceModel::Create();

	// テクスチャ・モデルの読み込み
	CPause::Load();    // ポーズ
	CPlayer::Load();   // プレイヤー
	CCaptain::Load();  // キャプテン

	// ポーズ状態の時
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CManager::Uninit(void)
{
	// 開放処理
	CScene::ReleaseAll();

	// テクスチャクラスの生成
	CResourceTexture::Release();
	// モデルリソースクラスの生成
	CResourceModel::Release();

	// テクスチャのアンロード
	CPause::Unload();    // ポーズ
	CPlayer::Unload();   // プレイヤー
	CCaptain::Unload();  // キャプテン

	if (m_pSound != NULL)
	{
		// 終了処理
		m_pSound->Uninit();
		// メモリの解放
		delete m_pSound;
		m_pSound = NULL;
	}

	if (m_pRenderer != NULL)
	{
		// 終了処理
		m_pRenderer->Uninit();
		// メモリの解放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{
		// 終了処理
		m_pInputKeyboard->Uninit();
		// メモリの解放
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	if (m_pJoypad != NULL)
	{
		// 終了処理
		m_pJoypad->Uninit();
		// メモリの解放
		delete m_pJoypad;
		m_pJoypad = NULL;
	}

	if (m_pInputMouse != NULL)
	{
		// 終了処理
		m_pInputMouse->Uninit();
		// メモリの解放
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	if (m_pFade != NULL)
	{
		// 終了処理
		m_pFade->Uninit();
		// メモリの解放
		delete m_pFade;
		m_pFade = NULL;
	}
}


//=============================
// 更新処理
//=============================
void CManager::Update(void)
{
	// ジョイパッドクラスの更新処理
	if (m_pJoypad != NULL)
	{
		m_pJoypad->Update();
	}
	// キーボードクラスの更新処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// マウスクラスの更新処理
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Update();
	}

	// レンダラークラスの更新処理
	if (m_pRenderer != NULL)
	{
		if (m_mode == MODE_GAME)
		{// モードゲームのときポーズ画面の処理

			if (m_pInputKeyboard->GetKeyTrigger(DIK_TAB) || m_pJoypad->GetJoystickTrigger(11, 0))
			{// TAB

				if (m_pPause == NULL)
				{
					// 生成
					m_pPause = CPause::Create();
				}
				// ポーズの切り替え
				m_bPause ^= true;
			}
			if (!m_bPause)
			{// ポーズじゃないとき

				if (m_pPause != NULL)
				{
					m_pPause->Uninit();
					delete m_pPause;
					m_pPause = NULL;
				}
				m_pRenderer->Update();
			}
			else
			{// ポーズ状態
				if (m_pPause != NULL)
				{
					// ポーズの更新処理
					m_pPause->Update();
				}
			}
		}
		else
		{
			m_pRenderer->Update();
		}
		
	}

	// フェードクラスの更新処理
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

}

//=============================
// 描画処理
//=============================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================
// セットモード
//=============================
void CManager::SetMode(MODE mode)
{

	switch (m_mode)
	{
	case MODE_TITLE:
		// NULLクリア
		m_pTitle = NULL;
		break;
	case MODE_TUTORIAL:
		// NULLクリア
		m_pTutorial = NULL;
		// タイトルBGM停止
		m_pSound->Stop(CSound::LABEL_BGM_TITLE);
		break;
	case MODE_GAME:
		// NULLクリア
		m_pGame = NULL;
		// ゲームBGM停止
		m_pSound->Stop(CSound::LABEL_BGM_GAME);
		break;

	case MODE_RESULT:
		// NULLクリア
		m_pResult = NULL;
		// リザルトBGM停止
		//m_pSound->Stop(CSound::LABEL_BGM_RESULT);
		break;

	default:
		break;
	}

	m_mode = mode;
	// 開放処理
	CScene::ReleaseAll();

	switch (m_mode)
	{
	case MODE_TITLE:
		// タイトル生成
		m_pTitle = CTitle::Create();
		// タイトルBGM再生
		//m_pSound->Play(CSound::LABEL_BGM_TITLE);
		break;
	case MODE_TUTORIAL:
		// チュートリアル生成
		m_pTutorial = CTutorial::Create();
		break;
	case MODE_GAME:
		// ゲーム生成
		m_pGame = CGame::Create();
		//// ゲームBGM再生
		//m_pSound->Play(CSound::LABEL_BGM_GAME);
		break;

	case MODE_RESULT:
		// リザルト生成
		m_pResult = CResult::Create();
		// リザルトBGM再生
		//m_pSound->Play(CSound::LABEL_BGM_RESULT);
		break;

	default:
		break;
	}
}
