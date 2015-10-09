//�w�b�_�[�C���N���[�h
#include "CInputKeyboard.h"

CInputKeyboard* CInputKeyboard::m_Instance = NULL;

CInputKeyboard* CInputKeyboard::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new CInputKeyboard();
	}
	return m_Instance;
}
void CInputKeyboard::deleteInstance()
{
	if(m_Instance != NULL)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}


HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance,hWnd);

	// �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
    if( FAILED( m_pDInput->CreateDevice( GUID_SysKeyboard,
		&m_pDIDevice, NULL ) ) )
	{
		MessageBox(hWnd,"�f�o�C�X�������s","ERROR",MB_OK);
		return E_FAIL;
	} 
	// �f�o�C�X���L�[�{�[�h�ɐݒ�
    if( FAILED(  m_pDIDevice->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		MessageBox(hWnd,"�t�H�[�}�b�g���s","ERROR",MB_OK);
		return E_FAIL;
	}
	// �������x���̐ݒ�
    if( FAILED( m_pDIDevice->SetCooperativeLevel( 
		hWnd,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND )) )
	{
		MessageBox(hWnd,"�������[�h�̐ݒ莸�s","ERROR",MB_OK);
		return E_FAIL;
	}
	// �f�o�C�X���u�擾�v����
    m_pDIDevice->Acquire();

	for(int i = 0;i < KEY_MAX;i++)
	{
		
		m_nKeyCounter[i] = 0;
	}
	return S_OK;
}
//�J��
void CInputKeyboard::Uninit()
{
	CInput::Uninit();

	if(m_pDIDevice != NULL)
	{
		m_pDIDevice->Unacquire();
		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}
}
//�X�V
void CInputKeyboard::Update()
{
	//�ϐ��錾
	BYTE aKeyState[KEY_MAX];
	
	if(SUCCEEDED(m_pDIDevice->GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		//�L�[���̐ݒ�ƕۑ�
		for(int nkey = 0;nkey < KEY_MAX;nkey++)
		{	
			
			//�g���K�[�L�[
			m_aTrigKey[nkey] = ((m_aKeyState[nkey]^aKeyState[nkey])&aKeyState[nkey]);
			//�����[�X�L�[
			m_aReleaseKey[nkey] = ((m_aKeyState[nkey]^aKeyState[nkey])&m_aKeyState[nkey]);
			
			//���s�[�g�L�[
			//g_RepeatKey[nkey] = (g_aKeyState[nkey] & aKeyState[nkey];
			
			if(m_aKeyState[nkey] && m_nKeyCounter[nkey] >= 30)
			{
				
				//���s�[�g�L�[
				m_RepeatKey[nkey] = (aKeyState[nkey] & m_aKeyState[nkey]);
				
			}
			else if(m_aKeyState[nkey])
			{
				m_nKeyCounter[nkey]++;
			}
			
			//�O�t���[���̏���ݒ�
			m_aKeyState[nkey] = aKeyState[nkey];
		}
	}
	else
	{
		m_pDIDevice->Acquire();
	}
}

	

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	if(m_aKeyState[nKey] & 0x80)
	{
		return true;
	}
	return false;
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	if(m_aTrigKey[nKey] & 0x80)
	{
		m_nKeyCounter[nKey] = 0;
		return true;
	}
	return false;
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool CInputKeyboard::GetKeyboardRepeat(int nKey)
{
	if(m_RepeatKey[nKey] & 0x80)
	{
		return true;
	}

	return false;
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	if(m_aReleaseKey[nKey] & 0x80)
	{
		return true;
	}
	return false;
}