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
		FLAG_TYPE_LEFT = 0,  // 左
		FLAG_TYPE_RIGHT,     // 右
		FLAG_TYPE_MAX
	}FLAG_TYPE;

	// 旗あげ状態
	typedef enum
	{
		FLAG_STATE_NONE = 0, // none
		FLAG_STATE_UP,       // 上がってる
		FLAG_STATE_DOWN,     // 下がっている
		FLAG_STATE_MAX
	}FLAG_STATE;

	//============
	// メンバ関数
	//============

	CFlipper();
	~CFlipper();
	static CFlipper *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了

	// 旗の状態取得・セット
	FLAG_STATE GetState(FLAG_TYPE type) { return m_flagState[type]; } // 取得 引数:取得したい旗が右か左か
	void SetState(FLAG_TYPE type, FLAG_STATE state) { m_flagState[type] = state; }// セット 引数:セットしたい旗が右か左か,セットする状態

private:
	//============
	// メンバ変数
	//============
	FLAG_STATE m_flagState[FLAG_TYPE_MAX];
};

#endif