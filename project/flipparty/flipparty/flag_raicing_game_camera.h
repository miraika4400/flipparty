//=============================================================================
//
// cameraヘッダ [camera.h]
// Author : 筒井 俊稀
//
//=============================================================================

//二重インクルード防止
#ifndef _FLAG_RAICING_GAME_CAMERA_H_
#define _FLAG_RAICING_GAME_CAMERA_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "camera_base.h"

//*****************************
// クラス定義
//*****************************

// 連打ゲームのカメラクラス
class CFlagRaicingGameCamera : public CCamera
{
public:
	//============
	// メンバ関数
	//============
	CFlagRaicingGameCamera();
	~CFlagRaicingGameCamera();

	// static
	static CFlagRaicingGameCamera *Create(void);  // クラス生成

	HRESULT Init(void);   // 初期化
	void Update(void);	  // 更新
	void SetCamera(void); // カメラのセット

private:
};

#endif#pragma once
#pragma once
