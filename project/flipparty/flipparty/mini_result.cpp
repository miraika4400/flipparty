////////////////////////////////////////////////////
//
//    ミニゲームリザルトクラスの処理[mini_result.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "mini_result.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "sound.h"
#include "game.h"
#include "camera_base.h"
#include "count_selection.h"
#include "player.h"
#include "rank_ui.h"
#include "tears_manager.h"
#include "rule_manager.h"
#include "sound.h"
#include "sea.h"
#include "iceberg.h"
#include "stage.h"
#include "resource_texture.h"

//**********************************
// 静的メンバ変数宣言
//**********************************

//**********************************
// マクロ定義
//**********************************
#define PLAYER_SPACE 150.0f //　プレイヤー位置の間隔
#define BLACKOUT_SIZE  D3DXVECTOR3(10000.0f, 10000.0f, 0.0f)
#define BLACKOUT_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f)
#define BLACKOUT_POS   D3DXVECTOR3(0.0f, 2000.0f, 50.0f)
#define PLAYER_RESULT_WORST_ROT_X D3DXToRadian(70.0f) // 最下位の時の回転軸のXの値
#define RANK_UI_HEGHT -50  // ランキングのUIプレイヤーからの位置
#define OBJ_BASE_POS_Y 2000.0f
#define LOGO_POS D3DXVECTOR3(SCREEN_WIDTH/2, 100.0f, 0.0f)
#define LOGO_SIZE D3DXVECTOR3(300.0f,75.0f,0.0f)

//=============================
// コンストラクタ
//=============================
CMiniResult::CMiniResult():CScene(OBJTYPE_MINIRESULT_SYSTEM)
{
}

//=============================
// デストラクタ
//=============================
CMiniResult::~CMiniResult()
{
}

//=============================
// クリエイト
//=============================
CMiniResult * CMiniResult::Create(void)
{
	// メモリの確保
	CMiniResult *pMiniResult = new CMiniResult;
	// 初期化
	pMiniResult->Init();
	return pMiniResult;
}

//=============================
// 初期化処理
//=============================
HRESULT CMiniResult::Init(void)
{
	// カメラの切り替え
	CCamera * pCamera = CCamera::Create();
	// カメラクラスの生成
	CManager::SetCamera(pCamera);
	pCamera->SetCamera();

	D3DXVECTOR3 cameraPos = CManager::GetCamera()->GetPos();
	cameraPos.y = OBJ_BASE_POS_Y + 100.0f;
	CManager::GetCamera()->SetPosV(cameraPos);

	// 海の生成
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 24.0f, 0.0f), 0.001f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 22.0f, 0.0f), 0.0025f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 20.0f, 0.0f), 0.004f, CSea::TYPE_NORMAL);

	// 氷山の生成
	CIceberg::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 50.0f, -900.0f), CIceberg::ICEBERG_TYPE(rand() % CIceberg::ICEBERG_MAX));

	// プレイヤー数の取得
	int nPlayNum = CCountSelect::GetPlayerNum();

	// プレイヤーオブジェクトの取得
	CPlayer *pPlayer = (CPlayer *)CScene::GetTop(CScene::OBJTYPE_PLAYER);

	if (pPlayer != NULL)
	{
		// 最下位の順位
		int nWorstRank = pPlayer->GetRank();
		for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
		{
			// 最下位の順位
			if (nWorstRank < pPlayer->GetRank())
			{
				nWorstRank = pPlayer->GetRank();
			}
			pPlayer = (CPlayer*)pPlayer->GetNext();
		}

		// プレイヤー情報の初期化
		pPlayer = (CPlayer *)CScene::GetTop(CScene::OBJTYPE_PLAYER);

		// 生成位置X軸の調整
		float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
		for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
		{
			// プレイヤー生成位置
			D3DXVECTOR3 createPlayerPos = D3DXVECTOR3(posX, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT, 100.0f);

			// プレイヤーの生成
			CPlayer * pResultPlayer = CPlayer::Create(createPlayerPos, nCntPlayer);
			// オブジェクトタイプ
			pResultPlayer->SetPriority(OBJTYPE_MINIRESULT_OBJ);
			// 操作不可
			pResultPlayer->SetMoveFlag(false);

			// カメラの方向に体を向ける
			D3DXVECTOR3 cemeraPos = CManager::GetCamera()->GetPos();
			float fRotY = atan2f(createPlayerPos.x - cemeraPos.x, createPlayerPos.z - cemeraPos.z);

			// 角度の調整
			pResultPlayer->SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));

			// モーションの分岐
			if (pPlayer->GetRank() == 0)
			{// 一位
				pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_1);
				// 表情の設定
				pResultPlayer->SetFacePattern(CPlayer::FACE_PATTERN_GOOD);
			}
			else if (pPlayer->GetRank() == nWorstRank)
			{// 最下位
				pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_4);
				// 角度の調整
				pResultPlayer->SetPos(D3DXVECTOR3(createPlayerPos.x, createPlayerPos.y - 20, createPlayerPos.z));
				// 表情の設定
				pResultPlayer->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);
				pResultPlayer->Draw();
				D3DXVECTOR3 headPos;
				headPos.x = pResultPlayer->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._41;
				headPos.y = pResultPlayer->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._42;
				headPos.z = pResultPlayer->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._43 - 10;
				CTearsManager::Create(headPos);
			}
			else if (pPlayer->GetRank() == 1)
			{// 二位
				pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_2);
			}
			else if (pPlayer->GetRank() == 2)
			{// 三位
				pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_3);
				D3DXVECTOR3 pos = pResultPlayer->GetPos();
				pos.y -= 8.0f;
				pResultPlayer->SetPos(pos);

				// 表情の設定
				pResultPlayer->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);
			}

			// ランクUIの生成
			CRankUI::Create(D3DXVECTOR3(createPlayerPos.x, createPlayerPos.y + RANK_UI_HEGHT, createPlayerPos.z), pPlayer->GetRank());

			CStage::Create(createPlayerPos, CStage::STAGE_TYPE_NORMAL);

			// 位置をずらす
			posX -= PLAYER_SPACE;

			pPlayer = (CPlayer*)pPlayer->GetNext();
		}
	}

	// ロゴの生成
	CScene2d*pLogo = CScene2d::Create();
	pLogo->SetPriority(OBJTYPE_UI);// プライオリティ
	pLogo->SetPos(LOGO_POS);       // 座標
	pLogo->SetSize(LOGO_SIZE);     // サイズ
	pLogo->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_MINIRESULT_LOGO));// テクスチャ

	// BGMの再生
	CManager::GetSound()->Play(CSound::LABEL_BGM_MINIRESULT);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CMiniResult::Uninit(void)
{
	// BGMの停止
	CManager::GetSound()->Stop(CSound::LABEL_BGM_MINIRESULT);
	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CMiniResult::Update(void)
{
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
		CManager::GetMouse()->GetMouseTrigger(0) ||
		CManager::GetJoypad()->GetJoystickTrigger(3, 0) ||
		CManager::GetJoypad()->GetJoystickTrigger(11, 0))
	{
		CGame::GetRuleManager()->TransitionRule();

		// BGMの停止
		CManager::GetSound()->Stop(CSound::LABEL_BGM_MINIRESULT);
	}
}


//=============================
// 描画処理
//=============================
void CMiniResult::Draw(void)
{
	// カメラの切り替え
	CCamera * pCamera = CCamera::Create();
	// カメラクラスの生成
	CManager::SetCamera(pCamera);
	pCamera->SetCamera();
}
