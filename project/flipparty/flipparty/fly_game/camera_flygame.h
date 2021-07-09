//=============================================================================
//
// cameraヘッダ [camera.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CAMERA_FLY_GAME_H_
#define _CAMERA_FLY_GAME_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "camera_base.h"

//*****************************
// クラス定義
//*****************************

// 連打ゲームのカメラクラス
class CFlyGameCamera : public CCamera
{
public:
	//============
	// メンバ関数
	//============
	CFlyGameCamera();
	~CFlyGameCamera();

	// static
	static CFlyGameCamera *Create(void);  // クラス生成

	HRESULT Init(void);   // 初期化
	void Update(void);	  // 更新
	void SetCamera(void); // カメラのセット

private:
};

#endif