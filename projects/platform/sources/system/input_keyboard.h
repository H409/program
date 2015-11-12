//=============================================================================
//
// 入力処理 [input.h]
// Author :
//
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

#include "input.h"
//=============================================================================
// プロトタイプ宣言
//=============================================================================
class InputKeyboard :public Input
{
public:
	InputKeyboard(void);
	~InputKeyboard(void);
	void Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	void ReInit();

	bool GetPress(int nKey)const;
	bool GetTrigger(int nKey)const;
	bool GetRepeat(int nKey)const;
	bool GetRelease(int nKey)const;
private:
	static const u32 KEYBOARD_MAX = 256;
	static const u32 KEY_BIT = 0x80;

	BYTE m_aKeyState[KEYBOARD_MAX];
	BYTE m_aKeyTrigger[KEYBOARD_MAX];
	BYTE m_aKeyRelease[KEYBOARD_MAX];
	BYTE m_aKeyboardRepeat[KEYBOARD_MAX];
	int KeyCount[KEYBOARD_MAX];
};
#endif