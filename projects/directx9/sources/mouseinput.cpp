#include "MouseInput.h"

CInputMouse::CInputMouse(void)
{
}

CInputMouse::~CInputMouse(void)
{
}

void CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//������
	m_pDInput = NULL;
	m_pDIDevice = NULL;

	//�쐬
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL);
	
	m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIDevice, NULL);
	m_pDIDevice->SetDataFormat(&c_dfDIMouse2); // �}�E�X�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
	m_pDIDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; // ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS
	m_pDIDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	//���͐���J�n
	m_pDIDevice->Acquire();

	//�z�񏉊���
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
	//�l�̍X�V
	if (FAILED(m_pDIDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &MouseState)))
	{
		m_pDIDevice->Acquire();
	}
	else
	{
		for (int nCntkey = 0; nCntkey < 3; nCntkey++)
		{
			//�g���K�[���̐���
			m_aMouseKeyTrigger[nCntkey] = (MouseState.rgbButtons[nCntkey]^m_aMouseKeyState[nCntkey])&MouseState.rgbButtons[nCntkey];
			//�����[�X���̐���
			m_aMouseKeyRelease[nCntkey] = (MouseState.rgbButtons[nCntkey]^m_aMouseKeyState[nCntkey])&m_aMouseKeyState[nCntkey];
			//�v���X���̐���
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
