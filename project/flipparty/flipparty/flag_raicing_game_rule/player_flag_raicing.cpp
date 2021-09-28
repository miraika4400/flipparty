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
#include "resource_texture.h"
#include "scene3d.h"

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

		//　影の生成
		CScene3d * p3DPolygon = CScene3d::Create(D3DXVECTOR3(pos.x, pos.y + 1.0f, pos.z), PLAYER_SHADOW_SIZE);
		p3DPolygon->SetPriority(CScene::OBJTYPE_PARTICLE); // プライオリティの設定
		p3DPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PENGUIN_SHADOW));// テクスチャ
		p3DPolygon->SetColor(PLAYER_SHADOW_COLOR);// 色
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
//	//前回の値を取得
//	CFlipper::FLIPPER_STATE oldLeftFlipper = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT);
//	CFlipper::FLIPPER_STATE oldRightFlipper = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT);
//
	CPlayer::Update();

	////今回の値を取得
	//CFlipper::FLIPPER_STATE nowLeftFlipper = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_LEFT);
	//CFlipper::FLIPPER_STATE nowRightFlipper = GetFlipperMoveState()->GetState(CFlipper::FLIPPER_TYPE_RIGHT);

	////左のcheck
	//if (nowLeftFlipper != oldLeftFlipper)
	//{
	//	//変更した情報を旗上げルールクラスへ送る
	//	CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_LEFT, nowLeftFlipper);

	//}
	//if (nowRightFlipper != oldRightFlipper)
	//{
	//	//変更した情報を旗上げルールクラスへ送る
	//	CFlagRaicingGame_rule::SetPlayerData(GetPlayerNumber(), CFlipper::FLIPPER_TYPE_RIGHT, nowRightFlipper);
	//}
}

//=============================================================================
//描画処理
//=============================================================================
void CPlayerFlagRaicing::Draw(void)
{
	CPlayer::Draw();
}

CAddPointDisplay *CPlayerFlagRaicing::GetAddPoitDisplay(void)
{
	return m_pAddPointDisplay;
}

