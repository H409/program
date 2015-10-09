//ヘッダーインクルード
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

	// 「DirectInputデバイス」オブジェクトの作成
    if( FAILED( m_pDInput->CreateDevice( GUID_SysKeyboard,
		&m_pDIDevice, NULL ) ) )
	{
		MessageBox(hWnd,"デバイス生成失敗","ERROR",MB_OK);
		return E_FAIL;
	} 
	// デバイスをキーボードに設定
    if( FAILED(  m_pDIDevice->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		MessageBox(hWnd,"フォーマット失敗","ERROR",MB_OK);
		return E_FAIL;
	}
	// 協調レベルの設定
    if( FAILED( m_pDIDevice->SetCooperativeLevel( 
		hWnd,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND )) )
	{
		MessageBox(hWnd,"協調モードの設定失敗","ERROR",MB_OK);
		return E_FAIL;
	}
	// デバイスを「取得」する
    m_pDIDevice->Acquire();

	for(int i = 0;i < KEY_MAX;i++)
	{
		
		m_nKeyCounter[i] = 0;
	}
	return S_OK;
}
//開放
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
//更新
void CInputKeyboard::Update()
{
	//変数宣言
	BYTE aKeyState[KEY_MAX];
	
	if(SUCCEEDED(m_pDIDevice->GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		//キー情報の設定と保存
		for(int nkey = 0;nkey < KEY_MAX;nkey++)
		{	
			
			//トリガーキー
			m_aTrigKey[nkey] = ((m_aKeyState[nkey]^aKeyState[nkey])&aKeyState[nkey]);
			//リリースキー
			m_aReleaseKey[nkey] = ((m_aKeyState[nkey]^aKeyState[nkey])&m_aKeyState[nkey]);
			
			//リピートキー
			//g_RepeatKey[nkey] = (g_aKeyState[nkey] & aKeyState[nkey];
			
			if(m_aKeyState[nkey] && m_nKeyCounter[nkey] >= 30)
			{
				
				//リピートキー
				m_RepeatKey[nkey] = (aKeyState[nkey] & m_aKeyState[nkey]);
				
			}
			else if(m_aKeyState[nkey])
			{
				m_nKeyCounter[nkey]++;
			}
			
			//前フレームの情報を設定
			m_aKeyState[nkey] = aKeyState[nkey];
		}
	}
	else
	{
		m_pDIDevice->Acquire();
	}
}

	

//=============================================================================
// キーボードのプレス状態を取得
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
// キーボードのトリガー状態を取得
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
// キーボードのリピート状態を取得
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
// キーボードのリリ－ス状態を取得
//=============================================================================
bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	if(m_aReleaseKey[nKey] & 0x80)
	{
		return true;
	}
	return false;
}