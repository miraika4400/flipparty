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
#define CAMERA_POS_V D3DXVECTOR3(0.0f,0.0f, 500.0f)  // 位置
#define CAMERA_POS_R D3DXVECTOR3(0.0f, 150.0f, 0.0f) // 注視点

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
	m_posV = CAMERA_POS_V;

	m_posR = CAMERA_POS_R;
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
}