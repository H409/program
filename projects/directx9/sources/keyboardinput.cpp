//=============================================================================
//
// 入力処理 [inputKeyboard.cpp]
// Author : 
//
//=============================================================================
#include "KeyBoardInput.h"
#pragma warning (disable : 4800)
//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================

//=============================================================================
// キーボードのコンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard(void)
{
}
//=============================================================================
// キーボードのコンストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard(void)
{
}
//=============================================================================
// キーボードのInit
//=============================================================================
void CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{

	// DirectInputオブジェクトの作成
	if (m_pDInput == NULL)
	{
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_pDInput, NULL);
	}
	// デバイスオブジェクトを作成
	if (m_pDInput != NULL)
	{
		m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL);
		// データフォーマットを設定
		m_pDIDevice->SetDataFormat(&c_dfDIKeyboard);
		// 協調モードを設定（フォアグラウンド＆非排他モード）
		m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		// キーボードへのアクセス権を獲得(入力制御開始)
		m_pDIDevice->Acquire(); //キーボードへのアクセス権を取得

		for (int nCntkey = 0; nCntkey < 256; nCntkey++)
		{
			m_aKeyTrigger[nCntkey] = 0;
			m_aKeyRelease[nCntkey] = 0;
			m_aKeyState[nCntkey] = 0;
		}
	}
}
//=============================================================================
// キーボードのUpdate
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
			//トリガー情報の作成
			m_aKeyTrigger[nCntkey] = (aKeyState[nCntkey] ^ m_aKeyState[nCntkey])&aKeyState[nCntkey];
			//リリース情報の作成
			m_aKeyRelease[nCntkey] = (aKeyState[nCntkey] ^ m_aKeyState[nCntkey])&m_aKeyState[nCntkey];
			//プレス情報の作成
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
// キーボードのUninit
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// DirectInputオブジェクトの開放
	if (m_pDInput != NULL)
	{
		m_pDInput->Release();
		m_pDInput = NULL;
	}

	// デバイスオブジェクトの開放
	if (m_pDIDevice != NULL)
	{
		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}
}
//=============================================================================
// キーボードのプレス状態を取得
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
// キーボードのトリガー状態を取得
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
// キーボードのリピート状態を取得
//=============================================================================
bool CInputKeyboard::GetKeyboardRepeat(int nKey)
{
	return m_aKeyboardRepeat[nKey];
}

//=============================================================================
// キーボードのリリ－ス状態を取得
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
// キーボードのアクティベート
//=============================================================================
void CInputKeyboard::ReInit(void)
{
	m_pDIDevice->Acquire(); //キーボードへのアクセス権を取得
}