////////////////////////////////////////////////////
//
//    ゲームクラスの処理[game.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "warning.h"
#include "billboard.h"
#include "resource_texture.h"
#include "rule_flygame.h"
#include "player_flygame.h"
#include "cloud.h"

//=============================
// マクロ定義
//=============================
#define UI_SIZE D3DXVECTOR3(15.0f,15.0f,0.0f)    // UIサイズ
#define UI_POS_Y 105                             // プレイヤーからどれくらい高い位置か
#define UI_POS_Z 5                               // プレイヤーからどれくらい手前か
#define COLOR D3DXCOLOR(1.0f,1.0f,1.0f,m_fAlpha) // 色
#define CLOUD_COUNT 60                           // 雲生成カウント
#define LIFE CLOUD_COUNT + 60                    // 寿命

//=============================
// 静的メンバ変数宣言
//=============================

//=============================
// コンストラクタ
//=============================
CWarningUI::CWarningUI() :CScene(OBJTYPE_UI)
{
	// 変数のクリア
	m_pBillboard = NULL;  // ビルボードポインタ
	m_nCloudCount = 0;
	m_fAlpha = 0.0f;
}

//=============================
// デストラクタ
//=============================
CWarningUI::~CWarningUI()
{
}

//=============================
// クリエイト
//=============================
CWarningUI * CWarningUI::Create(int nPlayerNum)
{
	// メモリの確保
	CWarningUI *pWarningUi = new CWarningUI;

	// 引数の代入
	pWarningUi->m_nPlayerNum = nPlayerNum;

	// 初期化
	pWarningUi->Init();

	return pWarningUi;
}

//=============================
// 初期化処理
//=============================
HRESULT CWarningUI::Init(void)
{
	// ビルボードクラスの生成
	m_pBillboard = CBillboard::Create(ReturnUIPosition(), UI_SIZE);

	// テクスチャの設定
	m_pBillboard->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_WARNING));

	// カウントの初期化
	m_nCloudCount = 0;
	
	// アルファ値の初期化
	m_fAlpha = 0.0f;

	// 色の設定
	m_pBillboard->SetColor(COLOR);
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CWarningUI::Uninit(void)
{
	if (m_pBillboard != NULL)
	{
		m_pBillboard->Uninit();
		delete m_pBillboard;
		m_pBillboard = NULL;
	}

	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CWarningUI::Update(void)
{
	m_nCloudCount++;

	if (m_nCloudCount < CLOUD_COUNT)
	{
		m_fAlpha = (float)((m_nCloudCount) % (CLOUD_COUNT / 2)) / (float)(CLOUD_COUNT / 2);
	}
	else if (m_nCloudCount >= LIFE)
	{
		Uninit();
		return;
	}
	else if (m_nCloudCount == CLOUD_COUNT)
	{
		m_fAlpha = 1.0f;
		CCloud::Create(m_nPlayerNum);
	}



	if (m_pBillboard != NULL)
	{
		// UIの位置調整
		m_pBillboard->SetPos(ReturnUIPosition());
		m_pBillboard->SetColor(COLOR);
	}
}

//=============================
// 描画処理
//=============================
void CWarningUI::Draw(void)
{
	if (m_pBillboard != NULL)
	{
		m_pBillboard->Draw();
	}
}

//=============================
// UIの位置を返す
//=============================
D3DXVECTOR3 CWarningUI::ReturnUIPosition(void)
{
	D3DXVECTOR3 OutPos = CRuleFly::GetPlayer(m_nPlayerNum)->GetPos();

	OutPos.y += UI_POS_Y;
	OutPos.z += UI_POS_Z;

	return OutPos;
}
