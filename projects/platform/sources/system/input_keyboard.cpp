//=============================================================================
//
// 入力処理 [inputKeyboard.cpp]
// Author : 
//
//=============================================================================
#include "input_keyboard.h"
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
InputKeyboard::InputKeyboard(void)
{
}
//=============================================================================
// キーボードのデストラクタ
//=============================================================================
InputKeyboard::~InputKeyboard(void)
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
// キーボードのInit
//=============================================================================
void InputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
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
// キーボードのUpdate
//=============================================================================
void InputKeyboard::Update(void)
{
	BYTE aKeyState[256];
	if (FAILED(m_pDIDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		m_pDIDevice->Acquire();
		//初期化を入れる
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
			//トリガー情報の作成
			m_aKeyTrigger[nCntkey] = (aKeyState[nCntkey] ^ m_aKeyState[nCntkey])&aKeyState[nCntkey];
			//リリース情報の作成
			m_aKeyRelease[nCntkey] = (aKeyState[nCntkey] ^ m_aKeyState[nCntkey])&m_aKeyState[nCntkey];
			//プレス情報の作成
			m_aKeyState[nCntkey] = aKeyState[nCntkey];

			//リリース情報作成
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
// キーボードのUninit
//=============================================================================
void InputKeyboard::Uninit(void)
{

}
//=============================================================================
// キーボードのプレス状態を取得
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
// キーボードのトリガー状態を取得
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
// //キーボードのリピートを取得する、nKeyにキーコード、
// //countにリピート判定するための最低フレーム数を入れる
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
// キーボードのリリ－ス状態を取得
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
// キーボードのアクティベート
//=============================================================================
void InputKeyboard::ReInit(void)
{
	m_pDIDevice->Acquire(); //キーボードへのアクセス権を取得
}