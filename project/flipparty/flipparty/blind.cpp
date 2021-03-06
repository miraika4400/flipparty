////////////////////////////////////////////////////
//
//    blindクラスの処理[blind.cpp]
//    Author:山田 陵太
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "blind.h"
#include "manager.h"
#include "renderer.h"
#include "resource_texture.h"

//===================================
// マクロ定義
//===================================
#define BLIND_START_POS D3DXVECTOR3(0.0f, 220.0f, -100.0f)	//開始時のブラインドの位置
#define BLIND_POS D3DXVECTOR3(0.0f, -20.0f, 0.0f)			//ブラインドの位置
#define BLIND_SIZE D3DXVECTOR3(100.0f, 60.0f, 0.0f)			//ブラインドのサイズ
#define BLIND_MOVE 5.0f										//移動量

//===================================
// コンストラクタ
//===================================
CBlind::CBlind() : CScene3d(OBJTYPE_BG)
{
	m_nTime = 0;
	m_state = BLIND_STATE_MOVE;
	m_nMoveStartTime = 0;
	m_pBlackPolygon = NULL;
}

//===================================
// デストラクタ
//===================================
CBlind::~CBlind()
{
}

//===================================
// クリエイト関数
//===================================
CBlind * CBlind::Create(int nTime, int nStartTime)
{
	// ポインタ変数
	CBlind *pBlind = NULL;

	//インスタンス生成
	pBlind = new CBlind;

	if (pBlind)
	{
		//初期化処理
		pBlind->Init();
		pBlind->SetTime(nTime);
		pBlind->m_nMoveStartTime = nStartTime;
	}

	return pBlind;
}

//===================================
// 初期化処理
//===================================
HRESULT CBlind::Init(void)
{
	//初期化処理
	CScene3d::Init();

	//位置の設定
	SetPos(BLIND_START_POS);

	//サイズの設定
	SetSize(BLIND_SIZE);

	//描画順の設定
	SetPriority(CScene::OBJTYPE_MOTION);

	//テクスチャの設定
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_BLIND));

	//黒ポリゴンの生成
	m_pBlackPolygon = CScene3d::Create(
		D3DXVECTOR3(BLIND_START_POS.x, BLIND_START_POS.y, BLIND_START_POS.z - 1.0f), 
		BLIND_SIZE);
	m_pBlackPolygon->SetPriority(OBJTYPE_BG);


	//黒ポリゴンの色設定
	if (m_pBlackPolygon)
	{
		m_pBlackPolygon->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}

	return S_OK;
}

//===================================
// 終了処理
//===================================
void CBlind::Uninit(void)
{
	//終了処理
	CScene3d::Uninit();
}

//===================================
// 更新処理
//===================================
void CBlind::Update(void)
{
	//更新処理
	CScene3d::Update();

	if (m_state == BLIND_STATE_MOVE)
	{
		//移動開始タイムより小さくなった時
		if (m_nTime <= m_nMoveStartTime)
		{
			//位置取得
			D3DXVECTOR3 pos = GetPos();

			//移動量を与える
			pos.y -= BLIND_MOVE;

			//目的の位置に到達したら
			if (pos.y <= BLIND_POS.y)
			{
				//位置を修正
				pos.y = BLIND_POS.y;

				//移動をやめる
				m_state = BLIND_STATE_NORMAL;
			}

			//位置の設定
			SetPos(pos);

			//黒ポリゴンの設定
			if (m_pBlackPolygon)
			{
				m_pBlackPolygon->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z - 1.0f));
			}
		}
	}
}

//===================================
// 描画処理
//===================================
void CBlind::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	//Zバッファ設定の保存用変数
	DWORD dwCurZTest = 0;
	
	if (m_state == BLIND_STATE_NORMAL)
	{
		//Zバッファの設定を一時保存
		pDevice->GetRenderState(D3DRS_ZFUNC, &dwCurZTest);

		//ステンシルテストの設定
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);				//ステンシルテストを有効にする
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x03);				//ステンシルバッファへ反映する参照値の設定
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);			//マスクの設定（ビットを削らないように指定）
		pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);	//0xffffffffにする
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATER);		//ステンシルテストの判定を必ず成功するように指定

		//テストの結果の組み合わせ設定
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	//ステンシル・Zテストともに失敗した場合
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);	//ステンシルのみ成功した場合
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	//両方とも成功した場合
	}

	//ポリゴンの描画
	CScene3d::Draw();

	if (m_state == BLIND_STATE_NORMAL)
	{
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);	//ステンシルテストを無効にする
		pDevice->SetRenderState(D3DRS_ZFUNC, dwCurZTest);		//Zバッファの設定を戻す
	}
}
