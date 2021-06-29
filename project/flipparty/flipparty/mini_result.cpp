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

//**********************************
// 静的メンバ変数宣言
//**********************************

//**********************************
// マクロ定義
//**********************************
#define PLAYER_SPACE 150.0f //　プレイヤー位置の間隔
#define BLACKOUT_SIZE  D3DXVECTOR3(10000.0f, 10000.0f, 0.0f)
#define BLACKOUT_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f)
#define BLACKOUT_POS   D3DXVECTOR3(0.0f, 0.0f, 50.0f)
#define LIGHT_DIR     

//=============================
// コンストラクタ
//=============================
CMiniResult::CMiniResult():CScene(OBJTYPE_MINIRESULT)
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
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 背景を暗くするよう
	CScene3d * p3DPolygon = CScene3d::Create(BLACKOUT_POS, BLACKOUT_SIZE);
	p3DPolygon -> SetColor(BLACKOUT_COLOR);      //色の設定
	p3DPolygon->SetPriority(OBJTYPE_MINIRESULT); // プライオリティの設定

	// プレイヤー数の取得
	int nPlayNum = CCountSelect::GetPlayerNum();

	// プレイヤーオブジェクトの取得
	CPlayer *pPlayer = (CPlayer *)CScene::GetTop(CScene::OBJTYPE_PLAYER);

	// 最下位の順位
	int nWorstRank = pPlayer->GetRank();

	// 生成位置X軸の調整
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		// 最下位の順位
		if (nWorstRank < pPlayer->GetRank())
		{
			nWorstRank = pPlayer->GetRank();
		}

		// プレイヤー生成位置
		D3DXVECTOR3 createPlayerPos = D3DXVECTOR3(posX, -PLAYER_CENTER_HEIGHT, 100.0f);
		// プレイヤーの生成
		CPlayer * pResultPlayer = CPlayer::Create(createPlayerPos, nCntPlayer);
		// オブジェクトタイプ
		pResultPlayer->SetPriority(OBJTYPE_MINIRESULT);
		// 操作不可
		pResultPlayer->SetMoveFlag(false);

		// カメラの方向に体を向ける
		D3DXVECTOR3 cemeraPos = CGame::GetCamera()->GetPos();
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
		else if(pPlayer->GetRank() == nWorstRank)
		{// 最下位
			pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_4);
			// 角度の調整
			pResultPlayer->SetRot(D3DXVECTOR3(D3DXToRadian(90.0f), fRotY, 0.0f));
			// 表情の設定
			pResultPlayer->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);
		}
		else if (pPlayer->GetRank() == 1)
		{// 二位
			pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_2);
		}
		else if (pPlayer->GetRank() == 2)
		{// 最下位
			pResultPlayer->SetMotion(CPlayer::MOTION_MINIRESULT_3);
			// 表情の設定
			pResultPlayer->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);
		}

		// 位置をずらす
		posX -= PLAYER_SPACE;

		pPlayer = (CPlayer *)pPlayer->GetNext();
	}

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CMiniResult::Uninit(void)
{
	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CMiniResult::Update(void)
{

}


//=============================
// 描画処理
//=============================
void CMiniResult::Draw(void)
{
	// カメラの切り替え
	CCamera * pCamera = CCamera::Create();
	// カメラクラスの生成
	CGame::SetCamera(pCamera);
	pCamera->SetCamera();

}
