////////////////////////////////////////////////////
//
//    billboardクラスの処理[billboard.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "billboard.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "game.h"

//******************************
// マクロ定義
//******************************
#define POLYGON_SIZE 200 // ポリゴンの初期サイズ

//===================================
// コンストラクタ
//===================================
CBillboard::CBillboard(int nPriority) :CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_fAngle = 0.0f;
	m_mtxWorld = {};
	m_pldxBuff = NULL;
	m_bAddMode = false;
}

//===================================
// デストラクタ
//===================================
CBillboard::~CBillboard()
{
}

//===================================
// クリエイト関数
//===================================
CBillboard * CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// メモリの確保
	CBillboard *pScene3d;
	pScene3d = new CBillboard;
	// 引数の代入
	pScene3d->m_pos = pos;
	pScene3d->m_size = size;
	// 初期化
	pScene3d->Init();

	return pScene3d;
}

//===================================
// 初期化処理
//===================================
HRESULT CBillboard::Init(void)
{
	VERTEX_3D *pVtx;// 頂点情報ポインタ

					// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// メンバ変数の初期化
	m_col = { 1.0f,1.0f,1.0f,1.0f };

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 中心から頂点の距離
	float fDistance = sqrtf(powf(m_size.x, 2) + powf(m_size.y, 2));
	// 中心から右上の頂点の角度
	float fAngle = atan2f(m_size.y, m_size.x);
	// 中心から左上の頂点の角度
	float  fAngle2 = atan2f(m_size.y, -m_size.x);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3((cosf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), (sinf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[1].pos = D3DXVECTOR3((cosf(fAngle + D3DXToRadian(m_fAngle)) * fDistance), (sinf(fAngle + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[2].pos = D3DXVECTOR3((cosf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), (sinf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[3].pos = D3DXVECTOR3((cosf(-fAngle + D3DXToRadian(m_fAngle))  * fDistance), (sinf(-fAngle + D3DXToRadian(m_fAngle)) * fDistance), 0);


	// テクスチャUV座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
	{
		// 色の設定
		pVtx[nCnt].col = m_col;
		// 法線
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	// アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===================================
// 終了処理
//===================================
void CBillboard::Uninit(void)
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
void CBillboard::Update(void)
{
}

//===================================
// 描画処理
//===================================
void CBillboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScail;//行列計算用マトリクス

	// ライトを消す
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	// 加算モードの時
	if (m_bAddMode)
	{
		// 加算合成
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// マトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&mtxRot);
	D3DXMatrixIdentity(&mtxTrans);
	D3DXMatrixIdentity(&mtxScail);

	// サイズ
	D3DXMatrixScaling(&mtxScail, 1.0f, 1.0f, 1.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScail);

# if 1
	// 向きを反映
	// カメラの向きに向ける
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);

	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

#else

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

#endif

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// テクスチャの初期化
	pDevice->SetTexture(0, 0);

	// 加算モードの時
	if (m_bAddMode)
	{
		// 通常合成に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	// ライトをつける
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

//===================================
// 座標のセット
//===================================
void CBillboard::SetPos(const D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;// 頂点情報ポインタ

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
	pVtx[0].pos = D3DXVECTOR3((cosf(  fAngle2 + D3DXToRadian(m_fAngle)) * fDistance) , (sinf( fAngle2  + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[1].pos = D3DXVECTOR3((cosf(  fAngle  + D3DXToRadian(m_fAngle)) * fDistance) , (sinf( fAngle   + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[2].pos = D3DXVECTOR3((cosf( -fAngle2 + D3DXToRadian(m_fAngle)) * fDistance) , (sinf( -fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[3].pos = D3DXVECTOR3((cosf( -fAngle  + D3DXToRadian(m_fAngle)) * fDistance) , (sinf( -fAngle  + D3DXToRadian(m_fAngle)) * fDistance), 0);

	// アンロック
	m_pVtxBuff->Unlock();
}

//===================================
// 角度のセット
//===================================
void CBillboard::SetAngle(const float fAngle)
{
	m_fAngle = fAngle;
	SetPos(m_pos);
}

//===================================
// アニメーション情報のセット
//===================================
void CBillboard::SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX])
{
	VERTEX_3D *pVtx;// 頂点情報ポインタ

					// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = uv[0];
	pVtx[1].tex = uv[1];
	pVtx[2].tex = uv[2];
	pVtx[3].tex = uv[3];

	// アンロック
	m_pVtxBuff->Unlock();
}

//===================================
// サイズのセット
//===================================
void CBillboard::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;

	// 頂点座標の再設定
	SetPos(m_pos);
}

//===================================
// 色のセット
//===================================
void CBillboard::SetColor(const D3DXCOLOR col)
{
	VERTEX_3D *pVtx;// 頂点情報ポインタ

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
