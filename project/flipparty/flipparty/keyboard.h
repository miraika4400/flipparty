//===============================
//
// キーボードヘッダ [keyborad.h]
// Author:増澤 未来
//
//===============================

// 二重インクルード防止
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//===============================
// インクルードファイル
//===============================
#include "main.h"
#include "input.h"

//キーボードクラス
class CInputKeyboard : public CInput
{
public:
	//============
	//メンバ関数
	//============
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd); // 初期化
	void Uninit(void);                            // 終了
	void Update(void);                            // 更新
	bool GetKeyPress(int nKey);                   // プレス情報の取得
	bool GetKeyTrigger(int nKey);                 // トリガー情報の取得
	bool GetKeyRelease(int nKey);                 // リリース情報の取得

private:
	//============
	// メンバ変数
	//============
	BYTE m_aKeyState[NUM_KEY_MAX];          // キーボードの入力情報ワーク
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];   // キーボードのトリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];   // キーボードのリリース情報
};

#endif