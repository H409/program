//=============================================================================
//
// 入力オブジェクト管理 [input_manager.cpp]
// Author : Eyu Yuminaga
//
//=============================================================================

#include "input_manager.h"
#include "input_keyboard.h"
#include "input_mouse.h"

const u32 InputManager::keyboard_button_name_[(int)Command::MAX] = {
	DIK_UP,		//UP
	DIK_DOWN,	//DOWN
	DIK_LEFT,	//LEFT
	DIK_RIGHT,	//RIGHT
	DIK_X,		//A
	DIK_Z,		//B
	DIK_C,		//X
	DIK_V,		//Y
	DIK_Q,		//L1
	DIK_E,		//L2
	DIK_U,		//R1
	DIK_O		//R2
};

InputManager::InputManager(void)
{
	
}

InputManager::~InputManager()
{
	delete input_keyboard_;
	delete input_mouse_;
}

bool InputManager::Initialize(HWND _hWnd)
{
	input_keyboard_ = new InputKeyboard();
	input_keyboard_->Init(NULL, _hWnd);
	input_mouse_ = new InputMouse();
	input_mouse_->Init(NULL, _hWnd);
	return true;
}

void InputManager::Finalize(void)
{
	input_keyboard_->Uninit();
	input_mouse_->Uninit();
}

void InputManager::Update(void)
{
	input_keyboard_->Update();
	input_mouse_->Update();

	//コマンドの状態
	for (int key = 0; key < (int)Command::MAX; key++)
	{
		Trigger[key] = input_keyboard_->GetTrigger(keyboard_button_name_[key]);
		Press[key] = input_keyboard_->GetTrigger(keyboard_button_name_[key]);
		Release[key] = input_keyboard_->GetTrigger(keyboard_button_name_[key]);
		Repeat[key] = input_keyboard_->GetTrigger(keyboard_button_name_[key]);
	}
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool InputManager::GetTrigger(Command command)
{
	return Trigger[(int)command];
}
//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool InputManager::GetPress(Command command)
{
	return Press[(int)command];
}
//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool InputManager::GetRelease(Command command)
{
	return Release[(int)command];
}
//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool InputManager::GetRepeat(Command command)
{
	return Repeat[(int)command];
}