//=============================================================================
//
// 人数選択処理 [count_selection.cpp]
// Author : 増澤未来
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "count_selection.h"
#include "polygon.h"
#include "resource_texture.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"
#include "sound.h"
#include "joypad.h"

//*****************************
// マクロ定義
//*****************************
#define UI_SPACE 250.0f                                        // UIの間隔
#define UI_HEIGHT 500.0f                                       // UI位置の画面上の高さ
#define UI_SIZE D3DXVECTOR3( 100.0f, 100.0f, 0.0f)               // UIのサイズ
#define UI_COLOR_SELECT     D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f) // UI選択時のカラー
#define UI_COLOR_NOT_SELECT D3DXCOLOR( 0.6f, 0.6f, 0.6f, 1.0f) // UI非選択時のカラー

//*****************************
// 静的メンバ変数宣言
//*****************************
int CCountSelect::m_nPlayerNum = 0;
//=============================================================================
//コンストラクタ
//=============================================================================
CCountSelect::CCountSelect() :CScene(OBJTYPE_UI)
{
	// 変数のクリア
	ZeroMemory(&m_pPolygon, sizeof(m_pPolygon)); // UIポリゴン
	m_nSelectUi = 0;                             // 選んでいるUIのタイプ
	m_bMove = true;
}

//=============================================================================
//デストラクタ
//=============================================================================
CCountSelect::~CCountSelect()
{
}

//=============================================================================
//クラス生成
//=============================================================================
CCountSelect * CCountSelect::Create(void)
{
	// メモリの確保
	CCountSelect *pSelect;
	pSelect = new CCountSelect;

	// 初期化
	pSelect->Init();

	return pSelect;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CCountSelect::Init(void)
{

	SetPriority(OBJTYPE_UI);
	// 選んでいるUIのタイプの初期化
	m_nSelectUi = 0;
	
	// UI座標
	D3DXVECTOR3 pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - UI_SPACE, UI_HEIGHT, 0.0f);
	// UIポリゴンの生成
	for (int nCntUi = 0; nCntUi < SELECT_COUNT_MAX; nCntUi++)
	{
		if (m_pPolygon[nCntUi] == NULL)
		{
			m_pPolygon[nCntUi] = CPolygon::Create(pos, UI_SIZE);
			pos.x += UI_SPACE;
		}
	}
	// テクスチャの設定
	m_pPolygon[SELECT_2_PLAYER]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_COUNT_SELECT_2));
	m_pPolygon[SELECT_3_PLAYER]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_COUNT_SELECT_3));
	m_pPolygon[SELECT_4_PLAYER]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_COUNT_SELECT_4));

	m_bMove = true;

	return S_OK;
}


//=============================================================================
//終了処理
//=============================================================================
void CCountSelect::Uninit(void)
{
	// UIポリゴンの破棄
	for (int nCntUi = 0; nCntUi < SELECT_COUNT_MAX; nCntUi++)
	{
		if (m_pPolygon[nCntUi] != NULL)
		{
			m_pPolygon[nCntUi]->Uninit();
			delete m_pPolygon[nCntUi];
			m_pPolygon[nCntUi] = NULL;
		}
	}
	//オブジェクトの破棄
	Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CCountSelect::Update(void)
{
	// 選択処理
	SelectUi();
	// UIカラーの管理
	ManageUiColor();
}

//=============================================================================
//描画処理
//=============================================================================
void CCountSelect::Draw(void)
{
	// UIポリゴンの描画
	for (int nCntUi = 0; nCntUi < SELECT_COUNT_MAX; nCntUi++)
	{
		if (m_pPolygon[nCntUi] != NULL)
		{
			m_pPolygon[nCntUi]->Draw();
		}
	}
}

//=============================================================================
// UIの選択処理
//=============================================================================
void CCountSelect::SelectUi(void)
{
	

	DIJOYSTATE jy = CManager::GetJoypad()->GetStick(0);
	// キーボードによる選択処理
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RIGHT) || m_bMove && jy.lX >= 600)
	{// 右
		m_nSelectUi++;
		m_bMove = false;
		if (m_nSelectUi >= SELECT_COUNT_MAX)
		{
			m_nSelectUi = 0;
		}

		// SEの再生
		CManager::GetSound()->Play(CSound::LABEL_SE_CURSOR);
	}
	if(CManager::GetKeyboard()->GetKeyTrigger(DIK_LEFT) || m_bMove && jy.lX <= -600)
	{// 左
		m_nSelectUi--;
		m_bMove = false;
		if (m_nSelectUi < 0)
		{
			m_nSelectUi = SELECT_COUNT_MAX - 1;
		}

		// SEの再生
		CManager::GetSound()->Play(CSound::LABEL_SE_CURSOR);
	}

	// スティック用フラグの初期化
	if (jy.lX <= 500 && jy.lX >= -500)
	{
		m_bMove = true;
	}

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN)|| CManager::GetJoypad()->GetJoystickTrigger(3, 0))
	{
		m_nPlayerNum = m_nSelectUi + 2;
		CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);

		// SEの再生
		CManager::GetSound()->Play(CSound::LABEL_SE_ENTER);
	}
}

//=============================================================================
// UIカラーの管理処理
//=============================================================================
void CCountSelect::ManageUiColor(void)
{
	// 選択しているかいないかで色を変える
	for (int nCntUi = 0; nCntUi < SELECT_COUNT_MAX; nCntUi++)
	{
		if (m_pPolygon[nCntUi] != NULL)
		{
			if (m_nSelectUi == nCntUi)
			{// 選択時
				m_pPolygon[nCntUi]->SetColor(UI_COLOR_SELECT);
			}
			else
			{// 非選択時
				m_pPolygon[nCntUi]->SetColor(UI_COLOR_NOT_SELECT);
			}
		}
	}
}
