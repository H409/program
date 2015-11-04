#include "MouseInput.h"

CInputMouse::CInputMouse(void)
{
}

CInputMouse::~CInputMouse(void)
{
}

void CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//初期化
	m_pDInput = NULL;
	m_pDIDevice = NULL;

	//作成
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL);
	
	m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIDevice, NULL);
	m_pDIDevice->SetDataFormat(&c_dfDIMouse2); // マウス用のデータ・フォーマットを設定
	m_pDIDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; // 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS
	m_pDIDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	//入力制御開始
	m_pDIDevice->Acquire();

	//配列初期化
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_aMouseKeyTrigger[nCnt] = 0;
		m_aMouseKeyRelease[nCnt] = 0;
		m_aMouseKeyState[nCnt] = 0;
	}
}

void CInputMouse::Uninit(void)
{
	if (m_pDIDevice != NULL)
	{
		m_pDIDevice->Release();
		m_pDIDevice->Unacquire();
		m_pDIDevice = NULL;
	}

	if (m_pDInput != NULL)
	{
		m_pDInput->Release();
		m_pDInput = NULL;
	}
}

void CInputMouse::Update(void)
{
	DIMOUSESTATE2 MouseState;
	//値の更新
	if (FAILED(m_pDIDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &MouseState)))
	{
		m_pDIDevice->Acquire();
	}
	else
	{
		for (int nCntkey = 0; nCntkey < 3; nCntkey++)
		{
			//トリガー情報の生成
			m_aMouseKeyTrigger[nCntkey] = (MouseState.rgbButtons[nCntkey]^m_aMouseKeyState[nCntkey])&MouseState.rgbButtons[nCntkey];
			//リリース情報の生成
			m_aMouseKeyRelease[nCntkey] = (MouseState.rgbButtons[nCntkey]^m_aMouseKeyState[nCntkey])&m_aMouseKeyState[nCntkey];
			//プレス情報の生成
			m_aMouseKeyState[nCntkey] = MouseState.rgbButtons[nCntkey];
			
		}
	}
}

D3DXVECTOR2 CInputMouse::GetMousePosition(void)
{
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(m_hWnd, &pos);
	return D3DXVECTOR2((float)pos.x, (float)pos.y);
}

bool CInputMouse::GetMousePress(MOUSE_KEY nKey)
{
	if (m_aMouseKeyState[nKey] & 0x080)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CInputMouse::GetMouseTrigger(MOUSE_KEY nKey)
{
	if (m_aMouseKeyTrigger[nKey] & 0x080)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CInputMouse::GetMouseRepeat(MOUSE_KEY nKey)
{
	
	return false;
}

bool CInputMouse::GetMouseRelease(MOUSE_KEY nKey)
{
	if (m_aMouseKeyRelease[nKey] & 0x080)
	{
		return true;
	}
	else
	{
		return false;
	}
}
