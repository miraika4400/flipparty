//=============================================================================
//
// player_flag_raicing処理 [player_flag_raicing.cpp]
// Author : 山田　陵太
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "player_flag_raicing.h"
#include "flipper.h"
#include "flag_raicing_game_rule.h"
#include "add_point_display.h"
#include "manager.h"
#include "joypad.h"
#include "sound.h"
#include "keyboard.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CPlayerFlagRaicing::CPlayerFlagRaicing()
{
	m_pAddPointDisplay = NULL;
}

//=============================================================================
//デストラクタ
//=============================================================================
CPlayerFlagRaicing::~CPlayerFlagRaicing()
{
}

//=============================================================================
//クリエイト処理
//=============================================================================
CPlayerFlagRaicing * CPlayerFlagRaicing::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
	CPlayerFlagRaicing *pPlayerFlag = NULL;

	//インスタンス生成
	pPlayerFlag = new CPlayerFlagRaicing;

	if (pPlayerFlag)
	{
		pPlayerFlag->SetPlayerNumber(nPlayerNum);			//番号の設定
		pPlayerFlag->SetPos(pos);							//位置の設定
		pPlayerFlag->SetPriority(CScene::OBJTYPE_PLAYER);	//描画順を設定
		pPlayerFlag->Init();								//初期化		
	}

	return pPlayerFlag;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CPlayerFlagRaicing::Init(void)
{
	CPlayer::Init();

	m_pAddPointDisplay = CAddPointDisplay::Create(GetPlayerNumber());

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CPlayerFlagRaicing::Uninit(void)
{
	CPlayer::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CPlayerFlagRaicing::Update(void)
{
	CPlayer::Update();
}

//=============================================================================
//描画処理
//=============================================================================
void CPlayerFlagRaicing::Draw(void)
{
	CPlayer::Draw();
}

void CPlayerFlagRaicing::ControllFlipper(void)
{
#ifdef _DEBUG
	// キーボード操作
	// 右羽を操作
	if (CManager::GetKeyboard()->GetKeyPress(DIK_UP))
	{// 上げる
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_UP)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);

		//変更した情報を旗上げルールクラスへ送る
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);

	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_DOWN))
	{// 下げる
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_DOWN)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);

		//変更した情報を旗上げルールクラスへ送る
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);

	}

	// 左羽を操作
	if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
	{// 上げる
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_UP)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);

		//変更した情報を旗上げルールクラスへ送る
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);

	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_S))
	{// 下げる
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_DOWN)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);

		//変更した情報を旗上げルールクラスへ送る
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
	}

#endif // _DEBUG
	// コントローラー操作
	// 右羽を操作
	if (CManager::GetJoypad()->GetStick(GetPlayerNumber()).lRz <= -10)
	{// 上げる

		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_UP)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);

		//変更した情報を旗上げルールクラスへ送る
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (CManager::GetJoypad()->GetStick(GetPlayerNumber()).lRz >= 10)
	{// 下げる

		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_DOWN)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
		}
		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);

		//変更した情報を旗上げルールクラスへ送る
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
	}

	// 左羽を操作
	if (CManager::GetJoypad()->GetStick(GetPlayerNumber()).lY <= -10)
	{// 上げる

		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_UP)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);

		//変更した情報を旗上げルールクラスへ送る
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (CManager::GetJoypad()->GetStick(GetPlayerNumber()).lY >= 10)
	{// 下げる
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;

		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_DOWN)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + GetPlayerNumber()));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);

		//変更した情報を旗上げルールクラスへ送る
		CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
	}

}

