#include "input_mouse.h"

InputMouse::InputMouse(void)
{
}

InputMouse::~InputMouse(void)
{
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

	//1�t���[���O�̃}�E�X�|�W�V�����A�L�[�X�e�[�g�ۑ�
	m_Prev_Mousepos = m_Mousepos;
	for (int nCntkey = 0; nCntkey < 3; nCntkey++)
	{
		m_aPrevMouseKeyState[nCntkey] = m_aMouseKeyState[nCntkey];
	}

	//�}�E�X�̃|�W�V�����擾
	GetCursorPos(&m_Mousepos);
	ScreenToClient(m_hWnd, &m_Mousepos);

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
// �}�E�X�h���b�O�A�N�V�����̉����x�擾
//�h���b�O�����Ă��Ȃ��ꍇ�� D3DXVECTOR2(0.0f,0.0f)��Ԃ�
//*****************************************************************************
D3DXVECTOR2 InputMouse::GetDrag(MOUSE_KEY nKey)
{
	//�O�t���[��������������}�E�X�N���b�N�������Ă���ꍇ
	if (m_aPrevMouseKeyState[(int)nKey] && m_aMouseKeyState[(int)nKey])
	{
		//�O�t���[���ƌ��݃t���[���̃}�E�X�J�[�\���|�W�V�����̍�����Ԃ�
		return D3DXVECTOR2((float)(m_Mousepos.x - m_Prev_Mousepos.x), (float)(m_Mousepos.y - m_Prev_Mousepos.y));
	}

	//�����łȂ��ꍇ�͈ړ����Ă��Ȃ��̂�0��Ԃ��B
	return D3DXVECTOR2(0.0f, 0.0f);
}
