//=============================================================================
//
// ���͏��� [inputKeyboard.cpp]
// Author : 
//
//=============================================================================
#include "KeyBoardInput.h"
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
CInputKeyboard::CInputKeyboard(void)
{
}
//=============================================================================
// �L�[�{�[�h�̃R���X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard(void)
{
}
//=============================================================================
// �L�[�{�[�h��Init
//=============================================================================
void CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
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

		for (int nCntkey = 0; nCntkey < 256; nCntkey++)
		{
			m_aKeyTrigger[nCntkey] = 0;
			m_aKeyRelease[nCntkey] = 0;
			m_aKeyState[nCntkey] = 0;
		}
	}
}
//=============================================================================
// �L�[�{�[�h��Update
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[256];
	KeyCount[256];
	if (FAILED(m_pDIDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		m_pDIDevice->Acquire();
	}
	else
	{
		for (int nCntkey = 0; nCntkey < 256; nCntkey++)
		{
			//�g���K�[���̍쐬
			m_aKeyTrigger[nCntkey] = (aKeyState[nCntkey] ^ m_aKeyState[nCntkey])&aKeyState[nCntkey];
			//�����[�X���̍쐬
			m_aKeyRelease[nCntkey] = (aKeyState[nCntkey] ^ m_aKeyState[nCntkey])&m_aKeyState[nCntkey];
			//�v���X���̍쐬
			m_aKeyState[nCntkey] = aKeyState[nCntkey];

			if (m_aKeyState[nCntkey] != 0)
			{
				KeyCount[nCntkey]++;
				if ((KeyCount[nCntkey] == 1) || (KeyCount[nCntkey]>10))
				{
					m_aKeyboardRepeat[nCntkey] = aKeyState[nCntkey];
				}
				else
				{
					m_aKeyboardRepeat[nCntkey] = 0;
				}
			}
			else if (m_aKeyState[nCntkey] == 0)
			{
				m_aKeyboardRepeat[nCntkey] = 0;
				KeyCount[nCntkey] = 0;
			}
		}
	}
}
//=============================================================================
// �L�[�{�[�h��Uninit
//=============================================================================
void CInputKeyboard::Uninit(void)
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
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool CInputKeyboard::GetKeyboardPress(int nKey)
{

	if (m_aKeyState[nKey] & 0x080)
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
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	if (m_aKeyTrigger[nKey] & 0x080)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool CInputKeyboard::GetKeyboardRepeat(int nKey)
{
	return m_aKeyboardRepeat[nKey];
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	if (m_aKeyRelease[nKey] & 0x080)
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
void CInputKeyboard::ReInit(void)
{
	m_pDIDevice->Acquire(); //�L�[�{�[�h�ւ̃A�N�Z�X�����擾
}