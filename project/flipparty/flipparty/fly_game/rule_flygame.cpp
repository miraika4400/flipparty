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
#include "player_flygame.h"
#include "game.h"
#include "camera_flygame.h"
#include "light.h"
#include "timelimit.h"
#include "camera_tps.h"
#include "mini_result.h"
#include "bg.h"
#include "cloud.h"

//******************************
// マクロ定義
//******************************
#define PLAYER_SPACE 150.0f //　プレイヤー位置の間隔
#define PLAY_TIME 5         // 制限時間

//******************************
// 静的メンバ変数宣言
//******************************

//******************************
// コンストラクタ
//******************************
CRuleFly::CRuleFly()
{
	// 変数のクリア
	m_pTimeLimit = NULL;
	m_bPlay = true;
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
	CRuleFly * pRuleFly = new CRuleFly;
	pRuleFly->Init();

	return pRuleFly;
}

//******************************
// 初期化処理
//******************************
HRESULT CRuleFly::Init(void)
{
	// 背景の生成
	CBg::Create();

	// カメラクラスの生成
	CGame::SetCamera(CFlyGameCamera::Create());

	// プレイヤー数の取得
	int nPlayNum = CCountSelect::GetPlayerNum();
	
	// プレイヤーの生成
	// 生成位置X軸の調整
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		CFlyGamePlayer::Create(D3DXVECTOR3(posX, 0.0f, 0.0f), nCntPlayer);
		posX -= PLAYER_SPACE;
	}

	// 制限時間の生成
	m_pTimeLimit = CTimeLimit::Create(PLAY_TIME);

	// プレイ中フラグの初期化
	m_bPlay = true;

	// 雲生成
	CCloud::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	// 制限時間が0以下の時
	if (m_pTimeLimit->GetTimeLimit() <= 0)
	{
		if (m_bPlay)
		{
			// ゲーム中フラグをfalse
			m_bPlay = false;

			// 順位判定
			JudgeRank();
		}
		else
		{
			// カメラクラス
			CGame::SetCamera(CFlyGameCamera::Create());
		}
	}
}

//******************************
// 描画処理
//******************************
void CRuleFly::Draw(void)
{
}

//******************************
// 順位判定処理
//******************************
void CRuleFly::JudgeRank(void)
{
	std::vector<CPlayer*> vectorPlayer; // 順位付け用にプレイヤー情報を格納する変数 
	int nPlayerIndex = 0;  // ↑の変数のポインタをずらす用変数

	// プレイヤーオブジェクトの取得
	CPlayer *pPlayer = (CPlayer *)CScene::GetTop(CScene::OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		// 順位判定用変数に情報を保存
		vectorPlayer.push_back(pPlayer);
		nPlayerIndex++;

		if (pPlayer->GetMoveFlag())
		{
			// 操作を不可にする
			pPlayer->SetMoveFlag(false);
		}

		// 次のプレイヤー情報に更新
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}

	// ダブルポインタをY座標の高い順にソート
	for (int nCntPlayer = 0; nCntPlayer < nPlayerIndex; nCntPlayer++)
	{
		for (int nCntSort = nCntPlayer + 1; nCntSort < nPlayerIndex; nCntSort++)
		{
			if (vectorPlayer[nCntPlayer]->GetPos().y < vectorPlayer[nCntSort]->GetPos().y)
			{
				CPlayer * pSave = vectorPlayer[nCntPlayer];
				vectorPlayer[nCntPlayer] = vectorPlayer[nCntSort];
				vectorPlayer[nCntSort] = pSave;
			}
		}
	}

	// 順位付け
	for (int nCntPlayer = 0; nCntPlayer < nPlayerIndex; nCntPlayer++)
	{
		// 配列の順番がそのまま順位に
		vectorPlayer[nCntPlayer]->SetRank(nCntPlayer);

		// Y軸の座標が同じなら同じ順位にする
		if (nCntPlayer != 0)
		{
			if (vectorPlayer[nCntPlayer]->GetPos().y == vectorPlayer[nCntPlayer - 1]->GetPos().y)
			{
				vectorPlayer[nCntPlayer]->SetRank(vectorPlayer[nCntPlayer - 1]->GetRank());
			}
		}
	}

	// リザルト生成
	CMiniResult::Create();
}
