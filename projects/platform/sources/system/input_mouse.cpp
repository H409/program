#include "input_mouse.h"

InputMouse::InputMouse(void)
{
}

InputMouse::~InputMouse(void)
{
	if (m_pDIDevice != NULL)
	{
		m_pDIDevice->Unacquire();
		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}

	if (m_pDInput != NULL)
	{
		m_pDInput->Release();
		m_pDInput = NULL;
	}
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
	
}

void InputMouse::Update(void)
{
	DIMOUSESTATE2 MouseState;

	//1フレーム前のマウスポジション、キーステート保存
	m_Prev_Mousepos = m_Mousepos;
	for (int nCntkey = 0; nCntkey < (u32)MOUSE_KEY::MAX; nCntkey++)
	{
		m_aPrevMouseKeyState[nCntkey] = m_aMouseKeyState[nCntkey];

	}

	//マウスのポジション取得
	POINT Mousepos;

	GetCursorPos(&Mousepos);
	ScreenToClient(m_hWnd, &Mousepos);
	m_Mousepos = float2((f32)Mousepos.x,(f32)Mousepos.y);

	//値の更新
	if (FAILED(m_pDIDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &MouseState)))
	{

		m_pDIDevice->Acquire();

		//配列初期化
		for (int nCnt = 0; nCnt <(u32)MOUSE_KEY::MAX; nCnt++)
		{
			m_aMouseKeyTrigger[nCnt] = 0;
			m_aMouseKeyRelease[nCnt] = 0;
			m_aMouseKeyState[nCnt] = 0;
			m_aPrevMouseKeyState[nCnt] = 0;
		}
	}
	else
	{
		m_MouseDiff = float3((f32)MouseState.lX,(f32)MouseState.lY,(f32)MouseState.lZ);

		for (int nCntkey = 0; nCntkey < (u32)MOUSE_KEY::MAX; nCntkey++)
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

const float2& InputMouse::GetPosition(void)const
{
	return m_Mousepos;
}

const float2& InputMouse::GetPrevPosition(void)const
{
	return m_Prev_Mousepos;
}

bool InputMouse::GetPress(MOUSE_KEY nKey)const
{
	return (m_aMouseKeyState[(int)nKey] & 0x080);
}

bool InputMouse::GetTrigger(MOUSE_KEY nKey)const
{
	return (m_aMouseKeyTrigger[(int)nKey] & 0x080);
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
const float3& InputMouse::GetDiff(void)const
{
	return m_MouseDiff;
}
