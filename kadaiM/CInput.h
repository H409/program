//多重定義防止
#ifndef __CINPUT_H__
#define __CINPUT_H__

//ヘッダーインクルード
#include "main.h"

//クラス定義
class CInput
{
protected:
	static LPDIRECTINPUT8	m_pDInput;
	LPDIRECTINPUTDEVICE8	m_pDIDevice;
	LPDIRECTINPUTDEVICE8	m_pDIDeviceJoyPad;
	LPDIRECTINPUTDEVICE8	m_pDIDeviceMouse;
public:
	//コンストラクタ
	CInput()
	{
		m_pDInput = NULL;
		m_pDIDevice = NULL;
	}
	//デストラクタ
	virtual ~CInput(){}
	//初期化
	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);
	//開放
	virtual void Uninit(void);
	//更新
	virtual void Update(void) = 0;

};
#endif