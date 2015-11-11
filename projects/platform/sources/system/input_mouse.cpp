#include "input_mouse.h"

InputMouse::InputMouse(void)
{
}

InputMouse::~InputMouse(void)
{
}

void InputMouse::Init(HINSTANCE hInstance, HWND hWnd)
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
		m_aPrevMouseKeyState[nCnt] = 0;
	}
}

void InputMouse::Uninit(void)
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

void InputMouse::Update(void)
{
	DIMOUSESTATE2 MouseState;

	//1フレーム前のマウスポジション、キーステート保存
	m_Prev_Mousepos = m_Mousepos;
	for (int nCntkey = 0; nCntkey < 3; nCntkey++)
	{
		m_aPrevMouseKeyState[nCntkey] = m_aMouseKeyState[nCntkey];
	}

	//マウスのポジション取得
	GetCursorPos(&m_Mousepos);
	ScreenToClient(m_hWnd, &m_Mousepos);

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

D3DXVECTOR2 InputMouse::GetPosition(void)
{
	return D3DXVECTOR2((float)m_Mousepos.x, (float)m_Mousepos.y);
}

D3DXVECTOR2 InputMouse::GetPrevPosition(void)
{
	return D3DXVECTOR2((float)m_Prev_Mousepos.x, (float)m_Prev_Mousepos.y);
}

bool InputMouse::GetPress(MOUSE_KEY nKey)const
{
	if (m_aMouseKeyState[(int)nKey] & 0x080)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputMouse::GetTrigger(MOUSE_KEY nKey)const
{
	if (m_aMouseKeyTrigger[(int)nKey] & 0x080)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputMouse::GetRepeat(MOUSE_KEY nKey)const
{
	
	return false;
}

bool InputMouse::GetRelease(MOUSE_KEY nKey)const
{
	if (m_aMouseKeyRelease[(int)nKey] & 0x080)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//*****************************************************************************
// マウスドラッグアクションの加速度取得
//ドラッグをしていない場合は D3DXVECTOR2(0.0f,0.0f)を返す
//*****************************************************************************
D3DXVECTOR2 InputMouse::GetDrag(MOUSE_KEY nKey)
{
	//前フレームから引き続きマウスクリックし続けている場合
	if (m_aPrevMouseKeyState[(int)nKey] && m_aMouseKeyState[(int)nKey])
	{
		//前フレームと現在フレームのマウスカーソルポジションの差分を返す
		return D3DXVECTOR2((float)(m_Mousepos.x - m_Prev_Mousepos.x), (float)(m_Mousepos.y - m_Prev_Mousepos.y));
	}

	//そうでない場合は移動していないので0を返す。
	return D3DXVECTOR2(0.0f, 0.0f);
}
