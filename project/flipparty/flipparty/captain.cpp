////////////////////////////////////////////////////
//
//    captainクラスの処理[captain.cpp]
//    Author:増澤 未来(筒井俊稀)
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "captain.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "game.h"
#include "flipper.h"
#include "flag_raicing_game_rule.h"
#include "resource_shader.h"
#include "resource_texture.h"
#include "game.h"
#include "light.h"
#include "camera_base.h"
#include "motion.h"

//*****************************
// マクロ定義
//*****************************
#define HIERARCHY_TEXT_PATH "./data/Texts/hierarchy/pengin00.txt"    //階層構造テキストのパス
#define RIGHT_FLIPPER_PARTS_NUM 5                                    // 右羽のパーツ番号
#define LEFT_FLIPPER_PARTS_NUM  4                                    // 左羽のパーツ番号
#define RIGHT_FLIPPER_DIST_ANGLE_UP   D3DXToRadian(-60.0f)           // 右羽を上げたときの角度
#define RIGHT_FLIPPER_DIST_ANGLE_DOWN D3DXToRadian(30.0f)            // 右羽を下げたときの角度
#define LEFT_FLIPPER_DIST_ANGLE_UP    -RIGHT_FLIPPER_DIST_ANGLE_UP   // 左羽を上げたときの角度
#define LEFT_FLIPPER_DIST_ANGLE_DOWN  -RIGHT_FLIPPER_DIST_ANGLE_DOWN // 左羽を下げたときの角度
#define FLIPPER_RATE 0.07f                                           // 羽を動かすときの係数
#define FLIPPER_JUDGE D3DXToRadian(20.0f)                            // 上がっているか下がっているか判定の基準値
#define FACE_PARTS_NUMBER 3  // 表情パーツのパーツ番号
#define FACE_PATTERN 3       // 表情パターン数
#define FACE_TEX_V (1.0f/(float)FACE_PATTERN) * (float)m_facePattern
#define SCALE_VALUE 1.2f	//モデルのサイズ拡大係数

//*****************************
// 静的メンバ変数宣言
//*****************************
CResourceModel::Model CCaptain::m_model[MAX_PARTS_NUM] = {};
int CCaptain::m_nPartsNum = 0;
char CCaptainm_achAnimPath[64]
{
	 "./data/Texts/motion/idol.txt"          // 待機アニメーション
};

//******************************
// コンストラクタ
//******************************
CCaptain::CCaptain() :CModelHierarchy(OBJTYPE_CPU)
{
	// 変数のクリア
	m_pFlipper = NULL;
	ZeroMemory(&m_fFlipperDist, sizeof(m_fFlipperDist)); // 羽の角度 目標値
	m_nColor = 0;
	m_nCount = 0;
	m_nChoice = 0;
	m_facePattern = 0;

	m_bJudgRed = false;
	m_bJudgWhite = false;

	m_eColorRed = RED_FLAG_DOWN;
	m_eColorWhite = WHITE_FLAG_DOWN;

	m_pMotion = NULL;
}

//******************************
// デストラクタ
//******************************
CCaptain::~CCaptain()
{
}

//******************************
// クリエイト
//******************************
CCaptain * CCaptain::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CCaptain *pCaptain;
	pCaptain = new CCaptain;

	// 初期化
	pCaptain->Init();

	// 各値の代入・セット
	pCaptain->SetPos(pos);
	pCaptain->SetPriority(OBJTYPE_CPU); // オブジェクトタイプ

	return pCaptain;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CCaptain::Load(void)
{

	// モデルの読み込み
	LoadModels(HIERARCHY_TEXT_PATH, &m_model[0], &m_nPartsNum);

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CCaptain::Unload(void)
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
HRESULT CCaptain::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nPartsNum, &m_model[0], HIERARCHY_TEXT_PATH)))
	{
		return E_FAIL;
	}

	for (int nCnt = 0; nCnt < MAX_PARTS_NUM; nCnt++)
	{
		m_model[nCnt].size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	// フリッパークラスの生成
	m_pFlipper = CFlipper::Create();

	// 羽の目標角度の初期化
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = 0.0f;
	m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = 0.0f;

	// 表情の初期化
	m_facePattern = 0;

	//　モーションの設定
	m_pMotion = CMotion::Create(GetPartsNum(), CCaptainm_achAnimPath, GetModelData());
	m_pMotion->SetActiveMotion(true);

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CCaptain::Uninit(void)
{
	CModelHierarchy::Uninit();
	// フリッパークラスの終了処理
	if (m_pFlipper != NULL)
	{
		m_pFlipper->Uninit();
		m_pFlipper = NULL;
	}
}

//******************************
// 更新処理
//******************************
void CCaptain::Update(void)
{
    // キャプテンが動く処理
	if (CFlagRaicingGame_rule::GetGameLoop() == CFlagRaicingGame_rule::CAPTAIN_TRUN)
	{
		// 全部下げている状態
		Judge(RED_FLAG_DOWN, WHITE_FLAG_DOWN, WHITE_DOWN, RED_DOWN);
		// 白だけ上げている状態
		Judge(RED_FLAG_DOWN, WHITE_FLAG_UP, WHITE_UP, RED_DOWN);
		// 赤だけ上げている状態
		Judge(RED_FLAG_UP, WHITE_FLAG_DOWN, WHITE_DOWN, RED_UP);
		// どちらも上がっている状態
		Judge(RED_FLAG_UP, WHITE_FLAG_UP, WHITE_UP, RED_UP);

        // プレイヤーのターンに変更
		CFlagRaicingGame_rule::SetGameLoop(CFlagRaicingGame_rule::PLAYER_TRUN);
	}

	// 旗上げ判定処理
	FlagJudge();
	// 羽の角度の管理
	ManageFlipperAngle();
}

//******************************
// 描画処理
//******************************
void CCaptain::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Zバッファ設定の保存用変数
	DWORD dwCurZTest = 0;

	//Zバッファの設定を一時保存
	pDevice->GetRenderState(D3DRS_ZFUNC, &dwCurZTest);

	//Zテストの設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);	//Zバッファへの書き込みを禁止する

	//ステンシルテストの設定
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);				//ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x05);				//ステンシルバッファへ反映する参照値の設定
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);			//マスクの設定（ビットを削らないように指定）
	pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);	//0xffffffffにする
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);		//ステンシルテストの判定を必ず成功するように指定

	//テストの結果の組み合わせ設定
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		//ステンシル・Zテストともに失敗した場合
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);	//ステンシルのみ成功した場合
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);		//両方とも成功した場合

	//モデルサイズの取得
	D3DXVECTOR3 size = CModelHierarchy::GetSize();

	//アウトライン用にサイズを拡大
	CModelHierarchy::SetSize(size * SCALE_VALUE);

	//位置の取得
	D3DXVECTOR3 pos = CModelHierarchy::GetPos();

	//位置を修正して渡す
	CModelHierarchy::SetPos(D3DXVECTOR3(pos.x, pos.y - 8.0f, pos.z));

	//ステンシルバッファへ描画
	CModelHierarchy::Draw();
	
	//位置を戻す
	CModelHierarchy::SetPos(pos);
	
	//サイズを戻す
	CModelHierarchy::SetSize(size);
	
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);				//ステンシルバッファへ反映する参照値の設定
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);			//マスクの設定（ビットを削らないように指定）
	pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);	//0xffffffffにする
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);		//ステンシルテストの判定を必ず成功するように指定
	
	//テストの結果の組み合わせ設定
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		//ステンシル・Zテストともに失敗した場合
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);	//ステンシルのみ成功した場合
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);		//両方とも成功した場合

	pDevice->SetRenderState(D3DRS_ZFUNC, dwCurZTest);		//Zバッファの設定を戻す

	//Zバッファへ通常描画
	CModelHierarchy::Draw();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);	//ステンシルテストを無効にする
}

//******************************
// 色判別処理
//******************************
void CCaptain::Judge(FLAG ColorFlagRed, FLAG ColorFlagWhite, COLOR ColorRed, COLOR ColorWhite)
{
	// 全部下げている状態
	if (m_eColorRed == ColorFlagRed && m_eColorWhite == ColorFlagWhite)
	{
		while (true)
		{
			// 色判定
			m_nColor = rand() % 4 + 1;
			if (m_nColor != ColorRed && m_nColor != ColorWhite)
			{
				break;
			}
		}
	}
}

//******************************
// 下げているか上げているかの確認
//******************************
void CCaptain::JudgeColor(FLAG ColorFlagRed, FLAG ColorFlagWhite, COLOR ColorRed, COLOR ColorWhite)
{

}

//******************************
// 旗上げ判定処理
//******************************
void CCaptain::FlagJudge()
{
	// 旗上げ判定処理
	switch (m_nColor)
	{
		// 青上げ
	case WHITE_UP:
		if (!m_bJudgWhite)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_UP;
			m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_UP);
			m_eColorWhite = WHITE_FLAG_UP;
			m_bJudgWhite = true;
		}
		break;
		// 青下げ
	case WHITE_DOWN:
		if (m_bJudgWhite)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] = RIGHT_FLIPPER_DIST_ANGLE_DOWN;
			m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_RIGHT, CFlipper::FLIPPERSTATE_DOWN);
			m_eColorWhite = WHITE_FLAG_DOWN;
			m_bJudgWhite = false;
		}
		break;
		// 赤上げ
	case RED_UP:
		if (!m_bJudgRed)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_UP;
			m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_UP);
			m_eColorRed = RED_FLAG_UP;
			m_bJudgRed = true;
		}
		break;
		// 赤下げ
	case RED_DOWN:
		if (m_bJudgRed)
		{
			m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] = LEFT_FLIPPER_DIST_ANGLE_DOWN;
			m_pFlipper->SetState(CFlipper::FLIPPER_TYPE_LEFT, CFlipper::FLIPPERSTATE_DOWN);
			m_eColorRed = RED_FLAG_DOWN;
			m_bJudgRed = false;
		}
		break;
	}
}

//******************************
// 羽の角度の管理
//******************************
void CCaptain::ManageFlipperAngle(void)
{
	// モデルデータの取得
	CResourceModel::Model * pModelData = GetModelData();
	// 右羽を動かす
	pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z += (m_fFlipperDist[CFlipper::FLIPPER_TYPE_RIGHT] - pModelData[RIGHT_FLIPPER_PARTS_NUM].rot.z)*FLIPPER_RATE;
	// 左羽を動かす
	pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z += (m_fFlipperDist[CFlipper::FLIPPER_TYPE_LEFT] - pModelData[LEFT_FLIPPER_PARTS_NUM].rot.z)*FLIPPER_RATE;
}

//******************************
// モデルの描画
//******************************
void CCaptain::DrawModel(void)
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
				shader.pEffect->SetFloat("fTexV", FACE_TEX_V);
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
					//モデルパーツの描画
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
// シェーダーに値を送る
//******************************
void CCaptain::SetShaderVariable(LPD3DXEFFECT pEffect, CResourceModel::Model * pModelData)
{
	if (pEffect != NULL)
	{
		// シェーダーに情報を渡す
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		mat = pModelData->mtxWorld * (*CGame::GetCamera()->GetViewMtx())* (*CGame::GetCamera()->GetProjectionMtx());
		// ワールドプロジェクション
		pEffect->SetMatrix("WorldViewProj", &mat);
		// ワールド座標
		pEffect->SetMatrix("World", &pModelData->mtxWorld);
		// ライトディレクション
		D3DXVECTOR3 lightDir = CGame::GetLight()->GetDir();
		pEffect->SetFloatArray("LightDirection", (float*)&D3DXVECTOR3(lightDir.x, -lightDir.y, -lightDir.z), 3);
		// 視点位置
		D3DXVECTOR3 eye = CGame::GetCamera()->GetPos();
		pEffect->SetFloatArray("Eye", (float*)&eye, 3);
	}
}

