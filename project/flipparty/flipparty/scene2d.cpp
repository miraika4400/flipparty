////////////////////////////////////////////////////
//
//    scene2dクラスの処理[scene2d.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "scene2d.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "keyboard.h"
#include "joypad.h"

//******************************
// マクロ定義
//******************************
#define POLYGON_SIZE 200 // ポリゴンの初期サイズ

//===================================
// コンストラクタ
//===================================
CScene2d::CScene2d(int nPriority) :CScene(nPriority)
{
	// 変数のクリア
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_fAngle = 0.0f;
	m_bAddMode = false;
}

//===================================
// デストラクタ
//===================================
CScene2d::~CScene2d()
{
}

//===================================
// クリエイト関数
//===================================
CScene2d * CScene2d::Create(void)
{
	// メモリの確保
	CScene2d *pScene2d;
	pScene2d = new CScene2d;
	// 初期化
	pScene2d->Init();

	return pScene2d;
}

//===================================
// 初期化処理
//===================================
HRESULT CScene2d::Init(void)
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// メンバ変数の初期化
	m_size = { POLYGON_SIZE,POLYGON_SIZE,0.0f };
	m_fAngle = 0.0f;
	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 中心から頂点の距離
	float fDistance = sqrtf(powf(m_size.x, 2) + powf(m_size.y, 2));
	// 中心から右上の頂点の角度
	float fAngle = atan2f(m_size.y, m_size.x);
	// 中心から左上の頂点の角度
	float  fAngle2 = atan2f(m_size.y, -m_size.x);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(-fAngle + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle + D3DXToRadian(m_fAngle))  * fDistance), m_pos.y + (sinf(fAngle + D3DXToRadian(m_fAngle))  * fDistance), 0);

	// テクスチャUV座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
	{
		pVtx[nCnt].col = m_col;
		pVtx[nCnt].rhw = 1.0f;
	}
	// アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===================================
// 終了処理
//===================================
void CScene2d::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//===================================
// 更新処理
//===================================
void CScene2d::Update(void)
{
}

//===================================
// 描画処理
//===================================
void CScene2d::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (m_pTexture != NULL)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);
	}

	// 加算モードの時
	if (m_bAddMode)
	{
		// 加算合成
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// 加算モードの時
	if (m_bAddMode)
	{
		// 通常合成に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	pDevice->SetTexture(0, 0);
}

//===================================
// 座標のセット
//===================================
void CScene2d::SetPos(const D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

	//posの代入
	m_pos = pos;

	// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 中心から頂点の距離
	float fDistance = sqrtf(powf(m_size.x, 2) + powf(m_size.y, 2));
	// 中心から右上の頂点の角度
	float fAngle = atan2f(m_size.y, m_size.x);
	// 中心から左上の頂点の角度
	float  fAngle2 = atan2f(m_size.y, -m_size.x);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(-fAngle + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle + D3DXToRadian(m_fAngle))  * fDistance), m_pos.y + (sinf(fAngle + D3DXToRadian(m_fAngle))  * fDistance), 0);

	// アンロック
	m_pVtxBuff->Unlock();
}

//===================================
// アニメーション情報のセット
//===================================
void CScene2d::SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX])
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

					// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = uv[0];
	pVtx[1].tex = uv[1];
	pVtx[2].tex = uv[2];
	pVtx[3].tex = uv[3];

	// アンロック
	m_pVtxBuff->Unlock();
}

void CScene2d::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;

	// 頂点座標の再設定
	SetPos(m_pos);
}

void CScene2d::SetColor(const D3DXCOLOR col)
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

	m_col = col;

	// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// アンロック
	m_pVtxBuff->Unlock();
}
