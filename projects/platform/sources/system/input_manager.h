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
	bool GetTrigger(Command command);
	bool GetPress(Command command);
	bool GetRelease(Command command);
	bool GetRepeat(Command command);

private:
	InputKeyboard* input_keyboard_;	//キーボードクラス
	InputMouse* input_mouse_;		//マウスクラス

	bool Trigger[(int)Command::MAX];	//トリガー情報保存
	bool Press[(int)Command::MAX];		//プレス情報保存
	bool Release[(int)Command::MAX];	//リリース情報保存
	bool Repeat[(int)Command::MAX];		//リピート情報保存
};
#endif
