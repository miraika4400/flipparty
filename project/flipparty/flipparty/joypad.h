//===============================
//
// ジョイパッドヘッダ [joypad.h]
// Author:増澤 未来
//
//===============================

// 二重インクルード防止
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

//===============================
// インクルードファイル
//===============================
#include "main.h"
#include "input.h"

//===============================
//マクロ定義
//===============================
#define MAX_JOYSTICK_NUM 4    // JOYPAD接続上限
#define	NUM_JOY_MAX 31        // ボタンの最大数
#define JOYSTICK_TIP_MAX 1000 // 傾けの値の最大値
#define JOYPAD_SENSI_RATE 45000.0f // コントローラーのスティックの感度

//ジョイパッドクラス
class CInputJoypad : public CInput
{
public:
	//============
	// メンバ関数
	//============
	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd); // 初期化
	void Uninit(void);                            // 終了
	void Update(void);                            // 更新

	bool GetJoystickPress(int nKey, int nId);     // プレス情報の取得
	bool GetJoystickTrigger(int nKey, int nId);   // トリガー情報の取得
	bool GetJoystickRelease(int nKey, int nId);   // リリース情報の取得

	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext); // ジョイパッドの列挙
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);      // ジョイパッドの値の設定
	static DIJOYSTATE CInputJoypad::GetStick(const int nID);                                          // スティックの取得
private:
	//============
	// メンバ変数
	//============
	BYTE m_aJoyState[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};          // ジョイパッドの入力情報ワーク
	BYTE m_aJoyStateTrigger[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // ジョイパッドのトリガー情報
	BYTE m_aJoyStateRelease[NUM_JOY_MAX][MAX_JOYSTICK_NUM] = {};   // ジョイパッドのリリース情報

	static LPDIRECTINPUTDEVICE8 m_apDevice[MAX_JOYSTICK_NUM]; // デバイス
	static int m_nJoyStickCont;                               // 接続台数
	DIDEVCAPS   m_diDevCaps;


};

#endif