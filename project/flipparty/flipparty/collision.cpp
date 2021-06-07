////////////////////////////////////////////////////
//
//    collisonクラスの処理[collison.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"

//*****************************
// マクロ定義
//*****************************

//*****************************
// 静的メンバ変数宣言
//*****************************


//******************************
// コンストラクタ
//******************************
CCollision::CCollision() :CModel(OBJTYPE_COLLISION)
{
	// 変数のクリア
	m_pMeshModel = NULL;   	//メッシュ情報へのポインタ
	m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
	m_nNumMatModel = 0;	    //マテリアル情報の数
}

//******************************
// デストラクタ
//******************************
CCollision::~CCollision()
{
}

//******************************
// クリエイト(球)
//******************************
CCollision * CCollision::CreateSphere(D3DXVECTOR3 pos, float fRadius)
{
	// メモリの確保
	CCollision *pCollision;
	pCollision = new CCollision;

	// initで使うから先に代入
	pCollision->m_type = COLLISIONTYPE_SPHERE;
	pCollision->m_fRadius = fRadius;

	// 初期化
	pCollision->Init();

	// 各値の代入・セット
	pCollision->SetPos(pos);
	pCollision->SetPriority(OBJTYPE_COLLISION); // オブジェクトタイプ

	return pCollision;
}

//******************************
// 球と球の当たり判定
//******************************
bool CCollision::CollisionSphere(CCollision * pCollision1, CCollision * pCollision2)
{
	if (pCollision1 == NULL || pCollision2 == NULL)
	{
		return false;
	}
	else
	{
		if (pow(pCollision1->GetPos().x - pCollision2->GetPos().x, 2) +
			pow(pCollision1->GetPos().y - pCollision2->GetPos().y, 2) +
			pow(pCollision1->GetPos().z - pCollision2->GetPos().z, 2) <= pow(pCollision1->m_fRadius + pCollision2->m_fRadius, 2))
		{

			return true;
		}
		else
		{
			return false;
		}
	}	
}

//******************************
// 範囲内か見る
//******************************]
float CCollision::OnRange(float fPoint, float fMin, float fMax)
{

	if (fPoint < fMin)
	{
		return fMin;
	}
	else if (fPoint > fMax)
	{
		return fMax;
	}
	else
	{
		return fPoint;
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CCollision::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}
#ifdef _DEBUG

	CreateMesh();
	// モデル割り当て
	BindModel(CResourceModel::GetModel(CResourceModel::MODEL_GENERAL_SPHERE));

#endif

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CCollision::Uninit(void)
{
	//メッシュの破棄
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}
	//マテリアルの破棄
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}

	CModel::Uninit();
}

//******************************
// 更新処理
//******************************
void CCollision::Update(void)
{
}

//******************************
// 描画処理
//******************************
void CCollision::Draw(void)
{
#ifdef _DEBUG

	// 色の設定
	D3DXMATERIAL* mat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();
	mat->MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// カリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ワイヤーフレームで描画
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//　描画
	CModel::Draw();
	// ワイヤーフレームをもどす
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	// カリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

#endif // _DEBUG
}

//******************************
// メッシュ生成
//******************************
void CCollision::CreateMesh(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	switch (m_type)
	{
	case COLLISIONTYPE_BOX:
		D3DXCreateBox(pDevice, m_size.x, m_size.y, m_size.z, &m_pMeshModel, &m_pBuffMatModel);
		break;
	case COLLISIONTYPE_SPHERE:
		// 球体の生成
		D3DXCreateSphere(pDevice, m_fRadius, 8, 8, &m_pMeshModel, &m_pBuffMatModel);
		break;
	default:
		break;
	}
}
