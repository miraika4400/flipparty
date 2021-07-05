////////////////////////////////////////////////////
//
//    カメラクラスの処理[camera.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "camera_base.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "mouse.h"
#include "joypad.h"

//******************************
// マクロ定義
//******************************
#define CAMERA_INIT_POS D3DXVECTOR3(0.0f,0.0f,500.0f)
#define CAMERA_VIEW_MAX 100000.0f                            // カメラの描画距離(遠)
#define CAMERA_VIEW_MIN 10.0f                                // カメラの描画距離(近)
#define CAMERA_FOV_BASE D3DXToRadian(45.0f)                  // 視野角

//******************************
// 静的メンバ変数宣言
//******************************

//******************************
// コンストラクタ
//******************************
CCamera::CCamera()
{
	// 変数のクリア
	m_posV = { 0.0f,0.0f,0.0f };
	m_posR = { 0.0f,0.0f,0.0f };
	m_vecU = { 0.0f,0.0f,0.0f };
	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixIdentity(&m_mtxView);
	m_fFov = 0.0f;
}

//******************************
// デストラクタ
//******************************
CCamera::~CCamera()
{
}

//******************************
// クリエイト
//******************************
CCamera * CCamera::Create(void)
{
	CCamera * pCamera = new CCamera;
	pCamera->Init();

	return pCamera;
}


//******************************
// 初期化処理
//******************************
HRESULT CCamera::Init(void)
{
	// 変数の初期化

	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);      // 上方向ベクトル
	m_posV = CAMERA_INIT_POS; // 位置

	m_fFov = CAMERA_FOV_BASE; //視野角

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CCamera::Uninit(void)
{
	delete this;
}

//******************************
// 更新処理
//******************************
void CCamera::Update(void)
{
}

//******************************
// カメラのセット
//******************************
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIXA16 matWorld;

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクトマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		m_fFov, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, CAMERA_VIEW_MIN, CAMERA_VIEW_MAX);
	
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}