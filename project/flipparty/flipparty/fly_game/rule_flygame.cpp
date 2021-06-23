////////////////////////////////////////////////////
//
//    カメラクラスの処理[camera.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "rule_flygame.h"
#include "count_selection.h"
#include "player.h"
#include "game.h"
#include "camera_flygame.h"
#include "light.h"

//******************************
// マクロ定義
//******************************
#define PLAYER_SPACE 150.0f

//******************************
// 静的メンバ変数宣言
//******************************

//******************************
// コンストラクタ
//******************************
CRuleFly::CRuleFly()
{
	// 変数のクリア
}

//******************************
// デストラクタ
//******************************
CRuleFly::~CRuleFly()
{
}

//******************************
// クリエイト
//******************************
CRuleFly * CRuleFly::Create(void)
{
	CRuleFly * pCamera = new CRuleFly;
	pCamera->Init();

	return pCamera;
}

//******************************
// 初期化処理
//******************************
HRESULT CRuleFly::Init(void)
{
	// カメラクラスの生成
	CGame::SetCamera(CFlyGameCamera::Create());

	// プレイヤー数の取得
	int nPlayNum = CCountSelect::GetPlayerNum();
	
	// プレイヤーの生成
	// 生成位置X軸の調整
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		CPlayer::Create(D3DXVECTOR3(posX, 0.0f, 0.0f), nCntPlayer);
		posX -= PLAYER_SPACE;
	}

	return S_OK;
}

//******************************
// 初期化処理
//******************************
void CRuleFly::Uninit(void)
{

}

//******************************
// 更新処理
//******************************
void CRuleFly::Update(void)
{
}
