//=============================================================================
//
// 入力処理 [input.h]
// Author :
//
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

#include "Input.h"
//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard(void);
	~CInputKeyboard(void);
	void Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	void ReInit();

	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(int nKey);
	bool GetKeyboardRepeat(int nKey);
	bool GetKeyboardRelease(int nKey);
private:

	BYTE m_aKeyState[256];
	BYTE m_aKeyTrigger[256];
	BYTE m_aKeyRelease[256];
	BYTE m_aKeyboardRepeat[256];
	int KeyCount[256];
};
#endif