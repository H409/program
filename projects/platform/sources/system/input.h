//=============================================================================
//
// 入力処理 [input.h]
// Author :
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#define DIRECTINPUT_VERSION (0x800)
#include "dinput.h"
#include "d3dx9.h"
//*****************************************************************************
// ライブラリ参照
//*****************************************************************************
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

//=============================================================================
// プロトタイプ宣言
//=============================================================================
class Input
{
public:
	Input(void);
	virtual ~Input(void);
	virtual void Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
protected:
	static LPDIRECTINPUT8 m_pDInput;
	LPDIRECTINPUTDEVICE8 m_pDIDevice;
};

#endif