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

	BYTE m_aKeyState[256];
	BYTE m_aKeyTrigger[256];
	BYTE m_aKeyRelease[256];
	BYTE m_aKeyboardRepeat[256];
	int KeyCount[256];
};
#endif