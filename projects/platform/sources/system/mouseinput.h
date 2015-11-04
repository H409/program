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

class InputMouse :public Input
{
public:
	InputMouse(void);
	~InputMouse(void);

	void Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	D3DXVECTOR2 GetPosition(void);
	D3DXVECTOR2 GetPrevPosition(void);

	bool GetPress(MOUSE_KEY nKey);
	bool GetTrigger(MOUSE_KEY nKey);
	bool GetRepeat(MOUSE_KEY nKey);
	bool GetRelease(MOUSE_KEY nKey);
	D3DXVECTOR2 GetDrag(MOUSE_KEY nKey);

private:
	BYTE m_aMouseKeyState[3];
	BYTE m_aPrevMouseKeyState[3];
	BYTE m_aMouseKeyTrigger[3];
	BYTE m_aMouseKeyRelease[3];
	BYTE m_aMouseKeyboardRepeat[3];
	DIMOUSESTATE2 m_MouseState;	//マウスのステータス
	POINT m_Mousepos;			//マウスのポジション
	POINT m_Prev_Mousepos;		//1フレーム前のマウスのポジション
	HWND m_hWnd;				//ウィンドウハンドル


};

#endif