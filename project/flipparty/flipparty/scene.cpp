//=================================================
//
//    sceneクラスの処理[scene.cpp]
//    Author:増澤 未来
//
//=================================================

//***********************************
// インクルード
//***********************************
#include "scene.h"
#include "scene2d.h"
#include "debug_log.h"

//***********************************
//静的メンバ変数宣言
//***********************************
//CScene *CScene::m_apScene[MAX_SCENE] = {};
CScene * CScene::m_pTop[PRIORITY_NUM] = {};                // 先頭
CScene * CScene::m_pCur[PRIORITY_NUM] = {};                // 最後
int CScene::m_nIDAll = 0;
//===================================
// コンストラクタ
//===================================
CScene::CScene(int nPriority)
{
	// プライオリティの設定
	m_nPriority = nPriority;

	// 消すフラグ初期化
	m_bReleasFlag = false;

	if (m_pTop[m_nPriority] == NULL)
	{// 最初が空の時

	 // 最初にオブジェクトに自分を入れる
		m_pTop[m_nPriority] = this;

		// プレビューをNULLクリア
		m_pPrev = NULL;
	}
	if (m_pCur[m_nPriority] == NULL)
	{// 最後が空の時

	 // 最後にオブジェクトに自分を入れる
		m_pCur[m_nPriority] = this;

		// ネクストをNULLクリア
		m_pNext = NULL;

	}
	else
	{
		// 一個前のポインタ情報の更新
		m_pPrev = m_pCur[m_nPriority];
		// カレントポインタの次のポインタに自分を代入
		m_pCur[m_nPriority]->m_pNext = this;
		// カレントポインタを自分に更新
		m_pCur[m_nPriority] = this;
		// ネクストをNULLクリア
		m_pNext = NULL;
	}

	// IDの設定
	m_nNumID = m_nIDAll;
	m_nIDAll++;
}
//===================================
// デストラクタ
//===================================
CScene::~CScene()
{

}

//====================================
// すべて終了処理
//====================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		CScene*pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			// ネクストの保存
			CScene*pSave = pScene->m_pNext;
			// 終了処理
			pScene->Uninit();
			// リストをつなげなおす
			pScene->ReConnection();
			// オブジェクトの削除
			delete pScene;
			// ネクストの情報を渡す
			pScene = pSave;
		}
	}
}

//====================================
// すべて更新
//====================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		CScene*pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			// ネクストの保存
			CScene*pSave = pScene->m_pNext;

			// 死亡フラグチェック
			if (!pScene->m_bReleasFlag)
			{
				// 終了処理
				pScene->Update();
			}
			// ネクストの情報を渡す
			pScene = pSave;
		}
	}

	// 消滅フラグのチェック
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		// ネクストの保存
		CScene*pScene = m_pTop[nCntPriority];

		while (pScene)
		{
			CScene*pNext = pScene->m_pNext;

			// フラグが立ってたら
			if (pScene->m_bReleasFlag)
			{
				// リストをつなげなおす
				pScene->ReConnection();
				// 終了処理
				delete pScene;
			}
			// ネクストの情報に更新する
			pScene = pNext;
		}
	}
}

//====================================
// すべて描画
//====================================
void CScene::DrawAll(void)
{

	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		CScene*pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			// ネクストの保存
			CScene*pSave = pScene->m_pNext;
			// 死亡フラグチェック
			if (!pScene->m_bReleasFlag)
			{
				// 終了処理
				pScene->Draw();
			}
			// ネクストの情報を渡す
			pScene = pSave;
		}
	}
}

//====================================
// プライオリティの変更
//====================================
void CScene::SetPriority(const int nPriority)
{
	ReConnection();

	// プライオリティの設定
	m_nPriority = nPriority;

	if (m_pTop[m_nPriority] == NULL)
	{// 最初が空の時

	 // 最初にオブジェクトに自分を入れる
		m_pTop[m_nPriority] = this;

		// プレビューをNULLクリア
		m_pPrev = NULL;
	}
	if (m_pCur[m_nPriority] == NULL)
	{// 最後が空の時

	 // 最後にオブジェクトに自分を入れる
		m_pCur[m_nPriority] = this;

		// ネクストをNULLクリア
		m_pNext = NULL;

	}
	else
	{
		// 一個前のポインタ情報の更新
		m_pPrev = m_pCur[m_nPriority];
		// カレントポインタの次のポインタに自分を代入
		m_pCur[m_nPriority]->m_pNext = this;
		// カレントポインタを自分に更新
		m_pCur[m_nPriority] = this;
		// ネクストをNULLクリア
		m_pNext = NULL;
	}
}

//====================================
//メモリの破棄
//====================================
void CScene::Release(void)
{
	// 消すフラグを立てる
	m_bReleasFlag = true;
}

//====================================
// リストの再接続
//====================================
void CScene::ReConnection(void)
{
	// ネクストの情報をつなげる
	if (m_pNext != NULL)
	{
		m_pNext->m_pPrev = m_pPrev;
	}
	// プレビューの情報をつなげる
	if (m_pPrev != NULL)
	{
		m_pPrev->m_pNext = m_pNext;
	}

	if (m_pTop[m_nPriority] == this && m_pCur[m_nPriority] == this)
	{// 自分が先頭且つ最後だった時
		m_pTop[m_nPriority] = NULL;
		m_pCur[m_nPriority] = NULL;
	}
	else if (m_pTop[m_nPriority] == this)
	{// 自分がm_nPriority時
		m_pTop[m_nPriority] = m_pNext;
		if (m_pTop[m_nPriority] != NULL)
		{
			m_pTop[m_nPriority]->m_pPrev = NULL;
		}
	}
	else if (m_pCur[m_nPriority] == this)
	{// 自分が最後だった時
		m_pCur[m_nPriority] = m_pPrev;
		if (m_pCur[m_nPriority] != NULL)
		{
			m_pCur[m_nPriority]->m_pNext = NULL;
		}
	}
}
