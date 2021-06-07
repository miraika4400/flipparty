////////////////////////////////////////////////////
//
//    motionクラスの処理[motion.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "motion.h"
#include "debug_log.h"

//*****************************
// マクロ定義
//*****************************

//*****************************
// 静的メンバ変数宣言
//*****************************

//******************************
// コンストラクタ
//******************************
CMotion::CMotion() :CScene(OBJTYPE_MOTION)
{
	// メンバ変数のクリア
	m_pModel = NULL;                              // モデル情報
	m_nNumKey = 0;                                // キーフレームの数 
	m_nNumParts = 0;                              // パーツ数
	m_bMotion = false;                              // アニメーションしているか
	m_bLoop = false;                              // ループするか
	m_nCntKey = 0;                                // キーカウント
	m_nCntFrame = 0;                              // フレームカウント
	memset(&m_pos, 0, sizeof(m_pos));             // 座標
	memset(&m_rot, 0, sizeof(m_rot));             // 回転
	memset(&m_addPos, 0, sizeof(m_addPos));       // 座標の加算値
	memset(&m_addRot, 0, sizeof(m_addRot));       // 回転の加算値
	memset(&m_nNumFrame, 0, sizeof(m_nNumFrame)); // フレーム数
}

//******************************
// デストラクタ
//******************************
CMotion::~CMotion()
{
}

//******************************
// クリエイト
//******************************
CMotion * CMotion::Create(int nNumParts, const char *pPath, CResourceModel::Model*pModel)
{
	// メモリの確保
	CMotion *pAnimation;
	pAnimation = new CMotion;

	// 引数の代入
	pAnimation->m_nNumParts = nNumParts;
	pAnimation->m_pModel = pModel;
	// アニメーションの読み込み
	pAnimation->Load(pPath);
	// 初期化
	pAnimation->Init();

	return pAnimation;
}


//******************************
// 初期化処理
//******************************
HRESULT CMotion::Init(void)
{
	// 変数の初期化
	m_nCntKey = 0;    // キーカウント
	m_nCntFrame = 0;  // フレームカウント

					  // 加算値の初期化
	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		//m_pModel[nCntParts].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_addRot[nCntParts] = (m_rot[m_nCntKey][nCntParts] - m_pModel[nCntParts].rot) / (float)m_nNumFrame[m_nCntKey];
	}

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CMotion::Uninit(void)
{
	Release();
}

//******************************
// 更新処理
//******************************
void CMotion::Update(void)
{
	if (m_bMotion)
	{

		// フレームカウントを進める
		m_nCntFrame++;
		if (m_nCntFrame >= m_nNumFrame[m_nCntKey])
		{
			m_nCntFrame = 0;
			// キーカウントを進める
			m_nCntKey++;

			if (m_nCntKey >= m_nNumKey)
			{// 一周終えてループしないとき
				if (!m_bLoop)
				{
					// アニメーションの終了
					m_bMotion = false;
					return;
				}
				else
				{
					m_nCntKey = 0;
				}
			}

			// 加算値の更新
			for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
			{
				if (m_nCntKey == 0)
				{// 一番最初のフレーム
					m_addPos[nCntParts] = (m_pos[m_nCntKey][nCntParts] - m_pos[m_nNumKey - 1][nCntParts]) / (float)m_nNumFrame[m_nCntKey];
					m_addRot[nCntParts] = (m_rot[m_nCntKey][nCntParts] - m_rot[m_nNumKey - 1][nCntParts]) / (float)m_nNumFrame[m_nCntKey];
				}
				else
				{
					// グルんと回転しないよう調整
					if (m_rot[m_nCntKey][nCntParts].y - m_pModel[nCntParts].rot.y > D3DXToRadian(180))
					{
						m_pModel[nCntParts].rot.y += D3DXToRadian(360);
					}
					if (m_rot[m_nCntKey][nCntParts].y - m_pModel[nCntParts].rot.y < D3DXToRadian(-180))
					{
						m_pModel[nCntParts].rot.y -= D3DXToRadian(360);
					}

					m_addPos[nCntParts] = (m_pos[m_nCntKey][nCntParts] - m_pos[m_nCntKey - 1][nCntParts]) / (float)m_nNumFrame[m_nCntKey];
					m_addRot[nCntParts] = (m_rot[m_nCntKey][nCntParts] - m_pModel[nCntParts].rot) / (float)m_nNumFrame[m_nCntKey];
				}
			}
		}

		// 加算値を足す
		for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
		{
			m_pModel[nCntParts].pos += m_addPos[nCntParts];
			m_pModel[nCntParts].rot += m_addRot[nCntParts];
		}
	}
}

//******************************
// 描画処理
//******************************
void CMotion::Draw(void)
{
}

//******************************
// アニメーションのセット
//******************************
void CMotion::SetActiveMotion(bool bActive)
{
	//　引数の代入
	m_bMotion = bActive;
	if (m_bMotion)
	{
		// 初期化
		Init();
	}
}

void CMotion::Load(const char * pPath)
{
	// ファイルオープン
	FILE*pFile = NULL;
	pFile = fopen(pPath, "r");

	if (pFile != NULL)
	{
		// テキストファイルの解析

		// 特定の文字判定用
		char chChar[256] = {};
		fscanf(pFile, "%s", chChar);

		// "MOTIONSET"読み込むまでループ
		while (strcmp(chChar, "MOTIONSET") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}
		// "LOOP"読み込むまでループ
		while (strcmp(chChar, "LOOP") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}

		// 読み込んだループ情報の格納用
		int nLoop;
		// = ループするか
		fscanf(pFile, "%*s %d", &nLoop);
		// ループの判定
		if (nLoop == 1)
		{
			m_bLoop = true;
		}
		else
		{
			m_bLoop = false;
		}

		// "NUM_KEY"読み込むまでループ
		while (strcmp(chChar, "NUM_KEY") != 0)
		{
			fscanf(pFile, "%s", chChar);
		}
		// = キー数
		fscanf(pFile, "%*s %d", &m_nNumKey);
		// キーフレーム数分ループ
		for (int nCntKey = 0; nCntKey < m_nNumKey; nCntKey++)
		{
			// "KEYSET"読み込むまでループ
			while (strcmp(chChar, "KEYSET") != 0)
			{
				fscanf(pFile, "%s", chChar);
			}

			// "FRAME"読み込むまでループ
			while (strcmp(chChar, "FRAME") != 0)
			{
				fscanf(pFile, "%s", chChar);
			}
			fscanf(pFile, "%*s %d", &m_nNumFrame[nCntKey]);

			// パーツ数分ループ
			for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
			{
				// "KEY"読み込むまでループ
				while (strcmp(chChar, "KEY") != 0)
				{
					fscanf(pFile, "%s", chChar);
				}
				// 配列番号
				int nIndex = 0;
				fscanf(pFile, "%*s %*s [ %d ] %*s", &nIndex);
				// 座標
				fscanf(pFile, "%*s %*s %f %f %f", &m_pos[nCntKey][nIndex].x, &m_pos[nCntKey][nIndex].y, &m_pos[nCntKey][nIndex].z);
				// 回転
				fscanf(pFile, "%*s %*s %f %f %f", &m_rot[nCntKey][nIndex].x, &m_rot[nCntKey][nIndex].y, &m_rot[nCntKey][nIndex].z);

				// "END_KEY"読み込むまでループ
				while (strcmp(chChar, "END_KEY") != 0)
				{
					fscanf(pFile, "%s", chChar);
				}
			}
		}
		// ファイルクローズ
		fclose(pFile);
	}
}
