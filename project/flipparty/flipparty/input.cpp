//===============================
//
//　入力の処理 [input.cpp]
//	Author:増澤　未来
//
//===============================

//===============================
//インクルード
//===============================
#include "input.h"
#include "keyboard.h"

//===============================
// 静的メンバ変数宣言
//===============================
LPDIRECTINPUT8 CInput::m_pInput = NULL;    // DirectInputポインタ
//CInputKeyboard *CInput::m_pKeybord; // キーボードクラス

//===============================
// コンストラクタ
//===============================
CInput::CInput()
{
	m_pDevice = NULL;
}

//===============================
// デストラクタ
//===============================
CInput::~CInput()
{
}

HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// DirectInputオブジェクトの作成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

void CInput::Uninit(void)
{
	// 入力デバイス(キーボード)の開放
	if (m_pDevice != NULL)
	{
		// キーボードへのアクセス権を開放(入力制御終了)
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}
