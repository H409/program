//ヘッダーインクルード
#include "CInput.h"

LPDIRECTINPUT8 CInput::m_pDInput = NULL;

HRESULT CInput::Init(HINSTANCE hInstance,HWND hWnd)
{
	if(m_pDInput == NULL)
	{
		// 「DirectInput」オブジェクトの作成
		 if( FAILED(  DirectInput8Create( GetModuleHandle(NULL), 
			 DIRECTINPUT_VERSION,IID_IDirectInput8, (VOID**)&m_pDInput, NULL ) ) )
		 {
			 MessageBox(hWnd,"オブジェクト生成失敗","ERROR",MB_OK);
			 return E_FAIL;
		 }
	}
   
	return S_OK;
}
void CInput::Uninit()
{
	// DirectInputオブジェクトの開放
	SAFE_RELEASE(m_pDInput);

}
