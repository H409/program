//*****************************************************************************
//
// input_manager.h
//
// Author		: Eyu Yuminaga
//
//*****************************************************************************
//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

//*****************************************************************************
// include
//*****************************************************************************

//*****************************************************************************
// forward declaration
//*****************************************************************************
class InputMouse;
class InputKeyboard;
class InputJoypad;

#define PLAYER_SUM (4)
#define PLAYER1 (0x01)
#define PLAYER2 (0x02)
#define PLAYER3 (0x04)
#define PLAYER4 (0x08)

//*****************************************************************************
// class definition
//*****************************************************************************
class InputManager
{
public:
	//入力コマンド
	enum class Command
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
		A,
		B,
		X,
		Y,
		L1,
		L2,
		R1,
		R2,
		MAX,
	};

	static const u32 keyboard_button_name_[(int)Command::MAX];
	static const u32 joypad_button_name_[(int)Command::MAX];
	
	//コンストラクタ
	InputManager();

	//デストラクタ
	virtual ~InputManager();

	//マネージャ初期化
	bool Initialize(HWND _hWnd);

	//マネージャ終了処理
	void Finalize(void);

	//更新処理
	void Update(void);

	//コマンド情報取得
	bool GetTrigger(Command command, int id)const;
	bool GetPress(Command command, int id)const;
	bool GetRelease(Command command, int id)const;
	bool GetRepeat(Command command, int id)const;

	InputKeyboard* GetKeyboard(void) { return input_keyboard_; };
	InputMouse* GetMouse(void) { return input_mouse_; };

private:
	InputKeyboard* input_keyboard_;					//キーボードクラス
	InputMouse* input_mouse_;						//マウスクラス
	InputJoypad* input_joypad_[PLAYER_SUM];			//ジョイパッドクラス

	BYTE Trigger[(int)Command::MAX][PLAYER_SUM];	//トリガー情報保存
	BYTE Press[(int)Command::MAX][PLAYER_SUM];		//プレス情報保存
	BYTE Release[(int)Command::MAX][PLAYER_SUM];	//リリース情報保存
	BYTE Repeat[(int)Command::MAX][PLAYER_SUM];		//リピート情報保存
};
#endif
