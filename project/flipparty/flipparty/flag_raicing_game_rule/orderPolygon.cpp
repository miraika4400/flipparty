//=============================================================================
//
// 指示ポリゴンヘッダ [orderpolygon.cpp]
// Author : 山田　陵太
//
//=============================================================================

//******************************
// インクルード
//******************************
#include "orderPolygon.h"
#include "manager.h"
#include "resource_texture.h"
#include "billboard.h"

//******************************
// マクロ定義
//******************************
#define ODER_POLYGON_LEFT_POS D3DXVECTOR3(50.0f,35.0f,100.0f)	//左のポリゴンの位置
#define ODER_POLYGON_RIGHT_POS D3DXVECTOR3(-50.0f,35.0f,100.0f)	//右のポリゴンの位置
#define ODER_POLYGON_SIZE D3DXVECTOR3(10.0f,10.0f,0.0f)			//ポリゴンのサイズ

D3DXVECTOR3 pos[CFlipper::FLIPPER_TYPE_MAX] =
{
	ODER_POLYGON_LEFT_POS,ODER_POLYGON_RIGHT_POS
};
//******************************
// 静的メンバ変数宣言
//******************************
bool COrderPolygon::m_bUse = true;

//******************************
// コンストラクタ
//******************************
COrderPolygon::COrderPolygon():CScene(CScene::OBJTYPE_UI)
{
	//メンバ変数のクリア
	ZeroMemory(&m_Order, sizeof(m_Order));
}

//******************************
// デストラクタ
//******************************
COrderPolygon::~COrderPolygon()
{
}

//******************************
// クリエイト
//******************************
COrderPolygon * COrderPolygon::Crate(void)
{
	//指示ポリゴンクラスのポインタ変数
	COrderPolygon *pOrderPolygon = NULL;

	//インスタンス生成
	pOrderPolygon = new COrderPolygon;

	if (pOrderPolygon)
	{
		//初期化処理
		pOrderPolygon->Init();
	}

	return pOrderPolygon;
}

//******************************
// 初期化処理
//******************************
HRESULT COrderPolygon::Init(void)
{
	for (int nCntPoygon = 0; nCntPoygon < CFlipper::FLIPPER_TYPE_MAX; nCntPoygon++)
	{
		//左右のポリゴンを生成
		m_Order[nCntPoygon].pOrderBillboard = CBillboard::Create(pos[nCntPoygon], ODER_POLYGON_SIZE);
		m_Order[nCntPoygon].bIsDraw = false;
	}
	
	m_bUse = true;

	return S_OK;
}

//******************************
// 終了処理
//******************************
void COrderPolygon::Uninit(void)
{
	for (int nCntPoygon = 0; nCntPoygon < CFlipper::FLIPPER_TYPE_MAX; nCntPoygon++)
	{
		//左右のポリゴンを削除
		if (m_Order[nCntPoygon].pOrderBillboard)
		{
			//終了処理
			m_Order[nCntPoygon].pOrderBillboard->Uninit();

			//メモリ削除
			delete m_Order[nCntPoygon].pOrderBillboard;

			//メモリのクリア
			m_Order[nCntPoygon].pOrderBillboard = NULL;
		}
	}

	//自身の削除
	Release();
}

//******************************
// 更新処理
//******************************
void COrderPolygon::Update(void)
{
}

//******************************
// 描画処理
//******************************
void COrderPolygon::Draw(void)
{
	if (m_bUse)
	{
		for (int nCntPoygon = 0; nCntPoygon < CFlipper::FLIPPER_TYPE_MAX; nCntPoygon++)
		{
			if (m_Order[nCntPoygon].bIsDraw)
			{
				//ポリゴンを描画
				m_Order[nCntPoygon].pOrderBillboard->Draw();
			}
		}
	}
}

//******************************
// 描画セット処理
//******************************
void COrderPolygon::SetDraw(CFlipper::FLIPPER_TYPE flipperState, CFlipper::FLIPPER_STATE state)
{
	//左手の場合
	if (flipperState == CFlipper::FLIPPER_TYPE_LEFT)
	{
		//左側を表示、右側を非表示
		m_Order[CFlipper::FLIPPER_TYPE_LEFT].bIsDraw = true;
		m_Order[CFlipper::FLIPPER_TYPE_RIGHT].bIsDraw = false;

		//上げる場合
		if (state == CFlipper::FLIPPERSTATE_UP)
		{
			m_Order[flipperState].pOrderBillboard->BindTexture
			(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_LEFT_UP));
		}
		//下げる場合
		else if (state == CFlipper::FLIPPERSTATE_DOWN)
		{
			m_Order[flipperState].pOrderBillboard->BindTexture
			(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_LEFT_DOWN));
		}
		
	}
	//右手の場合
	else if (flipperState == CFlipper::FLIPPER_TYPE_RIGHT)
	{
		//右側を表示、左側を非表示
		m_Order[CFlipper::FLIPPER_TYPE_LEFT].bIsDraw = false;
		m_Order[CFlipper::FLIPPER_TYPE_RIGHT].bIsDraw = true;

		//上げる場合
		if (state == CFlipper::FLIPPERSTATE_UP)
		{
			m_Order[flipperState].pOrderBillboard->BindTexture
			(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_RIGHT_UP));
		}
		//下げる場合
		else if (state == CFlipper::FLIPPERSTATE_DOWN)
		{
			m_Order[flipperState].pOrderBillboard->BindTexture
			(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_RIGHT_DOWN));
		}
	}
}
