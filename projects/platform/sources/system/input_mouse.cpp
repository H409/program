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
		m_aPrevMouseKeyState[nCnt] = 0;
	}
}

void InputMouse::Uninit(void)
{
	
}

void InputMouse::Update(void)
{
	DIMOUSESTATE2 MouseState;

	//1�t���[���O�̃}�E�X�|�W�V�����A�L�[�X�e�[�g�ۑ�
	m_Prev_Mousepos = m_Mousepos;
	for (int nCntkey = 0; nCntkey < (u32)MOUSE_KEY::MAX; nCntkey++)
	{
		m_aPrevMouseKeyState[nCntkey] = m_aMouseKeyState[nCntkey];

	}

	//�}�E�X�̃|�W�V�����擾
	POINT Mousepos;

	GetCursorPos(&Mousepos);
	ScreenToClient(m_hWnd, &Mousepos);
	m_Mousepos = float2((f32)Mousepos.x,(f32)Mousepos.y);

	//�l�̍X�V
	if (FAILED(m_pDIDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &MouseState)))
	{

		m_pDIDevice->Acquire();

		//�z�񏉊���
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
			//�g���K�[���̐���
			m_aMouseKeyTrigger[nCntkey] = (MouseState.rgbButtons[nCntkey]^m_aMouseKeyState[nCntkey])&MouseState.rgbButtons[nCntkey];
			//�����[�X���̐���
			m_aMouseKeyRelease[nCntkey] = (MouseState.rgbButtons[nCntkey]^m_aMouseKeyState[nCntkey])&m_aMouseKeyState[nCntkey];
			//�v���X���̐���
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
// �}�E�X�h���b�O�A�N�V�����̉����x�擾
//�h���b�O�����Ă��Ȃ��ꍇ�� D3DXVECTOR2(0.0f,0.0f)��Ԃ�
//*****************************************************************************
const float3& InputMouse::GetDiff(void)const
{
	return m_MouseDiff;
}
