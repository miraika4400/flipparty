//=============================================================================
//
// debug_logヘッダ [debug_log.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _DEBUG_LOG_H_
#define _DEBUG_LOG_H_

//*****************************
//インクルード
//*****************************
#include "main.h"

//*****************************
//マクロ定義
//*****************************
#define DEBUG_LOG_MAX_STRING 1024

//*****************************
//クラス定義
//*****************************

//デバッグログクラス
class CDebugLog
{
public:
	//============
	// メンバ関数
	//============
	CDebugLog();
	~CDebugLog();

	static HRESULT Init(void);                  // 初期化
	static void Uninit(void);                   // 終了
	static void Print(const char *format, ...); // プリント
	static void Draw(void);                     // 描画

private:
	//============
	// メンバ変数
	//============
	static LPD3DXFONT m_pFont;                       // ファント
	static char       m_aStr[DEBUG_LOG_MAX_STRING];  // 文字列
};

#endif