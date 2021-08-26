////////////////////////////////////////////////////
//
//    scene3dクラスの処理[scene3d.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "object3d_shader.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "camera_base.h"

//******************************
// マクロ定義
//******************************
#define POLYGON_SIZE 200 // ポリゴンの初期サイズ
#define FVF_SHADER (D3DFVF_XYZ|D3DFVF_NORMAL |D3DFVF_DIFFUSE|D3DFVF_TEX1)

//===================================
// コンストラクタ
//===================================
CObject3dShader::CObject3dShader(int nPriority) :CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pDecl = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_mtxWorld = {};
	m_pldxBuff = NULL;
	m_bAddMode = false;

	memset(&m_shader, 0, sizeof(m_shader)); // シェーダー
}

//===================================
// デストラクタ
//===================================
CObject3dShader::~CObject3dShader()
{
}

//===================================
// クリエイト関数
//===================================
CObject3dShader * CObject3dShader::Create(void)
{
	// メモリの確保
	CObject3dShader *p3dShader;
	p3dShader = new CObject3dShader;
	// 初期化
	p3dShader->Init();

	return p3dShader;
}

//===================================
// 初期化処理
//===================================
HRESULT CObject3dShader::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点宣言
	D3DVERTEXELEMENT9 vertexElements[] = {
		{ 0          ,0          ,D3DDECLTYPE_FLOAT3 ,D3DDECLMETHOD_DEFAULT ,D3DDECLUSAGE_POSITION ,0 },    // 座標
		{ 0          ,12         ,D3DDECLTYPE_FLOAT3 ,D3DDECLMETHOD_DEFAULT ,D3DDECLUSAGE_NORMAL   ,0 },    // 法線
		{ 0          ,24         ,D3DDECLTYPE_FLOAT2 ,D3DDECLMETHOD_DEFAULT ,D3DDECLUSAGE_TEXCOORD ,0 },    // テクスチャUV
		{ 0          ,32         ,D3DDECLTYPE_FLOAT3 ,D3DDECLMETHOD_DEFAULT ,D3DDECLUSAGE_TANGENT  ,0 },    // 接線
		{ 0          ,44         ,D3DDECLTYPE_D3DCOLOR ,D3DDECLMETHOD_DEFAULT ,D3DDECLUSAGE_COLOR    ,0 },  // カラー
		{ 0xFF       ,0          ,D3DDECLTYPE_UNUSED ,0                     ,0                     ,0 } };

	pDevice->CreateVertexDeclaration(vertexElements, &m_pDecl);

	VERTEX_3D_SHADER *pVtx;// 頂点情報ポインタ

						   // 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_SHADER)*NUM_VERTEX, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_pVtxBuff, NULL);

	// メンバ変数の初期化
	m_size = { POLYGON_SIZE, 1.0f, POLYGON_SIZE };
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(+1.0f, +1.0f, -1.0f);
	pVtx[1].pos = D3DXVECTOR3(-1.0f, +1.0f, -1.0f);
	pVtx[2].pos = D3DXVECTOR3(+1.0f, -1.0f, +1.0f);
	pVtx[3].pos = D3DXVECTOR3(-1.0f, -1.0f, +1.0f);

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
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// 接線
		pVtx[nCnt].tangent = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	}

	// アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===================================
// 終了処理
//===================================
void CObject3dShader::Uninit(void)
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
void CObject3dShader::Update(void)
{
}

//===================================
// 描画処理
//===================================
void CObject3dShader::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_shader.pEffect != NULL)
	{// シェーダーがNULLじゃないとき

	 // シェーダー光源計算をするためライトを消す
		pDevice->SetRenderState(D3DRS_LIGHTING, false);

		D3DXMATRIX mtxRot, mtxTrans, mtxScail; // 行列計算用マトリクス

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
		D3DXMatrixScaling(&mtxScail, m_size.x, m_size.y, m_size.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScail);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D_SHADER));
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_SHADER);

		pDevice->SetTexture(0, m_pTexture);

		pDevice->SetVertexDeclaration(m_pDecl);

		// テクニック
		m_shader.pEffect->SetTechnique(m_shader.achTechniqueName);

		// パス数の取得
		UINT numPass = 0;
		m_shader.pEffect->Begin(&numPass, 0);

		// シェーダに情報
		D3DXMATRIX mat, viewMtx;
		D3DXMatrixIdentity(&mat);
		mat = m_mtxWorld * (*CManager::GetCamera()->GetViewMtx())* (*CManager::GetCamera()->GetProjectionMtx());
		m_shader.pEffect->SetMatrix("WorldViewProj", &mat); // プロジェクション
		m_shader.pEffect->SetMatrix("World", &m_mtxWorld);  // ワールド
		m_shader.pEffect->SetFloatArray("LightDirection", (float*)&D3DXVECTOR3(0.01f, 1.0f, 0.0f), 3);// ライトディレクション
		m_shader.pEffect->SetFloatArray("DiffuseColor", (float*)&D3DXVECTOR4(1, 1, 1, 1), 4); // 反射光

																							  // パス数分描画処理のループ
		for (int nCntEffect = 0; nCntEffect < (int)numPass; nCntEffect++)
		{
			// シェーダーに情報を送る
			SetShaderValue();

			// シェーダパスの描画開始
			m_shader.pEffect->BeginPass(nCntEffect);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

			// シェーダパスの終了
			m_shader.pEffect->EndPass();
		}

		// シェーダの終了
		m_shader.pEffect->End();

		// 加算モードの時
		if (m_bAddMode)
		{
			// 通常合成に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		// テクスチャの初期化
		pDevice->SetTexture(0, 0);
		// ライトをつける
		pDevice->SetRenderState(D3DRS_LIGHTING, true);

		pDevice->SetVertexDeclaration(NULL);
	}
}

//===================================
// 座標のセット
//===================================
void CObject3dShader::SetPos(const D3DXVECTOR3 pos)
{
	//posの代入
	m_pos = pos;
}

//===================================
// アニメーション情報のセット
//===================================
void CObject3dShader::SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX])
{
	VERTEX_3D_SHADER *pVtx;// 頂点情報ポインタ

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
void CObject3dShader::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;

	// 頂点座標の再設定
	SetPos(m_pos);
}

//===================================
// 色のセット
//===================================
void CObject3dShader::SetColor(const D3DXCOLOR col)
{
	VERTEX_3D_SHADER *pVtx;// 頂点情報ポインタ

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

//===================================
// HLSLに値を送る
//===================================
void CObject3dShader::SetShaderValue(void)
{

}