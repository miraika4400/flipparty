////////////////////////////////////////////////////
//
//    タイトルクラスの処理[title.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "sound.h"
#include "resource_texture.h"
#include "count_selection.h"
#include "camera_base.h"
#include "sea.h"
#include "bg.h"
#include "iceberg.h"
#include "stage.h"
#include "rule_base.h"

//**********************************
// 静的メンバ変数宣言
//**********************************

//**********************************
// マクロ定義
//**********************************
#define OBJ_BACE_POS_Y 2000.0f
#define STAGE_SPACE 150.0f

//=============================
// コンストラクタ
//=============================
CTitle::CTitle()
{
	m_pPolygon = NULL;
}

//=============================
// デストラクタ
//=============================
CTitle::~CTitle()
{
}

//=============================
// クリエイト
//=============================
CTitle * CTitle::Create(void)
{
	// メモリの確保
	CTitle *pTitle = new CTitle;
	// 初期化
	pTitle->Init();
	return pTitle;
}

//=============================
// 初期化処理
//=============================
HRESULT CTitle::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 200.0f, 0.0f),
		D3DXVECTOR3(400.0f, 200.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TITLE));
	
	// 人数選択クラスの生成
	CCountSelect::Create();

	// カメラの生成
	CManager::SetCamera(CCamera::Create());
	// カメラの位置調整
	CManager::GetCamera()->SetPosV(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y + 150.0f, 500.0f));

	// 海の生成
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y -24.0f, 0.0f), 0.001f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y -22.0f, 0.0f), 0.0025f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y -20.0f, 0.0f), 0.004f, CSea::TYPE_NORMAL);

	// 背景
	CBg::Create();

	// 氷山の生成
	CIceberg::Create(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y - 50.0f, -900.0f), CIceberg::ICEBERG_TYPE(rand() % CIceberg::ICEBERG_MAX));

	if (rand() % 2 == 0)
	{
		CStage::Create(D3DXVECTOR3(0.0f, OBJ_BACE_POS_Y, 0.0f), CStage::STAGE_TYPE_LARGE);
	}
	else
	{
		// プレイヤーの生成
		// 生成位置X軸の調整
		float posX = 0 + ((float)(MAX_PLAYER_NUM - 1) * STAGE_SPACE) / 2;
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
		{
			// ステージの生成
			CStage::Create(D3DXVECTOR3(posX, OBJ_BACE_POS_Y, 0.0f), CStage::STAGE_TYPE_NORMAL);

			posX -= STAGE_SPACE;
		}
	}

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CTitle::Uninit(void)
{
	// カメラクラスの解放処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		CManager::SetCamera(NULL);
		pCamera = NULL;
	}

	if (m_pPolygon != NULL)
	{
		// ポリゴンの終了処理
		m_pPolygon->Uninit();

		// メモリの解放
		delete m_pPolygon;
		m_pPolygon = NULL;
	}

	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CTitle::Update(void)
{
	// カメラクラスの解放処理
	// カメラクラス更新処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Update();
	}


	// ポリゴンの更新処理
	m_pPolygon->Update();

	//if( CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) || 
	//	CManager::GetMouse()->GetMouseTrigger(0) || 
	//	CManager::GetJoypad()->GetJoystickTrigger(3, 0)||
	//	CManager::GetJoypad()->GetJoystickTrigger(11, 0))
	//{
	//	CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
	//}
}


//=============================
// 描画処理
//=============================
void CTitle::Draw(void)
{
	// カメラクラス更新処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->SetCamera();
	}

	// ポリゴンの描画処理
	m_pPolygon->Draw();
}
