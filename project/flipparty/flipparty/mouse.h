//===============================
//
// マウスヘッダ [mouse.h]
// Author:増澤 未来
//
//===============================

// 二重インクルード防止
#ifndef _MOUSE_H_
#define _MOUSE_H_

//===============================
// インクルード
//===============================
#include "main.h"
#include "input.h"

//===============================
// マクロ定義
//===============================
#define MAX_MOUSE_BOTTON 3           // マウスボタンの最大数

//===============================
// クラス定義
//===============================

//マウスクラス
class CInputMouse : public CInput
{
public:
	//============
	// メンバ関数
	//============
	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd); // 初期化
	void Uninit(void);                            // 終了
	void Update(void);                            // 更新

	bool GetMousePress(int nKey);      // プレス情報の取得
	bool GetMouseTrigger(int nKey);    // トリガー情報の取得
	bool GetMouseRelease(int nKey);    // リリース情報の取得
	D3DXVECTOR3 GetMousePos(void);     // マウスカーソル座標の取得
	void SetMousePos(D3DXVECTOR3 pos); // マウスカーソル座標のセット
	D3DXVECTOR3 GetMouseMove(void);    // マウスの移動量の取得
private:
	// メンバ変数
	BYTE m_aMouseState[MAX_MOUSE_BOTTON];          // キーボードの入力情報ワーク
	BYTE m_aMouseStateTrigger[MAX_MOUSE_BOTTON];   // キーボードのトリガー情報
	BYTE m_aMouseStateRelease[MAX_MOUSE_BOTTON];   // キーボードのリリース情報
	DIMOUSESTATE m_mousState;                      // マウス状態
};

#endif