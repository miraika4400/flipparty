//=============================================================================
//
// stratcountヘッダ [stratcount.cpp]
// Author : 山田陵太
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "startcount.h"
#include "number.h"
#include "manager.h"
#include "sound.h"
#include "resource_texture.h"
#include "scene2d.h"
#include "game.h"
#include "rule_manager.h"
#include "rule_base.h"
#include "game.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define LIMIT_TIME 3
#define STRAT_NUMBER_SIZE_X 100.0f
#define STRAT_NUMBER_SIZE_Y 100.0f
#define STRAT_ICON_SIZE_X 200.0f
#define STRAT_ICON_SIZE_Y 50.0f 
#define STRAT_ICON_SIZE_DIST (D3DXVECTOR3(STRAT_ICON_SIZE_X * 2, STRAT_ICON_SIZE_Y *2, 0.0f))
#define SCALE_RATE 0.1f
#define NUMBER_UPDATE_TIME 1	//ナンバークラスを更新する最終時間
#define NUMBER_DELETE_TIME 0	//ナンバークラスを削除する残り時間
#define SCENE_DELETE_TIME -2	//2Dポリゴンの削除する残り時間

//=============================================================================
//コンストラクタ
//=============================================================================
CStratCount::CStratCount() :CScene(CScene::OBJTYPE_SYSTEM)
{
	m_pNumber = NULL;
	m_pScene2D = NULL;
	m_nCntTime = 0;
	m_nLimitTime = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CStratCount::~CStratCount()
{
}

//=============================================================================
//クリエイト処理
//=============================================================================
CStratCount * CStratCount::Create(void)
{
	CStratCount *pStratCount = NULL;

	//インスタンス生成
	pStratCount = new CStratCount;

	if (pStratCount)
	{
		//初期化
		pStratCount->Init();
		//プライオリティの設定
		pStratCount->SetPriority(CScene::OBJTYPE_SYSTEM);
	}

	return pStratCount;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CStratCount::Init(void)
{
	//制限の初期化
	m_nLimitTime = LIMIT_TIME;

	m_nCntTime = 0;

	//ナンバーの生成
	m_pNumber = CNumber::Create(
		m_nLimitTime,
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(STRAT_NUMBER_SIZE_X, STRAT_NUMBER_SIZE_Y, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//カウント音の再生
	CManager::GetSound()->Play(CSound::LABEL_SE_COUNT);
	
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CStratCount::Uninit(void)
{
	//ナンバーの削除
	if (m_pNumber)
	{
		//終了処理
		m_pNumber->Uninit();

		//メモリ削除
		delete m_pNumber;

		//メモリのクリア
		m_pNumber = NULL;
	}

	//自身を破棄
	CScene::Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CStratCount::Update(void)
{
	//カウントを増やす
	m_nCntTime++;

	if (m_nCntTime >= 60)
	{
		//カウントを初期化
		m_nCntTime = 0;

		//制限時間を減らす
		m_nLimitTime--;

		if (m_pNumber && m_nLimitTime >= NUMBER_UPDATE_TIME)
		{
			//変更された値を与える
			m_pNumber->SetNumber(m_nLimitTime);

			//カウント音の再生
			CManager::GetSound()->Play(CSound::LABEL_SE_COUNT);
		}
	}

	if (m_nLimitTime <= SCENE_DELETE_TIME)
	{
		//ルールの状態をゲームへ設定
		CGame::GetRuleManager()->GetRule()->SetRuleState(CRuleBase::RULE_STATE_GAME);

		//ポリゴンの終了
		m_pScene2D->Uninit();

		//終了処理
		Uninit();

		return;
	}
	else if (m_nLimitTime <= NUMBER_DELETE_TIME)
	{
		//ナンバーの削除
		if (m_pNumber)
		{
			//終了処理
			m_pNumber->Uninit();

			//メモリ削除
			delete m_pNumber;

			//メモリのクリア
			m_pNumber = NULL;
		}
		if (!m_pScene2D)
		{
			//ポリゴン生成
			m_pScene2D = CScene2d::Create();

			//サイズの設定
			m_pScene2D->SetSize(D3DXVECTOR3(STRAT_ICON_SIZE_X, STRAT_ICON_SIZE_Y, 0.0f));

			//テクスチャの設定
			m_pScene2D->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_STRAT_ICON));

			//スタート音をここで再生予定
			//カウント音の再生
			CManager::GetSound()->Play(CSound::LABEL_SE_START);
		}
		else
		{
			//サイズを取得
			D3DXVECTOR3 size = m_pScene2D->GetSize();

			//目的サイズになるように加算
			size += (STRAT_ICON_SIZE_DIST - size) * SCALE_RATE;

			//サイズの設定
			m_pScene2D->SetSize(size);
		}
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CStratCount::Draw(void)
{
	if (m_pNumber)
	{
		//描画処理
		m_pNumber->Draw();
	}
}
