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
#include "sound.h"
#include "resource_texture.h"
#include "stage.h"
#include "sea.h"
#include "iceberg.h"

//**********************************
// マクロ定義
//**********************************
#define PLAYER_SPACE 150.0f //　プレイヤー位置の間隔
#define PLAYER_POS_Z 100.0f // プレイヤーのZ位置
#define PLAYER_FALL_COUNT 300 // プレイヤーがこけるカウント数
#define RANK_UI_HEGHT -50  // ランキングのUIプレイヤーからの位置
#define RESULT_BOARD_SPACE 320.0f

#define LOGO_POS D3DXVECTOR3(SCREEN_WIDTH/2, 100.0f, 0.0f)
#define LOGO_SIZE D3DXVECTOR3(300.0f,75.0f,0.0f)
#define OBJ_BASE_POS_Y 2000.0f

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
	ZeroMemory(&m_apRankUI, sizeof(m_apRankUI));
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
	D3DXVECTOR3 cameraPos = CManager::GetCamera()->GetPos();
	cameraPos.y = OBJ_BASE_POS_Y + 100.0f;
	CManager::GetCamera()->SetPosV(cameraPos);

	// 背景の生成
	CBg::Create();

	// 海の生成
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 24.0f, 0.0f), 0.001f , CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 22.0f, 0.0f), 0.0025f, CSea::TYPE_NORMAL);
	CSea::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 20.0f, 0.0f), 0.004f , CSea::TYPE_NORMAL);

	// 氷山の生成
	CIceberg::Create(D3DXVECTOR3(0.0f, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT - 50.0f, -900.0f), CIceberg::ICEBERG_TYPE(rand() % CIceberg::ICEBERG_MAX));

	// プレイヤー数の取得
	int nPlayNum = CCountSelect::GetPlayerNum();

	// プレイヤーの生成
	// 生成位置X軸の調整
	float posX = 0 + ((float)(nPlayNum - 1) * PLAYER_SPACE) / 2;
	for (int nCntPlayer = 0; nCntPlayer < nPlayNum; nCntPlayer++)
	{
		m_apPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(posX, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT, PLAYER_POS_Z), nCntPlayer);

		// カメラの方向に体を向ける
		D3DXVECTOR3 cemeraPos = CManager::GetCamera()->GetPos();
		float fRotY = atan2f(posX - cemeraPos.x, PLAYER_POS_Z - cemeraPos.z);

		// 角度の調整
		m_apPlayer[nCntPlayer]->SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));
		
		// 操作フラグfalse
		m_apPlayer[nCntPlayer]->SetMoveFlag(false);

		CStage::Create(D3DXVECTOR3(posX, OBJ_BASE_POS_Y - PLAYER_CENTER_HEIGHT, PLAYER_POS_Z), CStage::STAGE_TYPE_NORMAL);
		posX -= PLAYER_SPACE;
	}

	// カウントの初期化
	m_nCntFallTime = 0;

	// アクションを起こす順位の初期化(最下位)
	m_nActionRank = nPlayNum - 1;

	// 点数計算
	CalculationRank();

	// ロゴの生成
	CScene2d*pLogo = CScene2d::Create();
	pLogo->SetPriority(OBJTYPE_UI);// プライオリティ
	pLogo->SetPos(LOGO_POS);       // 座標
	pLogo->SetSize(LOGO_SIZE);     // サイズ
	pLogo->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_RESULT_LOGO));// テクスチャ

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
					// リザルトボードの生成
					CResultBoard::Create(nCntPlayer, boardPos);

					boardPos.x += RESULT_BOARD_SPACE;

					if (m_apRankUI[nCntPlayer] != NULL)
					{
						m_apRankUI[nCntPlayer]->Uninit();
						m_apRankUI[nCntPlayer] = NULL;
					}
				}
				m_bBoard = true;
			}
			else
			{// 画面遷移
				CManager::GetFade()->SetFade(CManager::MODE_TITLE);
			}
			
			// SEの再生
			CManager::GetSound()->Play(CSound::LABEL_SE_ENTER);

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
// [GetRank] その順位のプレイヤー番号を取得
// Author : AYANOKUDO
// 引数: 
// 返り値 :プレイヤーの番号
//=============================
int CResult::GetRank(int nRank)
{
    int nPlayerNum = 0;// プレイヤーの番号
    int aPoint = m_resultPoint[0].nPoint;
    // 順位
    for (int nCnt = 0; nCnt < MAX_PLAYER_NUM; nCnt++)
    {
        if (aPoint>=m_resultPoint[nCnt].nPoint)
        {
            nPlayerNum = nCnt;// プレイヤーの番号を保存
            aPoint = m_resultPoint[nCnt].nPoint;// 一番低いポイントを保存
        }
    }
    return nPlayerNum;
}

//=============================
// プレイヤーのモーションを変える
//=============================
void CResult::ChagePlayerMotion(void)
{

	if (m_nCntFallTime == 0 && m_nActionRank == 1)
	{
		// 一位発表時のSE再生
		CManager::GetSound()->Play(CSound::LABEL_SE_RESULT_WIN);
	}

	// カウントを進める
	m_nCntFallTime++;

	if (PLAYER_FALL_COUNT <= m_nCntFallTime)
	{// 一定のカウントで
	 // カウントのリセット
		
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

					// SE
					CManager::GetSound()->Play(CSound::LABEL_SE_MISS);

					m_nCntFallTime = 0;
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

					// SE
					CManager::GetSound()->Play(CSound::LABEL_SE_MISS);
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
		else if (m_nActionRank == 1)
		{
			m_nCntFallTime = 0;
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
			m_apRankUI[nCntPlayer] = CRankUI::Create(D3DXVECTOR3(playerPos.x, playerPos.y + RANK_UI_HEGHT, playerPos.z), m_apPlayer[nCntPlayer]->GetRank());
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
			playerPos.y += ((2000.0f -PLAYER_CENTER_HEIGHT - 20) - playerPos.y)*0.05f;

			m_apPlayer[nCntPlayer]->SetPos(playerPos);
		}
	}

}
