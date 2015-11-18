//=============================================================================
//
// ゲームパッド入力処理ヘッダー [input_joypad.h]
// Author : 
//
//=============================================================================
#pragma once
#ifndef _INPUTJOYPAD_H_
#define _INPUTJOYPAD_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
//*****************************************************************************
// 定数定義
//*****************************************************************************


#define JOYSTICK_NEWTRAL (32767)	//ジョイスティックのニュートラル状態の数字
#define JOYSTICK_MINUS (0)			//ジョイスティックのマイナス状態
#define JOYSTICK_MAXIMUM (65535)	//ジョイスティックのマックス状態

class InputJoypad
{

public:
	InputJoypad();
	~InputJoypad();

	//キーコード
	enum class KEY_CODE
	{
		KEY_CROSS_UP = 0,
		KEY_CROSS_RIGHT,
		KEY_CROSS_DOWN,
		KEY_CROSS_LEFT,

		KEY_UP,					// アナログスティック
		KEY_RIGHT,
		KEY_DOWN,
		KEY_LEFT,

		KEY_RIGHT_UP,
		KEY_RIGHT_RIGHT,
		KEY_RIGHT_DOWN,
		KEY_RIGHT_LEFT,

		KEY_A,		// △ボタン JOY_BUTTON1
		KEY_B,		// ○ボタン JOY_BUTTON2
		KEY_C,		// ×ボタン JOY_BUTTON3
		KEY_D,		// □ボタン JOY_BUTTON4

		KEY_L,		// Lボタン JOY_BUTTON5
		KEY_R,		// Rボタン JOY_BUTTON6

		KEY_L2,		// L2ボタン JOY_BUTTON7
		KEY_R2,		// R2ボタン JOY_BUTTON8

		KEY_SELECT,	// SELECTボタン JOY_BUTTON9
		KEY_START,	// STARTボタン JOY_BUTTON10

		KEY_L3,		// L3ボタン JOY_BUTTON11
		KEY_R3,		// R3ボタン JOY_BUTTON12

		KEY_NUM,	// キーの数
	};


	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);								// プレスキー情報取得
	bool GetTrigger(int nKey);								// トリガーキー情報取得
	bool GetRepeat(int nKey);								// リピートキー情報取得
	bool GetHold(int nKey);									// ホールドキー情報取得
	bool GetRelease(int nKey);								// リリースキー情報取得
	float GetRightAnalogStick(void);						// 右アナログスティック角度取得

private:
	JOYINFOEX				m_joyState;							// パッド情報保存用
	int						m_nJoyButtonID[(int)KEY_CODE::KEY_NUM - (int)KEY_CODE::KEY_A];	// ボタンマクロ格納
	BYTE					m_aKeyState[(int)KEY_CODE::KEY_NUM];				// キーボードの押下状態を受け取る
	BYTE					m_aTriggerKey[(int)KEY_CODE::KEY_NUM];				// キーボードを押した瞬間の判定
	BYTE					m_aReleaseKey[(int)KEY_CODE::KEY_NUM];				// キーボードを離した瞬間の判定
	BYTE					m_aHoldKey[(int)KEY_CODE::KEY_NUM];				// キーボードを押し続けてるかの判定
	BYTE					m_aRepeatKey[(int)KEY_CODE::KEY_NUM];				// リピートキー判定
	int						m_aCountKey[(int)KEY_CODE::KEY_NUM];				// リピートキー用のカウンタ
	int						m_this_id;							//このJoyPadのID
	static int				m_joyNum;							// 設定されたパッド数
};

#endif