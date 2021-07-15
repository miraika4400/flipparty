////////////////////////////////////////////////////
//
//    particleクラスの処理[particle.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "player_flygame.h"
#include "rule_flygame.h"
#include "manager.h"
#include "keyboard.h"
#include "joypad.h"

//*****************************
// マクロ定義
//*****************************
#define FLY_HEIGHT 0.5f // 一回の判定で飛ぶ高さ
#define FLY_RATE 1.0f   // 飛ぶ係数
#define STAN_FLANE 100  // スタンフレーム数

//*****************************
// 静的メンバ変数宣言
//*****************************

//******************************
// コンストラクタ
//******************************
CFlyGamePlayer::CFlyGamePlayer()
{
	m_fHeightDist = 0.0f;
	m_state = STATE_NORMAL;
	m_nCntState = 0;
}

//******************************
// デストラクタ
//******************************
CFlyGamePlayer::~CFlyGamePlayer()
{
}

//******************************
// クリエイト
//******************************
CFlyGamePlayer * CFlyGamePlayer::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
	// メモリの確保
	CFlyGamePlayer *pPlayer;
	pPlayer = new CFlyGamePlayer;

	// プレイヤー番号のセット
	pPlayer->SetPlayerNumber(nPlayerNum);

	// 初期化
	pPlayer->Init();

	// 各値の代入・セット
	pPlayer->SetPos(pos);
	pPlayer->SetPriority(OBJTYPE_PLAYER); // オブジェクトタイプ
	pPlayer->m_fHeightDist = pos.y;

	return pPlayer;
}

//******************************
// 初期化処理
//******************************
HRESULT CFlyGamePlayer::Init(void)
{
	CPlayer::Init();

	// 状態初期化
	m_state = STATE_NORMAL;
	m_nCntState = 0;

	SetFacePattern(FACE_PATTERN_GOOD);
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CFlyGamePlayer::Uninit(void)
{
	CPlayer::Uninit();
}

//******************************
// 更新処理
//******************************
void CFlyGamePlayer::Update(void)
{
	// 状態管理
	ManageState();

	if (GetMoveFlag())
	{
		// フリッパー更新前の移動状態
		CFlipper::FLIPPER_STATE leftStateOld = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT);
		CFlipper::FLIPPER_STATE rightStateOld = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT);

		// プレイヤークラスの更新処理
		CPlayer::Update();

		// 飛ぶ処理
		Fly(GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT), leftStateOld);
		Fly(GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT), rightStateOld);
	}
}

//******************************
// 描画処理
//******************************
void CFlyGamePlayer::Draw(void)
{
	CPlayer::Draw();
}

//******************************
// 飛ぶ処理
//******************************
void CFlyGamePlayer::Fly(CFlipper::FLIPPER_STATE stateNow, CFlipper::FLIPPER_STATE stateOld)
{
	if (stateNow != stateOld)
	{
		// 高さにプラス
		m_fHeightDist += FLY_HEIGHT;

		SetMotion(MOTION_FLY);
		SetFacePattern(FACE_PATTERN_NORMAL);
	}

	// 座標の取得
	D3DXVECTOR3 pos = GetPos();
	pos.y += (m_fHeightDist - pos.y)*FLY_RATE;
	// 座標のセット
	SetPos(pos);
}

//******************************
// 状態管理
//******************************
void CFlyGamePlayer::ManageState(void)
{
	switch (m_state)
	{
	case STATE_NORMAL:
		break;
	case STATE_STAN:

		if (m_nCntState == 0) 
		{
			SetMotion(MOTION_MINIRESULT_3);
			SetMoveFlag(false);
			SetFacePattern(FACE_PATTERN_NO_GOOD);
		}
		
		m_nCntState++;
		if (m_nCntState >= STAN_FLANE)
		{
			m_nCntState = 0;
			m_state = STATE_NORMAL;
			SetMotion(MOTION_FLY);
			SetMoveFlag(CRuleFly::GetPlayFlag());
			SetFacePattern(FACE_PATTERN_NORMAL);
		}
		break;

	default:
		break;
	}
}

//******************************
// 羽の操作処理
//******************************
void CFlyGamePlayer::ControllFlipper(void)
{

#ifdef _DEBUG
	// キーボード操作
	// 右羽を操作
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_A))
	{
		if (GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT) == CFlipper::FLIPPERSTATE_DOWN)
		{// 上げる
			SetFlipperDist(CFlipper::FLIPPER_TYPE_RIGHT, RIGHT_FLIPPER_DIST_ANGLE_UP);

			// 移動状態の更新
			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
		}
		else
		{// 下げる
			SetFlipperDist(CFlipper::FLIPPER_TYPE_RIGHT, RIGHT_FLIPPER_DIST_ANGLE_DOWN);

			// 移動状態の更新
			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
		}
	}

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_D))
	{
		if (GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT) == CFlipper::FLIPPERSTATE_DOWN)
		{// 上げる
			SetFlipperDist(CFlipper::FLIPPER_TYPE_LEFT, LEFT_FLIPPER_DIST_ANGLE_UP);

			// 移動状態の更新
			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
		}
		else
		{// 下げる
			SetFlipperDist(CFlipper::FLIPPER_TYPE_LEFT, LEFT_FLIPPER_DIST_ANGLE_DOWN);

			// 移動状態の更新
			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
		}
	}

#endif // _DEBUG
	// コントローラー操作

	// プレイヤー番号の取得
	int nPlayerNum = GetPlayerNumber();
	// 右羽を操作
	if (CManager::GetJoypad()->GetJoystickTrigger(5, nPlayerNum))
	{
		if (GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT) == CFlipper::FLIPPERSTATE_DOWN)
		{
			// 上げる
			SetFlipperDist(CFlipper::FLIPPER_TYPE_RIGHT, RIGHT_FLIPPER_DIST_ANGLE_UP);

			// 移動状態の更新
			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
		}
		else
		{// 下げる
			SetFlipperDist(CFlipper::FLIPPER_TYPE_RIGHT, RIGHT_FLIPPER_DIST_ANGLE_DOWN);

			// 移動状態の更新
			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
		}
	}

	// 左羽を操作
	if (CManager::GetJoypad()->GetJoystickTrigger(4, nPlayerNum))
	{
		if (GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT) == CFlipper::FLIPPERSTATE_DOWN)
		{// 上げる
			SetFlipperDist(CFlipper::FLIPPER_TYPE_LEFT, LEFT_FLIPPER_DIST_ANGLE_UP);

			// 移動状態の更新
			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
		}
		else
		{// 下げる
			SetFlipperDist(CFlipper::FLIPPER_TYPE_LEFT, LEFT_FLIPPER_DIST_ANGLE_DOWN);

			// 移動状態の更新
			GetFlipperMoveState()->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
		}
	}
}
