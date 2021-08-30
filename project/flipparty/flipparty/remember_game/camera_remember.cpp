//=============================================================================
//
// 記憶ゲームのカメラクラス [camera_remember.cpp]
// Author : AYANO KUDO
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "camera_remember.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CCameraRemember* CCameraRemember::m_pInsutance = nullptr;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_POS_V_REMEMBER D3DXVECTOR3(0.0f,0.0f, 150.0f)  // 位置
#define CAMERA_POS_R_REMEMBER D3DXVECTOR3(0.0f, 15.0f, 0.0f)  // 注視点

#define CAMERA_MOVE_SPEED (20)// カメラの移動速度
#define CAMERA_POS_X (150)

//=============================================================================
// [CreCCameraRememberate]オブジェクトの生成
//=============================================================================
CCameraRemember::CCameraRemember()
{

}

//=============================================================================
// [Create]オブジェクトの生成
//=============================================================================
CCameraRemember::~CCameraRemember()
{

}

//=============================================================================
// [Create]オブジェクトの生成
//=============================================================================
CCameraRemember * CCameraRemember::Create(void)
{
    m_pInsutance = new CCameraRemember;
    
    m_pInsutance->Init();

    return m_pInsutance;
}

//=============================================================================
// [Init]初期化処理
//=============================================================================
HRESULT CCameraRemember::Init(void)
{
    CCamera::Init();

    m_nDist = false;// 移動中かどうか
    m_fCameraDest = 0;

    // 位置の設定
    m_posV = CAMERA_POS_V_REMEMBER;
    m_posR = CAMERA_POS_R_REMEMBER;

    return S_OK;
}

//=============================================================================
// [Uninit]更新処理
//=============================================================================
void CCameraRemember::Update(void)
{
    // カメラの移動
    if (m_nDist > 0)
    {
        CameraMove();
        m_nDist--;
    }
}

//=============================================================================
// [SetCamera]カメラのセット
//=============================================================================
void CCameraRemember::SetCamera(void)
{
    CCamera::SetCamera();
}

//=============================================================================
// [SetDest]カメラの移動係数の設定
//=============================================================================
void CCameraRemember::SetDest(float fDest)
{
    m_fCameraDest = (fDest - m_posV.x) / CAMERA_MOVE_SPEED;
    m_nDist = CAMERA_MOVE_SPEED;
}

//=============================================================================
// [CameraMove]カメラの移動
//=============================================================================
void CCameraRemember::CameraMove(void)
{
    m_posV.x += m_fCameraDest;
    m_posR.x += m_fCameraDest;
}

