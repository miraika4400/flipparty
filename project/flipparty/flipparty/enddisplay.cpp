//=============================================================================
//
// enddisplay処理 [enddisplay.cpp]
// Author : 山田陵太
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enddisplay.h"
#include "resource_texture.h"
#include "manager.h"
#include "sound.h"
#include "rule_base.h"
#include "game.h"
#include "rule_manager.h"

#define DISPLAY_SIZE D3DXVECTOR3(100.0f,50.0f,0.0f)
#define SIPLAY_SIZE_DIST DISPLAY_SIZE * 2

//=============================================================================
//コンストラクタ
//=============================================================================
CEndDisplay::CEndDisplay() :CScene2d(CScene::OBJTYPE_SYSTEM)
{
	m_nCntTime = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CEndDisplay::~CEndDisplay()
{
}

//=============================================================================
//クリエイト処理
//=============================================================================
CEndDisplay * CEndDisplay::Create(void)
{
	//
	CEndDisplay *pEndDisplay = NULL;

	//インスタンス生成
	pEndDisplay = new CEndDisplay;

	if (pEndDisplay)
	{
		pEndDisplay->Init();
	}

	return pEndDisplay;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CEndDisplay::Init(void)
{
	CScene2d::Init();
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	SetSize(DISPLAY_SIZE);
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_ICON_FLAGRACING));
	
	//再生しているすべての音声を停止
	CManager::GetSound()->Stop();

	//終了音を再生
	CManager::GetSound()->Play(CSound::LABEL_SE_GAME_END);
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CEndDisplay::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CEndDisplay::Update(void)
{
	m_nCntTime++;

	if (m_nCntTime == 120)
	{
		//ミニリザルトへ移行
		CGame::GetRuleManager()->GetRule()->SetRuleState(CRuleBase::RULE_STATE_MINI_RESULT);
		Uninit();

		return;
	}
	else
	{
		//サイズを取得
		D3DXVECTOR3 size = GetSize();

		size += (SIPLAY_SIZE_DIST - size) * 0.1f;

		//サイズを設定
		SetSize(size);
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CEndDisplay::Draw(void)
{
	CScene2d::Draw();
}
