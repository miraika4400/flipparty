//=============================================================================
//
// cameraヘッダ [camera.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CAMERA_TPS_H_
#define _CAMERA_TPS_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "camera_base.h"

//*****************************
// クラス定義
//*****************************

// 三人称カメラクラス
class CTpsCamera : public CCamera
{
public:
	//============
	// メンバ関数
	//============
	CTpsCamera();
	~CTpsCamera();

	// static
	static CTpsCamera *Create(void);  // クラス生成

	HRESULT Init(void);   // 初期化
	void Update(void);	  // 更新

private:

	// 球面座標
	float m_fRad;                // 目標からの距離
	float m_fTheta;              // 角度シータ
	float m_fPhi;                // 角度ファイ
};

#endif