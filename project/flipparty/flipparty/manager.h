//=============================================================================
//
// マネージャーヘッダ [manager.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================
// インクルード
//=============================
#include "main.h"

//=============================
// 前方宣言
//=============================1
class CRenderer;
class CInputKeyboard;
class CInputJoypad;
class CInputMouse;
class CSound;
class CGame;
class CTitle;
class CResult;
class CFade;
class CTutorial;
class CPause;

//=============================
// クラス定義
//=============================

// マネージャークラス
class CManager
{
public:
	//============
	// 状態列挙
	//============
	// 画面遷移モード
	typedef enum
	{
		MODE_TITLE = 0, // タイトル
		MODE_TUTORIAL,  // チュートリアル
		MODE_GAME,      // ゲーム
		MODE_RESULT,    // リザルト
		MODE_MAX,       // モードの最大数
	}MODE;


	//============
	// メンバ関数
	//============
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow) ;// 初期化
	void Uninit(void);                                          // 終了
	void Update(void);                                          // 更新
	void Draw(void);                                            // 描画

	static void SetMode(MODE mode);              // モードのセット
	static MODE GetMode(void) { return m_mode; } // モード取得

	// 各ポインタの取得処理
	static CRenderer *GetRenderer(void) { return m_pRenderer; }            // レンダラーの取得処理
	static CInputKeyboard *GetKeyboard(void) { return m_pInputKeyboard; }  // キーボードの取得処理
	static CInputJoypad *GetJoypad(void) { return m_pJoypad; }             // ジョイパッドの取得処理
	static CInputMouse *GetMouse(void) { return m_pInputMouse; }           // マウスの取得処理
	static CSound *GetSound(void) { return m_pSound; }                     // ジョイパッドの取得処理
	static CGame *GetGame(void) { return m_pGame; }                        // ゲームの取得処理
	static CFade * GetFade(void) { return m_pFade; }                       // フェードの取得処理
	static CPause * GetPause(void) { return m_pPause; }                    // ポーズの取得処理
	static void SetActivePause(bool bPause) { m_bPause = bPause; }         // ポーズのセット
	static bool GetActivePause(void) { return m_bPause; }                  // フェードの取得処理

private:
	//============
	// メンバ変数
	//============
	static MODE m_mode;                      // モード

	static CRenderer *m_pRenderer;           // レンダラーポインタ
	static CInputKeyboard *m_pInputKeyboard; // キーボードポインタ
	static CInputJoypad*m_pJoypad;           // ジョイパッドポインタ
	static CInputMouse *m_pInputMouse;       // マウスポインタ
	static CSound*m_pSound;                  // サウンドポインタ
	static CGame*m_pGame;                    // ゲームクラスのポインタ
	static CTitle*m_pTitle;                  // タイトルクラスのポインタ
	static CResult*m_pResult;                // タイトルクラスのポインタ
	static CFade*m_pFade;                    // フェードポインタ
	static CTutorial*m_pTutorial;            // チュートリアル
	static CPause*m_pPause;                  // ポーズポインタ
	static bool m_bPause;                    // ポーズフラグ
};

#endif