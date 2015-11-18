//=============================================================================
//
// ���͏��� [inputKeyboard.cpp]
// Author : 
//
//=============================================================================
#include "input_keyboard.h"
#pragma warning (disable : 4800)
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �L�[�{�[�h�̃R���X�g���N�^
//=============================================================================
InputKeyboard::InputKeyboard(void)
{
}
//=============================================================================
// �L�[�{�[�h�̃f�X�g���N�^
//=============================================================================
InputKeyboard::~InputKeyboard(void)
{
	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pDInput != NULL)
	{
		m_pDInput->Release();
		m_pDInput = NULL;
	}

	// �f�o�C�X�I�u�W�F�N�g�̊J��
	if (m_pDIDevice != NULL)
	{
		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}
}
//=============================================================================
// �L�[�{�[�h��Init
//=============================================================================
void InputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{

	// DirectInput�I�u�W�F�N�g�̍쐬
	if (m_pDInput == NULL)
	{
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_pDInput, NULL);
	}
	// �f�o�C�X�I�u�W�F�N�g���쐬
	if (m_pDInput != NULL)
	{
		m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL);
		// �f�[�^�t�H�[�}�b�g��ݒ�
		m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);
		// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
		m_pDIDevice->Acquire(); //�L�[�{�[�h�ւ̃A�N�Z�X�����擾

		for (int nCntkey = 0; nCntkey < KEYBOARD_MAX; nCntkey++)
		{
			m_aKeyTrigger[nCntkey] = 0;
			m_aKeyRelease[nCntkey] = 0;
			m_aKeyState[nCntkey] = 0;
			m_aKeyRepeat[nCntkey] = 0;
		}
	}
}
//=============================================================================
// �L�[�{�[�h��Update
//=============================================================================
void InputKeyboard::Update(void)
{
	BYTE aKeyState[256];
	if (FAILED(m_pDIDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		m_pDIDevice->Acquire();
		//������������
		for (int nCntkey = 0; nCntkey < KEYBOARD_MAX; nCntkey++)
		{
			m_aKeyTrigger[nCntkey] = 0;
			m_aKeyRelease[nCntkey] = 0;
			m_aKeyState[nCntkey] = 0;
		}
	}
	else
	{
		for (int nCntkey = 0; nCntkey < KEYBOARD_MAX; nCntkey++)
		{
			//�g���K�[���̍쐬
			m_aKeyTrigger[nCntkey] = (aKeyState[nCntkey] ^ m_aKeyState[nCntkey])&aKeyState[nCntkey];
			//�����[�X���̍쐬
			m_aKeyRelease[nCntkey] = (aKeyState[nCntkey] ^ m_aKeyState[nCntkey])&m_aKeyState[nCntkey];
			//�v���X���̍쐬
			m_aKeyState[nCntkey] = aKeyState[nCntkey];

			//�����[�X���쐬
			if (m_aKeyState[nCntkey] != 0)
			{
				m_KeyCount[nCntkey]++;
			}
			else if (m_aKeyState[nCntkey] == 0)
			{
				m_aKeyRepeat[nCntkey] = 0;
				m_KeyCount[nCntkey] = 0;
			}
		}
	}
}
//=============================================================================
// �L�[�{�[�h��Uninit
//=============================================================================
void InputKeyboard::Uninit(void)
{

}
//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool InputKeyboard::GetPress(int nKey) const
{
	if (m_aKeyState[nKey] & KEY_BIT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool InputKeyboard::GetTrigger(int nKey)const
{
	if (m_aKeyTrigger[nKey] & KEY_BIT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// //�L�[�{�[�h�̃��s�[�g���擾����AnKey�ɃL�[�R�[�h�A
// //count�Ƀ��s�[�g���肷�邽�߂̍Œ�t���[����������
//=============================================================================
bool InputKeyboard::GetRepeat(int nKey, int count)const
{
	if (m_KeyCount[nKey] >= count)
	{
		return true;
	}
	else
	{
		return false;
	}
	/*return m_aKeyboardRepeat[nKey];*/
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool InputKeyboard::GetRelease(int nKey)const
{
	if (m_aKeyRelease[nKey] & KEY_BIT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// �L�[�{�[�h�̃A�N�e�B�x�[�g
//=============================================================================
void InputKeyboard::ReInit(void)
{
	m_pDIDevice->Acquire(); //�L�[�{�[�h�ւ̃A�N�Z�X�����擾
}