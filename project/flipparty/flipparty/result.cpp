////////////////////////////////////////////////////
//
//    リザルトクラスの処理[result.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "camera_base.h"
#include "player.h"
#include "bg.h"
#include "count_selection.h"
#include "tears_manager.h"

//**********************************
// 静的メンバ変数宣言
//**********************************

//**********************************
// マクロ定義
//**********************************
#define PLAYER_SPACE 150.0f //　プレイヤー位置の間隔
#define PLAYER_POS_Z 100.0f // プレイヤーのZ位置
#define PLAYER_FALL_COUNT 100 // プレイヤーがこけるカウント数

//=============================
// コンストラクタ
//=============================
CResult::CResult()
{
	m_pPolygon = NULL;
	ZeroMemory(&m_apPlayer, sizeof(m_apPlayer));
	m_nCntFallTime = 0;
}

//=============================
// デストラクタ
//=============================
CResult::~CResult()
{
}

//=============================
// クリエイト
//=============================
CResult * CResult::Create(void)
{
	// メモリの確保
	CResult *pResult = new CResult;
	// 初期化
	pResult->Init();
	return pResult;
}

//=============================
// 初期化処理
//=============================
HRESULT CResult::Init(void)
{
	//// カメラクラスの生成
	CManager::SetCamera(CCamera::Create());
	//m_pCamera = CGame::GetCamera();

	// 背景の生成
	CBg::Create();

	// プレイヤー数の取得
	int nPlayNum = CCountSelect::GetPlayerNum();

	// プレイヤーの生成
	// 生成位置X軸の調整
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		m_apPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(posX, -PLAYER_CENTER_HEIGHT, PLAYER_POS_Z), nCntPlayer);

		// カメラの方向に体を向ける
		D3DXVECTOR3 cemeraPos = CManager::GetCamera()->GetPos();
		float fRotY = atan2f(posX - cemeraPos.x, PLAYER_POS_Z - cemeraPos.z);

		// 角度の調整
		m_apPlayer[nCntPlayer]->SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));
		
		// 操作フラグfalse
		m_apPlayer[nCntPlayer]->SetMoveFlag(false);

		posX -= PLAYER_SPACE;
	}

	// カウントの初期化
	m_nCntFallTime = 0;

	/*m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));*/

	//m_pPolygon->BindTexture();
	
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CResult::Uninit(void)
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
void CResult::Update(void)
{

	// カメラクラスの更新v処理
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Update();
	}

	if (m_pPolygon != NULL)
	{
		// ポリゴンの更新処理
		m_pPolygon->Update();
	}

	//// カウントを進める
	//m_nCntFallTime++;
	//if (PLAYER_FALL_COUNT <= m_nCntFallTime)
	//{// 一定のカウントで
	//	// カウントのリセット
	//	m_nCntFallTime = 0;
	//	// プレイヤー数の取得
	//	int nPlayNum = CCountSelect::GetPlayerNum();
	//
	//	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	//	{
	//		// コケるモーションの再生
	//		m_apPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_FALL);
	//
	//		D3DXVECTOR3 headPos;
	//		headPos.x = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._41;
	//		headPos.y = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._42;
	//		headPos.z = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._43 - 10;
	//		CTearsManager::Create(headPos);
	//	}
	//}

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) || 
		CManager::GetMouse()->GetMouseTrigger(0) || 
		CManager::GetJoypad()->GetJoystickTrigger(3, 0))
	{
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
	}
}


//=============================
// 描画処理
//=============================
void CResult::Draw(void)
{
	CCamera * pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->SetCamera();
	}

	if (m_pPolygon != NULL)
	{
		// ポリゴンの描画処理
		m_pPolygon->Draw();
	}
}
