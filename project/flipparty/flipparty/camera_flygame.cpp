////////////////////////////////////////////////////
//
//    カメラクラスの処理[camera.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "camera_flygame.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "mouse.h"
#include "joypad.h"

//******************************
// マクロ定義
//******************************
#define CAMERA_POS D3DXVECTOR3(0.0f,0.0f,500.0f)

//******************************
// 静的メンバ変数宣言
//******************************

//******************************
// コンストラクタ
//******************************
CFlyGameCamera::CFlyGameCamera()
{
	// 変数のクリア
}

//******************************
// デストラクタ
//******************************
CFlyGameCamera::~CFlyGameCamera()
{
}

//******************************
// クリエイト
//******************************
CFlyGameCamera * CFlyGameCamera::Create(void)
{
	CFlyGameCamera * pCamera = new CFlyGameCamera;
	pCamera->Init();

	return pCamera;
}


//******************************
// 初期化処理
//******************************
HRESULT CFlyGameCamera::Init(void)
{
	CCamera::Init();

	// 位置の設定
	m_posV = CAMERA_POS;

	return S_OK;
}

//******************************
// 更新処理
//******************************
void CFlyGameCamera::Update(void)
{
}

//******************************
// カメラのセット
//******************************
void CFlyGameCamera::SetCamera(void)
{
	CCamera::SetCamera();

	//// デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//D3DXMATRIXA16 matWorld;
	//
	////ビューマトリックスの初期化
	//D3DXMatrixIdentity(GetViewMtx());
	////ビューマトリックスの作成
	//D3DXMatrixLookAtLH(GetViewMtx(), &this->m_posV, &this->m_posR, &this->m_vecU);
	////ビューマトリックスの設定
	//pDevice->SetTransform(D3DTS_VIEW, GetViewMtx());
	//
	////プロジェクトマトリックスの初期化
	//D3DXMatrixIdentity(GetProjectionMtx());
	//
	////プロジェクションマトリックスの作成*並行投影
	//D3DXMatrixOrthoLH(GetProjectionMtx(), ((float)SCREEN_WIDTH)*0.5f, ((float)SCREEN_HEIGHT)*0.5f, 10, 100000);
	//
	////プロジェクションマトリックスの設定
	//pDevice->SetTransform(D3DTS_PROJECTION, GetProjectionMtx());
	//pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 1.0f, 0);
}