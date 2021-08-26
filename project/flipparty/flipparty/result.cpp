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
#include "rank_ui.h"
#include "resultboard.h"

//**********************************
// マクロ定義
//**********************************
#define PLAYER_SPACE 150.0f //　プレイヤー位置の間隔
#define PLAYER_POS_Z 100.0f // プレイヤーのZ位置
#define PLAYER_FALL_COUNT 300 // プレイヤーがこけるカウント数
#define RANK_UI_HEGHT -50  // ランキングのUIプレイヤーからの位置
#define RESULT_BOARD_SPACE 320.0f

//**********************************
// 静的メンバ変数宣言
//**********************************
CResult::ResultPoint CResult::m_resultPoint[MAX_PLAYER_NUM] = {};

//=============================
// コンストラクタ
//=============================
CResult::CResult()
{
	ZeroMemory(&m_apPlayer, sizeof(m_apPlayer));
	m_nCntFallTime = 0;
	m_nActionRank = 0;
	m_bShow = true;
	m_bBoard = false;
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

	// アクションを起こす順位の初期化(最下位)
	m_nActionRank = nPlayNum - 1;

	// 点数計算
	CalculationRank();

	// ボードフラグ
	m_bBoard = false;
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

	// 集計ポイントを初期化しておく
	ResetResultPoint();

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

	if (m_bShow)
	{// 結果発表中
		
		// 結果発表時にプレイヤーのモーションを変える
		ChagePlayerMotion();
	}
	else
	{// 結果発表終了時
		if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
			CManager::GetMouse()->GetMouseTrigger(0) ||
			CManager::GetJoypad()->GetJoystickTrigger(3, 0))
		{
			if (!m_bBoard)
			{// リザルトボードの生成
				
				// プレイヤー数の取得
				int nPlayerNum = CCountSelect::GetPlayerNum();

				D3DXVECTOR3 boardPos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
				boardPos.x = boardPos.x - (RESULT_BOARD_SPACE*(nPlayerNum - 1)) / 2;

				for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
				{
					CResultBoard::Create(nCntPlayer, boardPos);
					boardPos.x += RESULT_BOARD_SPACE;
				}
				m_bBoard = true;
			}
			else
			{// 画面遷移
				CManager::GetFade()->SetFade(CManager::MODE_TITLE);
			}

			return;
		}
	}

	// プレイヤーの位置の調整
	AdjustPlayerPos();
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
}

//=============================
// プレイヤーのモーションを変える
//=============================
void CResult::ChagePlayerMotion(void)
{
	// カウントを進める
	m_nCntFallTime++;
	if (PLAYER_FALL_COUNT <= m_nCntFallTime)
	{// 一定のカウントで
	 // カウントのリセット
		m_nCntFallTime = 0;
		// プレイヤー数の取得
		int nPlayNum = CCountSelect::GetPlayerNum();

		for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
		{
			if (m_nActionRank != 1)
			{//3位以下
				if (m_apPlayer[nCntPlayer]->GetRank() == m_nActionRank)
				{
					// コケるモーションの再生
					m_apPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_FALL);
					// 表情の変更
					m_apPlayer[nCntPlayer]->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);
					//// 涙の生成
					//D3DXVECTOR3 headPos;
					//headPos.x = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._41;
					//headPos.y = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._42;
					//headPos.z = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._43 - 10;
					//CTearsManager::Create(headPos);
				}
			}
			else
			{// 2位発表時と同時に一位も発表
				if (m_apPlayer[nCntPlayer]->GetRank() == m_nActionRank)
				{
					// コケるモーションの再生
					m_apPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_FALL);
					// 表情の変更
					m_apPlayer[nCntPlayer]->SetFacePattern(CPlayer::FACE_PATTERN_NO_GOOD);
					//// 涙の生成
					//D3DXVECTOR3 headPos;
					//headPos.x = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._41;
					//headPos.y = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._42;
					//headPos.z = m_apPlayer[nCntPlayer]->GetModelData()[PLAYER_HEAD_PARTS_NUM].mtxWorld._43 - 10;
					//CTearsManager::Create(headPos);
				}
				else if (m_apPlayer[nCntPlayer]->GetRank() == 0)
				{
					// 一位モーションの再生
					m_apPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_MINIRESULT_1);
				}

			}
		}

		m_nActionRank--;
		if (m_nActionRank <= 0)
		{
			m_bShow = false;

			// 同ポイントを考慮して順位をつけなおす
			JudgePlayerRank(true);
		}
	}
}

//=============================
// 点数・順位の計算
//=============================
void CResult::CalculationRank(void)
{
	// プレイヤー数の取得
	int nPlayerNum = CCountSelect::GetPlayerNum();

	//////////////////////
	// 総合点数の計算

	// プレイヤー数でループ
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		// ルール数でループ
		for (int nCntRule = 0; nCntRule < CRuleManager::RULE_MAX; nCntRule++)
		{

			// ポイントの加算
			switch (m_resultPoint[nCntPlayer].nMiniGameRank[nCntRule])
			{
			case 0:
				// 一位
				m_resultPoint[nCntPlayer].nPoint += POINT_1ST;
				break;

			case 1:
				// 二位
				m_resultPoint[nCntPlayer].nPoint += POINT_2ND;
				break;

			case 2:
				// 三位
				m_resultPoint[nCntPlayer].nPoint += POINT_3RD;
				break;

			case 3:
				// 四位
				m_resultPoint[nCntPlayer].nPoint += POINT_4TH;
				break;

			default:
				break;
			}
		}
	}

	//////////////////////////////////
	// ポイントをプレイヤーに反映
	
	// プレイヤー数でループ
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		// ポイントの反映
		m_apPlayer[nCntPlayer]->SetPoint(m_resultPoint[nCntPlayer].nPoint);
	}

	// 同じ点数でも順位を分けて順位付け
	JudgePlayerRank(false);
}

//=============================
// 順位付け
//=============================
void CResult::JudgePlayerRank(bool bSamePointRank)
{
	// プレイヤー数の取得
	int nPlayerNum = CCountSelect::GetPlayerNum();

	////////////////////////////////
	// 順位付け

	// ポイントの高い順にソート
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		for (int nCntSort = nCntPlayer + 1; nCntSort < nPlayerNum; nCntSort++)
		{
			if (m_apPlayer[nCntPlayer]->GetPoint() < m_apPlayer[nCntSort]->GetPoint())
			{
				CPlayer * pSave = m_apPlayer[nCntPlayer];
				m_apPlayer[nCntPlayer] = m_apPlayer[nCntSort];
				m_apPlayer[nCntSort] = pSave;
			}
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		// 配列の順番がそのまま順位に
		m_apPlayer[nCntPlayer]->SetRank(nCntPlayer);

		if (bSamePointRank)
		{
			if (nCntPlayer != 0)
			{

				// ポイントが同じなら同じ順位にする
				if (m_apPlayer[nCntPlayer]->GetPoint() == m_apPlayer[nCntPlayer - 1]->GetPoint())
				{
					m_apPlayer[nCntPlayer]->SetRank(m_apPlayer[nCntPlayer - 1]->GetRank());
				}
			}

			D3DXVECTOR3 playerPos = m_apPlayer[nCntPlayer]->GetPos();
			// ランクUIの生成
			CRankUI::Create(D3DXVECTOR3(playerPos.x, playerPos.y + RANK_UI_HEGHT, playerPos.z), m_apPlayer[nCntPlayer]->GetRank());
		}
		else
		{
			if (nCntPlayer != 0)
			{

				// ポイントが同じなら同じ順位にする
				if (m_apPlayer[nCntPlayer]->GetPoint() == m_apPlayer[0]->GetPoint())
				{
					m_apPlayer[nCntPlayer]->SetRank(m_apPlayer[0]->GetRank());
				}
			}
		}
	}
}

//=============================
// プレイヤーの位置の調整
//=============================
void CResult::AdjustPlayerPos(void)
{
	// プレイヤー数の取得
	int nPlayerNum = CCountSelect::GetPlayerNum();
	for (int nCntPlayer = 0; nCntPlayer < nPlayerNum; nCntPlayer++)
	{
		if (m_apPlayer[nCntPlayer]->GetMotionActive(CPlayer::MOTION_FALL))
		{// コケるモーションの時
			D3DXVECTOR3 playerPos = m_apPlayer[nCntPlayer]->GetPos();
			playerPos.y += ((-PLAYER_CENTER_HEIGHT - 20) - playerPos.y)*0.05f;

			m_apPlayer[nCntPlayer]->SetPos(playerPos);
		}
	}

}
