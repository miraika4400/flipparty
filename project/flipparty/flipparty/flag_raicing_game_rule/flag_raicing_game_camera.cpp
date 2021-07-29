////////////////////////////////////////////////////
//
//    カメラクラスの処理[camera.cpp]
//    Author:筒井 俊稀
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "flag_raicing_game_camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "mouse.h"
#include "joypad.h"

//******************************
// マクロ定義
//******************************
#define CAMERA_POS_V D3DXVECTOR3(0.0f, 0.0f, 250.0f)  // 位置
#define CAMERA_POS_R D3DXVECTOR3(0.0f, 0.0f, 0.0f) // 注視点
//******************************
// 静的メンバ変数宣言
//******************************

//******************************
// コンストラクタ
//******************************
CFlagRaicingGameCamera::CFlagRaicingGameCamera()
{
	// 変数のクリア
}

//******************************
// デストラクタ
//******************************
CFlagRaicingGameCamera::~CFlagRaicingGameCamera()
{
}

//******************************
// クリエイト
//******************************
CFlagRaicingGameCamera * CFlagRaicingGameCamera::Create(void)
{
	CFlagRaicingGameCamera * pCamera = new CFlagRaicingGameCamera;
	pCamera->Init();

	return pCamera;
}


//******************************
// 初期化処理
//******************************
HRESULT CFlagRaicingGameCamera::Init(void)
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
void CFlagRaicingGameCamera::Update(void)
{
}