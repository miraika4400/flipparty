//=============================================================================
//
// 記憶ゲームのプレイヤークラス [player_remember.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "player_remember.h"
#include "scene3d.h"
#include "resource_texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define REMEMBER_PLAYER_ROT D3DXToRadian(180)
//=============================================================================
// [CPlayerRemember]コンストラクタ
//=============================================================================
CPlayerRemember::CPlayerRemember()
{
    m_IsLoss = false;
}

//=============================================================================
// [~CPlayerRemember]デストラクタ
//=============================================================================
CPlayerRemember::~CPlayerRemember()
{

}

//=============================================================================
// [Create]インスタンス生成
//=============================================================================
CPlayerRemember * CPlayerRemember::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
    CPlayerRemember* pPlayer = nullptr;
    if (!pPlayer)
    {
        pPlayer = new CPlayerRemember;

        pPlayer->SetPlayerNumber(nPlayerNum);   // プレイヤー番号のセット
        pPlayer->SetPos(pos);                   // プレイヤーの位置を設定
        pPlayer->SetRot({0.0f, REMEMBER_PLAYER_ROT, 0.0f});// プレイヤーの角度設定
        pPlayer->SetPriority(OBJTYPE_PLAYER);   // オブジェクトタイプ

        // 初期化
        pPlayer->Init();

		//　影の生成
		CScene3d * p3DPolygon = CScene3d::Create(D3DXVECTOR3(pos.x, pos.y + 1.0f, pos.z), PLAYER_SHADOW_SIZE);
		p3DPolygon->SetPriority(CScene::OBJTYPE_PARTICLE); // プライオリティの設定
		p3DPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PENGUIN_SHADOW));// テクスチャ
		p3DPolygon->SetColor(PLAYER_SHADOW_COLOR);// 色
    }
    return pPlayer;
}

//=============================================================================
// [Init]初期化処理
//=============================================================================
HRESULT CPlayerRemember::Init(void)
{
    m_IsLoss = false;
    SetMoveFlag(false);
    CPlayer::Init();

    return S_OK;
}

//=============================================================================
// [Uninit]終了処理
//=============================================================================
void CPlayerRemember::Uninit(void)
{
    CPlayer::Uninit();
}

//=============================================================================
// [Uninit]更新処理
//=============================================================================
void CPlayerRemember::Update(void)
{
    // プレイヤークラスの更新処理
    CPlayer::Update();

}

//=============================================================================
// [Draw]描画処理
//=============================================================================
void CPlayerRemember::Draw(void)
{
    CPlayer::Draw();
}

//=============================================================================
// [ControllFlipper]羽の操作
//=============================================================================
void CPlayerRemember::ControllFlipper(void)
{
    return;
}

void CPlayerRemember::GameProcess(void)
{
}

void CPlayerRemember::MiniResultProcess(void)
{
}

