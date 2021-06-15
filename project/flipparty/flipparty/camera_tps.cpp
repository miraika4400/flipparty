////////////////////////////////////////////////////
//
//    カメラクラスの処理[camera.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "camera_tps.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "mouse.h"
#include "joypad.h"

//******************************
// マクロ定義
//******************************
#define CAMERA_DISTANCE 200.0f                               // カメラと対象の距離
#define CAMERA_THETA_BASE D3DXToRadian(75.0f)                // カメラのファイ(高さ)の基本角度

//******************************
// 静的メンバ変数宣言
//******************************

//******************************
// コンストラクタ
//******************************
CTpsCamera::CTpsCamera()
{
	m_fRad   = 0.0f; // 目標からの距離
	m_fTheta = 0.0f; // 角度シータ
	m_fPhi   = 0.0f; // 角度ファイ
}

//******************************
// デストラクタ
//******************************
CTpsCamera::~CTpsCamera()
{
}

//******************************
// クリエイト
//******************************
CTpsCamera * CTpsCamera::Create(void)
{
	CTpsCamera * pCamera = new CTpsCamera;
	pCamera->Init();

	return pCamera;
}


//******************************
// 初期化処理
//******************************
HRESULT CTpsCamera::Init(void)
{
	// カメラクラスの初期化
	CCamera::Init();

	// 変数の初期化
	m_fRad = CAMERA_DISTANCE;     // 距離
	m_fTheta = D3DXToRadian(90);  // 角度シータ
	m_fPhi = CAMERA_THETA_BASE;   // 角度ファイ
	
	// 球面座標の設定
	m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
	m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
	m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);
	return S_OK;
}

//******************************
// 更新処理
//******************************
void CTpsCamera::Update(void)
{
	m_fTheta -= CManager::GetMouse()->GetMouseMove().x;
	m_fPhi -= CManager::GetMouse()->GetMouseMove().y;
	
	// 球面座標の設定
	m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
	m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
	m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);
}