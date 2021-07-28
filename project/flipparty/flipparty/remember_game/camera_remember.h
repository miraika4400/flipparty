//=============================================================================
//
// 記憶ゲームのカメラヘッダ [camera_remember.h]
// Author : AYANO KUDO
//
//=============================================================================
//二重インクルード防止
#ifndef _CAMERA_REMEMBER_H_
#define _CAMERA_REMEMBER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "camera_base.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCameraRemember : public CCamera
{
    static CCameraRemember* m_pInsutance;// オブジェクトのポインタ
    CCameraRemember();

public:

    //============
    // メンバ関数
    //============
    ~CCameraRemember();

    static CCameraRemember *Create(void);

    HRESULT Init(void);
    void Update(void);
    void SetCamera(void);

    void CameraMove(void);

    // Get関数
    static CCameraRemember* GetInsutance(void) { return m_pInsutance; }// オブジェクトのポインタを取得

    // Set関数
    void SetDest(float fDest);
private:
    int m_nDist;// 移動中かどうか
    float m_fCameraDest;// カメラの移動係数

};

#endif //_CAMERA_REMEMBER_H_