//=============================================================================
//
// マウス入力処理 [input.h]
// Author :
//
//=============================================================================
#ifndef _INPUT_MOUSEINPUT_H
#define _INPUT_MOUSEINPUT_H

#include "Input.h"

class InputMouse :public Input
{
public:
	enum class MOUSE_KEY
	{
		LEFT = 0,
		RIGHT,
		MAX,
	};

	InputMouse(void);
	~InputMouse(void);

	void Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	D3DXVECTOR2 GetPosition(void);
	D3DXVECTOR2 GetPrevPosition(void);

	bool GetPress(MOUSE_KEY nKey)const;
	bool GetTrigger(MOUSE_KEY nKey)const;
	bool GetRepeat(MOUSE_KEY nKey)const;
	bool GetRelease(MOUSE_KEY nKey)const;
	D3DXVECTOR2 GetDrag(MOUSE_KEY nKey);

private:
	static const u32 KEY_BIT = 0x80;

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