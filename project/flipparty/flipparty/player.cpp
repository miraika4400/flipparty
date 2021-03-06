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
#include "motion.h"
#include "resource_shader.h"
#include "camera_base.h"
#include "light.h"
#include "sound.h"
#include "scene3d.h"
#include "flag_raicing_game_rule.h"

//*****************************
// マクロ定義
//*****************************
#define HIERARCHY_TEXT_PATH1 "./data/Texts/hierarchy/pengin00.txt"   // 階層構造テキストのパス
#define FLIPPER_RATE 0.1f                                            // 羽を動かすときの係数
#define FLIPPER_JUDGE D3DXToRadian(20.0f)                            // 上がっているか下がっているか判定の基準値
#define PLAYER_NUMBER_ICON_HEIGHT 85.0f                              // プレイヤー番号アイコンの高さ
#define PLAYER_NUMBER_ICON_SIZE D3DXVECTOR3(10.0f,10.0f,0.0f)        // プレイヤー番号アイコンのサイズ
#define PLAYER_NUMBER_ICON_POS  D3DXVECTOR3(GetPos().x, GetPos().y + PLAYER_NUMBER_ICON_HEIGHT, GetPos().z) // プレイヤー番号アイコンの位置
#define FACE_PARTS_NUMBER 3  // 表情パーツのパーツ番号
#define FACE_PATTERN 3       // 表情パターン数
#define FACE_TEX_V (1.0f/(float)FACE_PATTERN) * (float)m_facePattern
#define PLAYER_RESULT_WORST_ROT_X D3DXToRadian(70.0f) // 最下位の時の回転軸のXの値

//*****************************
// 静的メンバ変数宣言
//*****************************
CResourceModel::Model CPlayer::m_model[MAX_PARTS_NUM] = {};
int CPlayer::m_nPartsNum = 0;
char CPlayer::m_achAnimPath[MOTION_MAX][64]
{
	{ "./data/Texts/motion/idol.txt" },         // 待機アニメーション
	{ "./data/Texts/motion/miniresult_1.txt" }, // 一位アニメーション
	{ "./data/Texts/motion/miniresult_2.txt" }, // 二位アニメーション
	{ "./data/Texts/motion/miniresult_3.txt" }, // 三位アニメーション
	{ "./data/Texts/motion/miniresult_4.txt" }, // 最下位アニメーション
	{ "./data/Texts/motion/fly.txt" },          // flyアニメーション
	{ "./data/Texts/motion/thunder3.txt" },     // 雷アニメーション
	{ "./data/Texts/motion/fall.txt" },         // 転ぶ アニメーション
};

//******************************
// コンストラクタ
//******************************
CPlayer::CPlayer() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// 変数のクリア
	m_pFlipper = NULL;
	m_pFlipperMoveState = NULL;
	m_nPlayerNum = 0;                  // プレイヤー番号
	ZeroMemory(&m_fFlipperDist, sizeof(m_fFlipperDist)); // 羽の角度 目標値
	m_pPlayerNumIcon = NULL; // プレイヤー番号アイコン
	m_bMove = false;         // 動けるかどうかのフラグ
	m_nRank = 0;
	m_pActiveMotion = NULL;
	m_facePattern = FACE_PATTERN_NORMAL;
	m_nPoint = 0;
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


	//　影の生成
	CScene3d * p3DPolygon = CScene3d::Create(D3DXVECTOR3(pos.x, pos.y + 1.0f, pos.z), PLAYER_SHADOW_SIZE);
	p3DPolygon->SetPriority(CScene::OBJTYPE_PARTICLE); // プライオリティの設定
	p3DPolygon->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PENGUIN_SHADOW));// テクスチャ
	p3DPolygon->SetColor(PLAYER_SHADOW_COLOR);// 色

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
	// ポイントの初期化
	m_nPoint = 0;

	// フリッパークラスの生成
	m_pFlipper = CFlipper::Create();
	m_pFlipperMoveState = CFlipper::Create();

	// 羽の目標角度の初期化
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;

	// プレイヤーアイコンの設定
	m_pPlayerNumIcon = CBillboard::Create(PLAYER_NUMBER_ICON_POS, PLAYER_NUMBER_ICON_SIZE);
	
	// アイコンテクスチャの設定
	if (m_pPlayerNumIcon != NULL)
	{
		// テクスチャ分岐
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

	// 動けるフラグの初期化
	m_bMove = false;

	// アニメーションの生成
	for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
	{
		m_apMotion[nCntAnim] = CMotion::Create(GetPartsNum(), m_achAnimPath[nCntAnim], GetModelData());
	}

	SetMotion(MOTION_IDOL);

	m_bMove = true;

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CPlayer::Uninit(void)
{
	CModelHierarchy::Uninit();

	// フリッパークラスの終了処理
	if (m_pFlipper != NULL)
	{
		m_pFlipper->Uninit();
		m_pFlipper = NULL;
	}

	// フリッパー移動状態終了処理
	if (m_pFlipperMoveState != NULL)
	{
		m_pFlipperMoveState->Uninit();
		m_pFlipperMoveState = NULL;
	}
	
	// アイコンの解放
	if (m_pPlayerNumIcon != NULL)
	{
		m_pPlayerNumIcon->Uninit();
		delete m_pPlayerNumIcon;
		m_pPlayerNumIcon = NULL;
	}
}

//******************************
// 更新処理
//******************************
void CPlayer::Update(void)
{
	if (m_bMove)
	{// フラグがtrueの時
		// 羽を動かす
		ControllFlipper();
		// 羽の角度の管理
		ManageFlipperAngle();
	}
	else
	{
		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT , CFlipper::FLIPPER_STATE_NONE);
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT  , CFlipper::FLIPPER_STATE_NONE);
	}

	// プレイヤー番号アイコンの位置の設定
	if (m_pPlayerNumIcon != NULL)
	{
		m_pPlayerNumIcon->SetPos(PLAYER_NUMBER_ICON_POS);
	}

	// アクティブモーションの管理
	if (m_pActiveMotion != NULL && !m_pActiveMotion->GetActiveMotion())
	{// アクティブのモーションが終了したとき
		if (m_pActiveMotion == m_apMotion[MOTION_FALL])
		{// 転ぶモーションからは転がるモーションに移行
			SetMotion(MOTION_MINIRESULT_4);
			D3DXVECTOR3 rot = GetRot();
			m_pActiveMotion->Update();
		}
		else
		{// アクティブのモーションをNULLにする
			m_pActiveMotion = NULL;
		}
	}
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
}

//******************************
// モーションのセット処理
//******************************
void CPlayer::SetMotion(MOTION_TYPE type)
{
	// 現在アクティブのモーションの停止
	if (m_pActiveMotion != NULL)
	{
		if (m_apMotion[type] != m_pActiveMotion)
		{
			m_pActiveMotion->SetActiveMotion(false);
			m_pActiveMotion = NULL;
		}
	}

	// モーションの再生
	if (m_apMotion[type] != NULL)
	{
		if (!m_apMotion[type]->GetActiveMotion())
		{
			m_apMotion[type]->SetActiveMotion(true);
			m_pActiveMotion = m_apMotion[type];
		}
	}
}

//******************************
// モデルの描画処理
//******************************
void CPlayer::DrawModel(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;	//現在のマテリアル保持用
	D3DXMATERIAL*pMat;	//マテリアルデータへのポインタ

	CResourceModel::Model *pModelData = GetModelData();

	for (int nCntParts = 0; nCntParts < GetPartsNum(); nCntParts++)
	{
		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &pModelData[nCntParts].mtxWorld);

		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);

		// シェーダー情報の取得
		CResourceShader::Shader shader = CResourceShader::GetShader(CResourceShader::SHADER_PLAYER);

		if (shader.pEffect != NULL)
		{
			// シェーダープログラムに値を送る
			SetShaderVariable(shader.pEffect, &pModelData[nCntParts]);

			// フェイスパターン
			if (nCntParts != FACE_PARTS_NUMBER)
			{
				shader.pEffect->SetFloat("fTexV", 0.0f);
			}
			else
			{
				shader.pEffect->SetFloat("fTexV", FACE_TEX_V );
			}

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)pModelData[nCntParts].pBuffMat->GetBufferPointer();

			// パス数の取得
			UINT numPass = 0;
			shader.pEffect->Begin(&numPass, 0);

			// パス数分描画処理のループ
			for (int nCntEffect = 0; nCntEffect < (int)numPass; nCntEffect++)
			{
				for (int nCntMat = 0; nCntMat < (int)pModelData[nCntParts].nNumMat; nCntMat++)
				{
					//マテリアルのアンビエントにディフューズカラーを設定
					pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// テクスチャ
					pDevice->SetTexture(0, pModelData[nCntParts].apTexture[nCntMat]);

					// テクスチャをシェーダーに送る
					shader.pEffect->SetTexture("Tex", pModelData[nCntParts].apTexture[nCntMat]);
					// テクスチャをシェーダーに送る
					shader.pEffect->SetTexture("ToonTex", CResourceTexture::GetTexture(CResourceTexture::TEXTURE_TOONSHADOW));
					// 色
					shader.pEffect->SetFloatArray("DiffuseColor", (float*)&pMat[nCntMat].MatD3D.Diffuse, 4);
					// シェーダパスの描画開始
					shader.pEffect->BeginPass(nCntEffect);
					// モデルパーツの描画
					pModelData[nCntParts].pMesh->DrawSubset(nCntMat);
					// シェーダパスの終了
					shader.pEffect->EndPass();

					pMat[nCntMat] = pModelData[nCntParts].defMat[nCntMat];
				}
			}
			// シェーダー終了
			shader.pEffect->End();
		}
		
		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
		// テクスチャの初期化
		pDevice->SetTexture(0, 0);
	}
}

//******************************
// 羽の操作処理
//******************************
void CPlayer::ControllFlipper(void)
{
#ifdef _DEBUG
	// キーボード操作
	// 右羽を操作
	if (CManager::GetKeyboard()->GetKeyPress(DIK_UP))
	{// 上げる
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_UP)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + m_nPlayerNum));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_DOWN))
	{// 下げる
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_DOWN)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + m_nPlayerNum));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
	}

	// 左羽を操作
	if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
	{// 上げる
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_UP)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + m_nPlayerNum));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_S))
	{// 下げる
		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_DOWN)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + m_nPlayerNum));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);

	}

#endif // _DEBUG
	// コントローラー操作
	// 右羽を操作
	if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lRz <= -10)
	{// 上げる

		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_UP)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + m_nPlayerNum));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);

	}
	else if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lRz >= 10)
	{// 下げる

		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] != RIGHT_FLIPPER_DIST_ANGLE_DOWN)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_RIGHT1) + m_nPlayerNum));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
		}
		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);

	}

	// 左羽を操作
	if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lY <= -10)
	{// 上げる

		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_UP)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + m_nPlayerNum));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);

	}
	else if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lY >= 10)
	{// 下げる
		m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;

		if (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] != LEFT_FLIPPER_DIST_ANGLE_DOWN)
		{
			// SE
			CManager::GetSound()->Play((CSound::LABEL)(((int)CSound::LABEL_SE_FLIPPER_LEFT1) + m_nPlayerNum));

			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
		}

		// 移動状態の更新
		m_pFlipperMoveState->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);

	}
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
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z >= RIGHT_FLIPPER_DIST_ANGLE_DOWN - FLIPPER_JUDGE)
	{// 下がっているとき
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
	}
	else
	{// 中間
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPER_STATE_NONE);
	}

	// 右羽の上がっているか下がっているかの判定
	if (pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z >= LEFT_FLIPPER_DIST_ANGLE_UP - FLIPPER_JUDGE)
	{// 上がっているとき
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
	}
	else if (pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z <= LEFT_FLIPPER_DIST_ANGLE_DOWN + FLIPPER_JUDGE)
	{// 下がっているとき
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
	}
	else
	{// 中間
		m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPER_STATE_NONE);
	}
}

//******************************
// シェーダープログラムに値を送る
//******************************
void CPlayer::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
{
	if (pEffect != NULL)
	{
		// シェーダーに情報を渡す
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		mat = pModelData->mtxWorld * (*CManager::GetCamera()->GetViewMtx())* (*CManager::GetCamera()->GetProjectionMtx());
		// ワールドプロジェクション
		pEffect->SetMatrix("WorldViewProj", &mat);
		// ワールド座標
		pEffect->SetMatrix("World", &pModelData->mtxWorld);
		// ライトディレクション
		D3DXVECTOR3 lightDir = LIGHT_DIR_BASE;
		pEffect->SetFloatArray("LightDirection", (float*)&D3DXVECTOR3(lightDir.x, -lightDir.y, -lightDir.z), 3);
		// 視点位置
		D3DXVECTOR3 eye = CManager::GetCamera()->GetPos();
		pEffect->SetFloatArray("Eye", (float*)&eye, 3);
	}
}

//******************************
// モーションのアクティブ状態の取得
//******************************
bool CPlayer::GetMotionActive(MOTION_TYPE type)
{
	return m_apMotion[type]->GetActiveMotion();
}