//===================================================
//
//    背景クラスの処理[bg.cpp]
//    Author:増澤 未来
//
//====================================================

//**********************************
//インクルード
//**********************************
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "game.h"
#include "resource_model.h"

//*****************************
// マクロ定義
//*****************************
#define SIZE       D3DXVECTOR3(110.0f,110.0f ,110.0f) // サイズ
#define ADD_ROT D3DXVECTOR3(0.0f,0.0005f,0.0f)         // ゆっくり回す

//*****************************
// 静的メンバ変数宣言
//*****************************

//==================================
// コンストラクタ
//==================================
CBg::CBg() : CModel(OBJTYPE_BG)
{
	
}

//==================================
// デストラクタ
//==================================
CBg::~CBg()
{
}

//==================================
// クリエイト
//==================================
CBg * CBg::Create(void)
{
	// メモリの確保
	CBg *pBg = new CBg;
	// 初期化処理
	pBg->Init();

	return pBg;
}


//==================================
// 初期化処理
//==================================
HRESULT CBg::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// モデル割り当て
	BindModel(CResourceModel::GetModel(CResourceModel::MODEL_BG));

	// サイズの設定
	SetSize(SIZE);
	
	return S_OK;
}

//==================================
// 終了処理
//==================================
void CBg::Uninit(void)
{
	CModel::Uninit();
}

//==================================
// 更新処理
//==================================
void CBg::Update(void)
{
	// ゆっくり回す
	SetRot(GetRot() + ADD_ROT);
}

//==================================
// 描画処理
//==================================
void CBg::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	// ライトを消す
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	CModel::Draw();

	// ライトをつける
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
