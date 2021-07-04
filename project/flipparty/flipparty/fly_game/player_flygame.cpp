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

//*****************************
// マクロ定義
//*****************************
#define FLY_HEIGHT 0.5f // 一回の判定で飛ぶ高さ
#define FLY_RATE 1.0f   // 飛ぶ係数

//*****************************
// 静的メンバ変数宣言
//*****************************

//******************************
// コンストラクタ
//******************************
CFlyGamePlayer::CFlyGamePlayer()
{
	m_fHeightDist = 0.0f;
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
	}

	// 座標の取得
	D3DXVECTOR3 pos = GetPos();
	pos.y += (m_fHeightDist - pos.y)*FLY_RATE;
	// 座標のセット
	SetPos(pos);
}
