////////////////////////////////////////////////////
//
//    particleクラスの処理[particle.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "game.h"
#include "flipper.h"
#include "polygon.h"
#include "resource_texture.h"
#include "billboard.h"

//*****************************
// マクロ定義
//*****************************
#define HIERARCHY_TEXT_PATH1 "./data/Texts/hierarchy/pengin00.txt"   // 階層構造テキストのパス
#define RIGHT_FLIPPER_PARTS_NUM 5                                    // 右羽のパーツ番号
#define LEFT_FLIPPER_PARTS_NUM  4                                    // 左羽のパーツ番号
#define RIGHT_FLIPPER_DIST_ANGLE_UP   D3DXToRadian(-60.0f)           // 右羽を上げたときの角度
#define RIGHT_FLIPPER_DIST_ANGLE_DOWN D3DXToRadian(30.0f)            // 右羽を下げたときの角度
#define LEFT_FLIPPER_DIST_ANGLE_UP    -RIGHT_FLIPPER_DIST_ANGLE_UP   // 左羽を上げたときの角度
#define LEFT_FLIPPER_DIST_ANGLE_DOWN  -RIGHT_FLIPPER_DIST_ANGLE_DOWN // 左羽を下げたときの角度
#define FLIPPER_RATE 0.07f                                           // 羽を動かすときの係数
#define FLIPPER_JUDGE D3DXToRadian(20.0f)                            // 上がっているか下がっているか判定の基準値
#define PLAYER_NUMBER_ICON_HEIGHT 85.0f                              // プレイヤー番号アイコンの高さ
#define PLAYER_NUMBER_ICON_SIZE D3DXVECTOR3(10.0f,10.0f,0.0f)       // プレイヤー番号アイコンのサイズ
#define PLAYER_NUMBER_ICON_POS  D3DXVECTOR3(GetPos().x, GetPos().y + PLAYER_NUMBER_ICON_HEIGHT, GetPos().z) // プレイヤー番号アイコンの位置

//*****************************
// 静的メンバ変数宣言
//*****************************
CResourceModel::Model CPlayer::m_model[MAX_PARTS_NUM] = {};
int CPlayer::m_nPartsNum = 0;

//******************************
// コンストラクタ
//******************************
CPlayer::CPlayer() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// 変数のクリア
	m_pFlieer = NULL;
	m_nPlayerNum = 0;                  // プレイヤー番号
	ZeroMemory(&m_fFlipperDist, sizeof(m_fFlipperDist)); // 羽の角度 目標値
	m_pPlayerNumIcon = NULL; // プレイヤー番号アイコン
#ifdef _DEBUG
	// デバッグ用変数
	ZeroMemory(&m_pPolygon, sizeof(m_pPolygon));// ポリゴンクラスのポインタ
#endif // _DEBUG
}

//******************************
// デストラクタ
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// クリエイト
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
	// メモリの確保
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->m_nPlayerNum = nPlayerNum;
	
	// 初期化
	pPlayer->Init();

	// 各値の代入・セット
	pPlayer->SetPos(pos);
	pPlayer->SetPriority(OBJTYPE_PLAYER); // オブジェクトタイプ

	return pPlayer;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CPlayer::Load(void)
{

	// モデルの読み込み
	LoadModels(HIERARCHY_TEXT_PATH1, &m_model[0], &m_nPartsNum);

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CPlayer::Unload(void)
{

	for (int nCnt = 0; nCnt < m_nPartsNum; nCnt++)
	{
		//メッシュの破棄
		if (m_model[nCnt].pMesh != NULL)
		{
			m_model[nCnt].pMesh->Release();
			m_model[nCnt].pMesh = NULL;
		}
		//マテリアルの破棄
		if (m_model[nCnt].pBuffMat != NULL)
		{
			m_model[nCnt].pBuffMat->Release();
			m_model[nCnt].pBuffMat = NULL;
		}
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nPartsNum, &m_model[0], HIERARCHY_TEXT_PATH1)))
	{
		return E_FAIL;
	}

	m_pFlieer = CFlipper::Create();

	// 羽の目標角度の初期化
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = 0.0f;
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = 0.0f;

	// プレイヤーアイコンの設定
	m_pPlayerNumIcon = CBillboard::Create(PLAYER_NUMBER_ICON_POS, PLAYER_NUMBER_ICON_SIZE);
	
	// アイコンテクスチャの設定
	if (m_pPlayerNumIcon != NULL)
	{
		switch (m_nPlayerNum)
		{
		case 0:
			m_pPlayerNumIcon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_1P));
			break;
		case 1:
			m_pPlayerNumIcon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_2P));
			break;
		case 2:
			m_pPlayerNumIcon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_3P));
			break;
		case 3:
			m_pPlayerNumIcon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_ICON_4P));
			break;
		default:
			break;
		}
	}

#ifdef _DEBUG
	// デバッグ用
	m_pPolygon[CFlipper::FLIPPER_TYPE_LEFT] = CPolygon::Create(D3DXVECTOR3(50.0f, 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));// ポリゴンクラスのポインタ
	m_pPolygon[CFlipper::FLIPPER_TYPE_RIGHT] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH - 50.0f, 100.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));// ポリゴンクラスのポインタ
#endif // _DEBU
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CPlayer::Uninit(void)
{
	CModelHierarchy::Uninit();

	// フリッパークラスの終了処理
	if (m_pFlieer != NULL)
	{
		m_pFlieer->Uninit();
		m_pFlieer = NULL;
	}

	// アイコンの解放
	if (m_pPlayerNumIcon != NULL)
	{
		m_pPlayerNumIcon->Uninit();
		delete m_pPlayerNumIcon;
		m_pPlayerNumIcon = NULL;
	}

#ifdef _DEBUG
	for (int nCntPolygon = 0; nCntPolygon < 2; nCntPolygon++)
	{
		if (m_pPolygon[nCntPolygon] != NULL)
		{			  
			m_pPolygon[nCntPolygon]->Uninit();
			delete m_pPolygon[nCntPolygon];
			m_pPolygon[nCntPolygon] = NULL;
		}
	}
#endif // _DEBU
}

//******************************
// 更新処理
//******************************
void CPlayer::Update(void)
{
	// 羽を動かす
	ControllFlipper();

	// プレイヤー番号アイコンの位置の設定
	if (m_pPlayerNumIcon != NULL)
	{
		m_pPlayerNumIcon->SetPos(PLAYER_NUMBER_ICON_POS);
	}

#ifdef _DEBUG

	for (int nCntPolygon = 0; nCntPolygon < 2; nCntPolygon++)
	{
		CFlipper::FLIPPER_STATE flipperState = m_pFlieer->GetState((CFlipper::FLIPPER_TYPE)nCntPolygon);

		switch (flipperState)
		{
		case CFlipper::FLIPPERSTATE_UP:
			m_pPolygon[nCntPolygon]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UP));
			break;
		case CFlipper::FLIPPERSTATE_DOWN:
			m_pPolygon[nCntPolygon]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_DOWN));
			break;
		case CFlipper::FLIPPER_STATE_NONE:

			if (nCntPolygon == CFlipper::FLIPPER_TYPE_LEFT)
			{
				m_pPolygon[nCntPolygon]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_LEFT));
			}
			else
			{
				m_pPolygon[nCntPolygon]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_RIGHT));
			}
			break;
		default:
			break;
		}
	}
#endif // _DEBU
}

//******************************
// 描画処理
//******************************
void CPlayer::Draw(void)
{
	CModelHierarchy::Draw();

	if (m_pPlayerNumIcon != NULL)
	{
		m_pPlayerNumIcon->Draw();
	}

#ifdef _DEBUG
	m_pPolygon[CFlipper::FLIPPER_TYPE_LEFT]->Draw();
	m_pPolygon[CFlipper::FLIPPER_TYPE_RIGHT]->Draw();
#endif // _DEBU
}

//******************************
// 羽の操作処理
//******************************
void CPlayer::ControllFlipper(void)
{

#ifdef _DEBUG
	// キーボード操作
	// 左羽を操作
	if (CManager::GetKeyboard()->GetKeyPress(DIK_UP))
	{// 上げる
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_DOWN))
	{// 下げる
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
	}

	// 右羽を操作
	if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
	{// 上げる
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_S))
	{// 下げる
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
	}
#endif // _DEBUG
	// コントローラー操作
	
	// 左羽を操作
	if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lRz <= -10)
	{// 上げる
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
	}
	else if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lRz >= 10)
	{// 下げる
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
	}

	// 右羽を操作
	if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lY <= -10)
	{// 上げる
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
	}
	else if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lY >= 10)
	{// 下げる
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
	}

	// 羽の角度の管理
	ManageFlipperAngle();

}

//******************************
// 羽の角度の管理
//******************************
void CPlayer::ManageFlipperAngle(void)
{
	// モデルデータの取得
	CResourceModel::Model * pModelData = GetModelData();
	// 右羽を動かす
	pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z += (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] - pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z)*FLIPPER_RATE;
	// 左羽を動かす
	pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z += (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] - pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z)*FLIPPER_RATE;

	// 右羽の上がっているか下がっているかの判定
	if (pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z <= RIGHT_FLIPPER_DIST_ANGLE_UP + FLIPPER_JUDGE)
	{// 上がっているとき
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z >= RIGHT_FLIPPER_DIST_ANGLE_DOWN - FLIPPER_JUDGE)
	{// 下がっているとき
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
	}
	else
	{// 中間
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPER_STATE_NONE);
	}

	// 右羽の上がっているか下がっているかの判定
	if (pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z >= LEFT_FLIPPER_DIST_ANGLE_UP - FLIPPER_JUDGE)
	{// 上がっているとき
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z <= LEFT_FLIPPER_DIST_ANGLE_DOWN + FLIPPER_JUDGE)
	{// 下がっているとき
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
	}
	else
	{// 中間
		m_pFlieer->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPER_STATE_NONE);
	}
}
