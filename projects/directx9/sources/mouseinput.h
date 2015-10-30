//=============================================================================
//
// マウス入力処理 [input.h]
// Author :
//
//=============================================================================
#ifndef _INPUT_MOUSEINPUT_H
#define _INPUT_MOUSEINPUT_H

#include "Input.h"

typedef enum
{
	MOUSE_KEY_LEFT = 0,
	MOUSE_KEY_RIGHT,
}MOUSE_KEY;

class CInputMouse :public CInput
{
public:
	CInputMouse(void);
	~CInputMouse(void);

	void Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	D3DXVECTOR2 GetMousePosition(void);

	bool GetMousePress(MOUSE_KEY nKey);
	bool GetMouseTrigger(MOUSE_KEY nKey);
	bool GetMouseRepeat(MOUSE_KEY nKey);
	bool GetMouseRelease(MOUSE_KEY nKey);

private:
	BYTE m_aMouseKeyState[3];
	BYTE m_aMouseKeyTrigger[3];
	BYTE m_aMouseKeyRelease[3];
	BYTE m_aMouseKeyboardRepeat[3];
	DIMOUSESTATE2 m_MouseState;	//マウスのステータス
	POINT m_Mousepos;			//マウスのポジション
	HWND m_hWnd;				//ウィンドウハンドル


};

#endif