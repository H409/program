//=============================================================================
//
// ���͏��� [input.h]
// Author :
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#define DIRECTINPUT_VERSION (0x800)
#include "dinput.h"
#include "d3dx9.h"
//*****************************************************************************
// ���C�u�����Q��
//*****************************************************************************
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

//=============================================================================
// �v���g�^�C�v�錾
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