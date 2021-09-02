//=============================================================================
//
// 各ゲームのチュートリアルヘッダ [mini_tutorial.h]
// Author : AYANO KUDO
//
//=============================================================================
//二重インクルード防止
#ifndef _MINI_TUTORIAL_H_
#define _MINI_TUTORIAL_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "scene.h"
#include "resource_texture.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMini_Tutorial : public CScene
{
public:
    // メンバ関数
    CMini_Tutorial();
    ~CMini_Tutorial();

    static CMini_Tutorial* Create(CResourceTexture::TEXTURE_TYPE texture);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    // Get関数
    bool GetIsTutorialEnd(void) { return m_IsTutorialEnd;}

private:
    // メンバ変数
    static LPDIRECT3DTEXTURE9 m_pTexture;                   // テクスチャへのポインタ
    CPolygon *m_pPolygon;                                   // ポリゴンへのポインタ
    static CResourceTexture::TEXTURE_TYPE m_TextureData;    // 読み込むテクスチャのデータ
    bool m_IsTutorialEnd;// チュートリアルが終わったら
};
#endif //!_MINI_TUTORIAL_H_