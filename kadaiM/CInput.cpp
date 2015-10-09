//�w�b�_�[�C���N���[�h
#include "CInput.h"

LPDIRECTINPUT8 CInput::m_pDInput = NULL;

HRESULT CInput::Init(HINSTANCE hInstance,HWND hWnd)
{
	if(m_pDInput == NULL)
	{
		// �uDirectInput�v�I�u�W�F�N�g�̍쐬
		 if( FAILED(  DirectInput8Create( GetModuleHandle(NULL), 
			 DIRECTINPUT_VERSION,IID_IDirectInput8, (VOID**)&m_pDInput, NULL ) ) )
		 {
			 MessageBox(hWnd,"�I�u�W�F�N�g�������s","ERROR",MB_OK);
			 return E_FAIL;
		 }
	}
   
	return S_OK;
}
void CInput::Uninit()
{
	// DirectInput�I�u�W�F�N�g�̊J��
	SAFE_RELEASE(m_pDInput);

}
