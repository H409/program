//多重定義防止
#ifndef __CINPUTKEYBOARD_H__
#define __CINPUTKEYBOARD_H__

//マクロ
#define KEY_MAX	(256)


//ヘッダーインクルード
#include "CInput.h"
//クラス定義
class CInputKeyboard:public CInput
{
private:
	BYTE m_aKeyState[KEY_MAX];
	BYTE m_aTrigKey[KEY_MAX];
	BYTE m_aReleaseKey[KEY_MAX];
	BYTE m_aRepeatKey[KEY_MAX];
	int  m_nKeyCounter[KEY_MAX];
	BOOL m_bKeyFlag[KEY_MAX];
	BYTE m_RepeatKey[KEY_MAX];
	static CInputKeyboard* m_Instance;
public:
	static CInputKeyboard* getInstance();
	static void deleteInstance();
	CInputKeyboard(){}
	virtual ~CInputKeyboard(){}

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(int nKey);
	bool GetKeyboardRepeat(int nKey);
	bool GetKeyboardRelease(int nKey);
};

#endif