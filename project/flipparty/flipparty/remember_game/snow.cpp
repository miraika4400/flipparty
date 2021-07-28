//=============================================================================
//
// 吹雪クラス [snow.h]
// Author : AYANO KUDO
//
//=============================================================================
#include "snow.h"
#include "resource_texture.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CSnow *CSnow::m_pInstance = nullptr;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SNOW_POS   D3DXVECTOR3(SCREEN_WIDTH/2.0F, SCREEN_HEIGHT/2.0F, 0.0f)
#define SNOW_SIZE  D3DXVECTOR3(SCREEN_WIDTH/2.0F, SCREEN_HEIGHT/2.0F, 0.0f)
#define SNOW_SPPED D3DXVECTOR2(0.01f,-0.03f)

//=============================================================================
// [CSnow] コンストラクタ
//=============================================================================
CSnow::CSnow()
{
}

//=============================================================================
// [~CSnow] デストラクタ
//=============================================================================
CSnow::~CSnow()
{
}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CSnow * CSnow::Create(void)
{
    // インスタンス生成
    if (!m_pInstance)
    {
        m_pInstance = new CSnow;
        m_pInstance->Init();
    }

    return m_pInstance;
}

//=============================================================================
// [Init] 初期化処理
//=============================================================================
HRESULT CSnow::Init(void)
{

    m_Speed = D3DXVECTOR2(0.0f, 0.0f);// アニメーションようUV初期化


    CScene2d::Init();

    //位置の設定
    SetPos(SNOW_POS);

    //サイズの設定
    SetSize(SNOW_SIZE);

    //テクスチャの設定
    BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_SNOW));


    return S_OK;
}

//=============================================================================
// [Uninit] 終了処理
//=============================================================================
void CSnow::Uninit(void)
{
    // インスタンスの破棄
    if (m_pInstance)
    {
      delete m_pInstance;
      m_pInstance = nullptr;
    }
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CSnow::Update(void)
{
    //更新処理
    CScene2d::Update();

    Scroll();
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CSnow::Draw(void)
{
    //ポリゴンの描画
    CScene2d::Draw();
}

//=============================================================================
// [Scroll] スクロール処理
//=============================================================================
void CSnow::Scroll(void)
{
    m_Speed +=SNOW_SPPED;
    m_vtx[0] = D3DXVECTOR2(0.0f+m_Speed.x,0.0f+m_Speed.y);
    m_vtx[1] = D3DXVECTOR2(1.0f+m_Speed.x,0.0f+m_Speed.y);
    m_vtx[2] = D3DXVECTOR2(0.0f+m_Speed.x,1.0f+m_Speed.y);
    m_vtx[3] = D3DXVECTOR2(1.0f+m_Speed.x,1.0f+m_Speed.y);

    // UV座標の変更
    SetTextureUV(m_vtx);
}
