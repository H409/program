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
	InputMouse(void);
	~InputMouse(void);

	enum class MOUSE_KEY
	{
		LEFT = 0,
		RIGHT,
		MAX,
	};

	void Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	const float2& GetPosition(void)const;
	const float2& GetPrevPosition(void)const;

	bool GetPress(MOUSE_KEY nKey)const;
	bool GetTrigger(MOUSE_KEY nKey)const;
	bool GetRepeat(MOUSE_KEY nKey)const;
	bool GetRelease(MOUSE_KEY nKey)const;
	const float2& GetDrag(MOUSE_KEY nKey)const;

private:
	BYTE m_aMouseKeyState[3];
	BYTE m_aPrevMouseKeyState[3];
	BYTE m_aMouseKeyTrigger[3];
	BYTE m_aMouseKeyRelease[3];
	BYTE m_aMouseKeyRepeat[3];
	int m_KeyCount[3];
	DIMOUSESTATE2 m_MouseState;	//マウスのステータス
	POINT m_Mousepos;			//マウスのポジション
	POINT m_Prev_Mousepos;		//1フレーム前のマウスのポジション
	HWND m_hWnd;				//ウィンドウハンドル


};

#endif