////////////////////////////////////////////////////
//
//    カメラクラスの処理[camera.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "mouse.h"
#include "joypad.h"

//******************************
// マクロ定義
//******************************
#define CAMERA_DISTANCE 850.0f                               // カメラと対象の距離
#define CAMERA_VIEW_MAX 100000.0f                            // カメラの描画距離(遠)
#define CAMERA_VIEW_MIN 10.0f                                // カメラの描画距離(近)
#define CAMERA_FOV_BASE D3DXToRadian(45.0f)                  // 視野角
#define CAMERA_FOV_RATE 0.05f                                // 視野角変化時の係数
#define CAMERA_MOVE_SPEED_MAX 0.04f                          // カメラ操作感度最大値
#define DAMERA_THETA_RATE 0.05f                              // カメラのシータ調整時の係数
#define CAMERA_THETA_BASE D3DXToRadian(75.0f)                // カメラのファイ(高さ)の基本角度
#define DAMERA_PHI_RATE 0.01f                                // カメラのファイ(高さ)調整時の係数
#define THETA_DIFFERENCE D3DXToRadian(60)                    // シータとシータの目標値の差の最大

// CPUに追従替えるに切り替えるマクロ
#define CPU_CAMERA
//#undef  CPU_CAMERA

//******************************
// 静的メンバ変数宣言
//******************************
CCamera*CCamera::m_pCamera = NULL;

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


	m_fRad   = 0.0f; // 目標からの距離
	m_fTheta = 0.0f; // 角度シータ
	m_fPhi   = 0.0f; // 角度ファイ
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

	m_pCamera = new CCamera;
	m_pCamera->Init();


	return m_pCamera;
}


//******************************
// 初期化処理
//******************************
HRESULT CCamera::Init(void)
{
	// 変数の初期化

	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);      // 上方向ベクトル

	m_fRad = CAMERA_DISTANCE;     // 距離
	m_fTheta = D3DXToRadian(90);  // 角度シータ
	m_fPhi = CAMERA_THETA_BASE;   // 角度ファイ

	// 球面座標の設定
	m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
	m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
	m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);

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
	m_fTheta -= CManager::GetMouse()->GetMouseMove().x;
	m_fPhi -= CManager::GetMouse()->GetMouseMove().y;

	// 球面座標の設定
	m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
	m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
	m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);
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
	D3DXMatrixIdentity(&m_pCamera->m_mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_pCamera->m_mtxView, &m_pCamera->m_posV, &m_pCamera->m_posR, &m_pCamera->m_vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_pCamera->m_mtxView);

	//プロジェクトマトリックスの初期化
	D3DXMatrixIdentity(&m_pCamera->m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_pCamera->m_mtxProjection,
		m_fFov, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, CAMERA_VIEW_MIN, CAMERA_VIEW_MAX);
	
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera->m_mtxProjection);
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 1.0f, 0);
}