//=============================================================================
//
// add_point_displayヘッダ [add_point_display.cpp]
// Author : 山田　陵太
//
//=============================================================================
#include "add_point_display.h"
#include "resource_texture.h"
#include "count_selection.h"
#include "manager.h"
#include "sound.h"
#include "game.h"
#include "rule_base.h"
#include "rule_manager.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define U_ONE_FRAME 1.0f / MAX_PLAYER_NUM
#define V_ONE_FRAME 1.0f / POINT_DISPLAY_TYPE_MAX
#define DISPLAY_SIZE D3DXVECTOR3(80.0f,40.0f,0.0f)

//=============================================================================
//コンストラクタ
//=============================================================================
CAddPointDisplay::CAddPointDisplay()
{
	m_displayType = POINT_DISPLAY_TYPE_3PT;
	m_IsDraw = false;
	m_nPlayerNumber = 0;
	m_nShoeCounter = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CAddPointDisplay::~CAddPointDisplay()
{
}

//=============================================================================
//クリエイト処理
//=============================================================================
CAddPointDisplay * CAddPointDisplay::Create(int nPlayerNumber)
{
	CAddPointDisplay *pPointDisplay = NULL;

	//インスタンス生成
	pPointDisplay = new CAddPointDisplay;

	if (pPointDisplay)
	{
		pPointDisplay->m_nPlayerNumber = nPlayerNumber;
		pPointDisplay->Init();
	}
	return pPointDisplay;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CAddPointDisplay::Init(void)
{
	CScene2d::Init();

	//サイズ
	SetSize(DISPLAY_SIZE);

	//テクスチャの設定
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ADD_POINT_DISPLAY));
	
	D3DXVECTOR2 uvPos[4];
	uvPos[0] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME, m_displayType * V_ONE_FRAME);
	uvPos[1] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME + U_ONE_FRAME, m_displayType * V_ONE_FRAME);
	uvPos[2] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME, m_displayType * V_ONE_FRAME + V_ONE_FRAME);
	uvPos[3] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME + U_ONE_FRAME, m_displayType * V_ONE_FRAME + V_ONE_FRAME);

	//UV座標の設定
	SetTextureUV(uvPos);

	//描画順を設定
	SetPriority(OBJTYPE_UI);

	//テクスチャタイプを設定
	m_displayType = POINT_DISPLAY_TYPE_3PT;

	//描画をオフにする
	m_IsDraw = false;

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CAddPointDisplay::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CAddPointDisplay::Update(void)
{
	CScene2d::Update();

	if (m_IsDraw)
	{
		if (m_nShoeCounter == 40)
		{
			m_IsDraw = false;
		}

		m_nShoeCounter++;
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CAddPointDisplay::Draw(void)
{
	if (m_IsDraw)
	{
		CScene2d::Draw();
	}
}

//=============================================================================
//ディスプレイ設定処理
//=============================================================================
void CAddPointDisplay::SetDisplay(POINT_DISPLAY_TYPE displayType)
{
	if (CGame::GetRuleManager()->GetRule()->GetRuleState() == CRuleBase::RULE_STATE_GAME)
	{
		m_displayType = displayType;

		m_IsDraw = true;
		m_nShoeCounter = 0;
		D3DXVECTOR2 uvPos[4];
		uvPos[0] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME, m_displayType * V_ONE_FRAME);
		uvPos[1] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME + U_ONE_FRAME, m_displayType * V_ONE_FRAME);
		uvPos[2] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME, m_displayType * V_ONE_FRAME + V_ONE_FRAME);
		uvPos[3] = D3DXVECTOR2(m_nPlayerNumber * U_ONE_FRAME + U_ONE_FRAME, m_displayType * V_ONE_FRAME + V_ONE_FRAME);

		//UV座標の設定
		SetTextureUV(uvPos);

		if (m_displayType == POINT_DISPLAY_TYPE_MISS)
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_MISS);
		}
		else
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_OK);
		}
	}
}