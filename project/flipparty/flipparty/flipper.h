//=============================================================================
//
// flipperヘッダ [flipper.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _FLIPPER_H_
#define _FLIPPER_H_

//*****************************
//インクルード
//*****************************
#include "main.h"

//*****************************
//クラス定義
//*****************************

// 旗クラス
class CFlipper
{
public:
	//============
	// 列挙
	//============
	typedef enum
	{
		FLIPPER_TYPE_LEFT = 0,  // 左
		FLIPPER_TYPE_RIGHT,     // 右
		FLIPPER_TYPE_MAX
	}FLIPPER_TYPE;

	// 旗あげ状態
	typedef enum
	{
		FLIPPER_STATE_NONE = 0, // none
		FLIPPERSTATE_UP,       // 上がってる
		FLIPPERSTATE_DOWN,     // 下がっている
		FLIPPER_STATE_MAX
	}FLIPPER_STATE;

	//============
	// メンバ関数
	//============

	CFlipper();
	~CFlipper();
	static CFlipper *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了

	// 旗の状態取得・セット
	FLIPPER_STATE GetState(FLIPPER_TYPE type) { return m_flagState[type]; } // 取得 引数:取得したい旗が右か左か
	void SetState(FLIPPER_TYPE type, FLIPPER_STATE state) { m_flagState[type] = state; }// セット 引数:セットしたい旗が右か左か,セットする状態

private:
	//============
	// メンバ変数
	//============
	FLIPPER_STATE m_flagState[FLIPPER_TYPE_MAX];
};

#endif