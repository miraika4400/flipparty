//===================================================
//
//   制限時間クラスの処理[time.cpp]
//    Author:増澤 未来
//
//====================================================

//**********************************
//インクルード
//**********************************
#include "timelimit.h"
#include "number.h"
#include "manager.h"
#include "rule_base.h"
#include "game.h"
#include "rule_manager.h"

//**********************************
//マクロ定義
//**********************************
#define UI_HEIGHT 80.0f                             // 位置*Y軸
#define NUMBER_SIZE D3DXVECTOR3(20.0f, 20.0f, 0.0f) // サイズ
#define NUMBER_SPACE 40.0f                          // 数字間の間隔
#define ONE_SECOND_COUNT 60                         // 一秒のカウント(フレーム)数

//**********************************
//静的メンバ変数宣言
//**********************************

//==================================
// コンストラクタ
//==================================
CTimeLimit::CTimeLimit() :CScene(OBJTYPE_UI)
{
	// ナンバーのクリア
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_nLimitTime = 0;
	m_nCntTime = 0;
	m_bIsTimeCount = false;
}

//==================================
// デストラクタ
//==================================
CTimeLimit::~CTimeLimit()
{
}

//==================================
// クリエイト
//==================================
CTimeLimit * CTimeLimit::Create(int nLimitTime)
{
	// メモリの確保
	CTimeLimit *pTime = new CTimeLimit;

	// 初期化処理
	pTime->Init();
	pTime->m_nLimitTime = nLimitTime;

	// オブジェクトタイプの設定
	pTime->SetPriority(OBJTYPE_UI);

	return pTime;
}

//==================================
// 初期化処理
//==================================
HRESULT CTimeLimit::Init(void)
{
	float posX = 0 - ((float)(MAX_TIME_NUM - 1) * NUMBER_SPACE) / 2;

	// 最大分ループ
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_NUM; nCntDigit++)
	{
		// ナンバー生成
		m_apNumber[nCntDigit] = CNumber::Create(0,
			D3DXVECTOR3((SCREEN_WIDTH/2) + posX, UI_HEIGHT, 0.0f),
			NUMBER_SIZE,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		posX += NUMBER_SPACE;
	}

	// カウント初期化
	m_nCntTime = 0;

	//更新フラグの初期化
	m_bIsTimeCount = true;
	return S_OK;
}

//==================================
// 終了処理
//==================================
void CTimeLimit::Uninit(void)
{
	// 最大分ループ
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_NUM; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{
			// 終了処理
			m_apNumber[nCntDigit]->Uninit();
			delete m_apNumber[nCntDigit];
			m_apNumber[nCntDigit] = NULL;
		}
	}

	// 開放処理
	Release();
}

//==================================
// 更新処理
//==================================
void CTimeLimit::Update(void)
{
	if (CGame::GetRuleManager()->GetRule()->GetRuleState() == CRuleBase::RULE_STATE_GAME)
	{
		if (m_nLimitTime > 0)
		{
			//trueの時のみカウントを進める
			if (m_bIsTimeCount)
			{
				// カウントを進める
				m_nCntTime++;
				// カウントが一定以上の時
				if (m_nCntTime >= ONE_SECOND_COUNT)
				{
					// カウントの初期化
					m_nCntTime = 0;
					// 制限時間を減らす
					m_nLimitTime--;

					if (m_nLimitTime <= 0)
					{
						m_nLimitTime = 0;
					}
				}
			}
			// 最大分ループ
			for (int nCntDigit = 0; nCntDigit < MAX_TIME_NUM; nCntDigit++)
			{
				// ナンバーのアップデート
				m_apNumber[nCntDigit]->Update();

				// 各桁の計算
				m_apNumber[nCntDigit]->SetNumber((m_nLimitTime % (int)(powf(10.0f, (MAX_TIME_NUM - nCntDigit)))) / (float)(powf(10.0, (MAX_TIME_NUM - nCntDigit - 1))));
			}
		}
	}
}

//==================================
// 描画処理
//==================================
void CTimeLimit::Draw(void)
{
	if (CGame::GetRuleManager()->GetRule()->GetRuleState() == CRuleBase::RULE_STATE_GAME)
	{
		// 最大分ループ
		for (int nCntDigit = 0; nCntDigit < MAX_TIME_NUM; nCntDigit++)
		{
			m_apNumber[nCntDigit]->Draw();
		}
	}
}
