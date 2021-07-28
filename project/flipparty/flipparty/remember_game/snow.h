//=============================================================================
//
// 吹雪ヘッダ [snow.h]
// Author : AYANO KUDO
//
//=============================================================================
//二重インクルード防止
#ifndef _SNOW_H_
#define _SNOW_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSnow : CScene2d
{
    static CSnow * m_pInstance;// インスタンスへのポインタ
    CSnow();
public:
    ~CSnow();

    static CSnow* Create(void);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void Scroll(void);

    // Get関数
    static CSnow* GetInstancce(void) { return m_pInstance; }        // インスタンスのゲッタ

private:
    D3DXVECTOR2 m_Speed;            // uvの移動スピード
    D3DXVECTOR2 m_vtx[NUM_VERTEX];  // UV座標

};

#endif // _SNOW_H_
