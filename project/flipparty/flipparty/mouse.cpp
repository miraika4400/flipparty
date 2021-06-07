//===============================
//
// マウスクラスの処理 [mouse.cpp]
// Author:増澤 未来
//
//===============================

//===============================
// インクルード
//===============================
#include "mouse.h"

//===============================
// マクロ定義
//===============================
#define MOUSE_SEINSI 0.0025f // 操作感度

//===============================
// コンストラクタ
//===============================
CInputMouse::CInputMouse()
{
	memset(m_aMouseState, 0, sizeof(m_aMouseState));
	memset(m_aMouseStateTrigger, 0, sizeof(m_aMouseStateTrigger));
	memset(m_aMouseStateRelease, 0, sizeof(m_aMouseStateRelease));
	memset(m_mousState.rgbButtons, 0, sizeof(m_mousState.rgbButtons));
	m_mousState.lX = 0;
	m_mousState.lY = 0;
	m_mousState.lZ = 0;
}

//===============================
// デストラクタ
//===============================
CInputMouse::~CInputMouse()
{
}

//===============================
// 初期化処理
//===============================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// 入力デバイス（キーボード）の作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}

//===============================
// 終了処理
//===============================
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}

//===============================
// 更新処理
//===============================
void CInputMouse::Update(void)
{
	int nCntKey;
	HRESULT hr;

	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();

		hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_mousState);

		//デバイスからデータを取得
		if (SUCCEEDED(hr))
		{
			for (nCntKey = 0; nCntKey < MAX_MOUSE_BOTTON; nCntKey++)
			{
				//キートリガー
				m_aMouseStateTrigger[nCntKey] = (m_aMouseState[nCntKey] ^ m_mousState.rgbButtons[nCntKey]) &  m_mousState.rgbButtons[nCntKey];

				//キーリリース
				m_aMouseStateRelease[nCntKey] = (m_aMouseState[nCntKey] ^ m_mousState.rgbButtons[nCntKey]) & ~m_mousState.rgbButtons[nCntKey];

				//キープレス情報を保存
				m_aMouseState[nCntKey] = m_mousState.rgbButtons[nCntKey];
			}

		}
		else
		{
			m_pDevice->Acquire();
		}
	}
}

//******************************
// プレス情報の取得
//*****************************
bool CInputMouse::GetMousePress(int nKey)
{
	return m_aMouseState[nKey] & 0x80 ? true : false;
}

//******************************
// トリガー情報の取得
//*****************************
bool CInputMouse::GetMouseTrigger(int nKey)
{
	return m_aMouseStateTrigger[nKey] & 0x80 ? true : false;
}

//******************************
// リリース情報の取得
//******************************
bool CInputMouse::GetMouseRelease(int nKey)
{
	return m_aMouseStateRelease[nKey] & 0x80 ? true : false;
}

//******************************
// マウスカーソル座標の取得
//******************************
D3DXVECTOR3 CInputMouse::GetMousePos(void)
{
	// マウス座標を取得する
	POINT p;
	GetCursorPos(&p);

	// スクリーン座標をクライアント座標に変換する
	ScreenToClient(FindWindowA(WINDOW_CLASS_NAME, nullptr), &p);

	return D3DXVECTOR3((float)p.x, (float)p.y, 0);
}

//******************************
// マウスカーソル座標のセット
//******************************
void CInputMouse::SetMousePos(D3DXVECTOR3 pos)
{
	POINT p;
	p.x = (LONG)pos.x;
	p.y = (LONG)pos.y;
	// クライアント座標をスクリーン座標に変換する
	ClientToScreen(FindWindowA(WINDOW_CLASS_NAME, nullptr), &p);

	SetCursorPos(p.x, p.y);
}

//******************************
// マウスの移動量の取得
//******************************
D3DXVECTOR3 CInputMouse::GetMouseMove(void)
{
	return D3DXVECTOR3((float)m_mousState.lX, (float)m_mousState.lY, (float)m_mousState.lZ) *MOUSE_SEINSI;
}
