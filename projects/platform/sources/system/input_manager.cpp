//=============================================================================
//
// ���̓I�u�W�F�N�g�Ǘ� [input_manager.cpp]
// Author : Eyu Yuminaga
//
//=============================================================================

#include "input_manager.h"
#include "input_keyboard.h"
#include "input_mouse.h"
#include "input_joypad.h"
#include "xi_pad.h"

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

const u32 InputManager::joypad_button_name_[(int)Command::MAX] = {
	(int)InputJoypad::KEY_CODE::KEY_CROSS_UP,		//UP
	(int)InputJoypad::KEY_CODE::KEY_CROSS_DOWN,		//DOWN
	(int)InputJoypad::KEY_CODE::KEY_CROSS_LEFT,		//LEFT
	(int)InputJoypad::KEY_CODE::KEY_CROSS_RIGHT,	//RIGHT
	(int)InputJoypad::KEY_CODE::KEY_B,				//A
	(int)InputJoypad::KEY_CODE::KEY_C,				//B
	(int)InputJoypad::KEY_CODE::KEY_A,				//X
	(int)InputJoypad::KEY_CODE::KEY_D,				//Y
	(int)InputJoypad::KEY_CODE::KEY_L,				//L1
	(int)InputJoypad::KEY_CODE::KEY_L2,				//L2
	(int)InputJoypad::KEY_CODE::KEY_R,				//R1
	(int)InputJoypad::KEY_CODE::KEY_R2,				//R2
};

const u32 InputManager::xipad_button_name_[(int)Command::MAX] = {
	(int)XIPad::KEY::UP,	//UP
	(int)XIPad::KEY::DOWN,	//DOWN
	(int)XIPad::KEY::LEFT,	//LEFT
	(int)XIPad::KEY::RIGHT,	//RIGHT
	(int)XIPad::KEY::A,		//A
	(int)XIPad::KEY::B,		//B
	(int)XIPad::KEY::X,		//X
	(int)XIPad::KEY::Y,		//Y
	(int)XIPad::KEY::L1,	//L1
	(int)XIPad::KEY::L2,	//L2
	(int)XIPad::KEY::R1,	//R1
	(int)XIPad::KEY::R2,	//R2
};

InputManager::InputManager(void)
{
	
}

InputManager::~InputManager()
{
	input_keyboard_->Uninit();
	input_mouse_->Uninit();

	delete input_mouse_;
	delete input_keyboard_;

	for (int i = 0; i < PLAYER_SUM; i++)
	{
		input_joypad_[i]->Uninit();
		delete input_joypad_[i];
		input_x_ipad_[i]->Clear();
		delete input_x_ipad_[i];
	}
}

bool InputManager::Initialize(HWND _hWnd)
{
	//�L�[�{�[�h�I�u�W�F�쐬
	input_keyboard_ = new InputKeyboard();
	input_keyboard_->Init(NULL, _hWnd);
	//�}�E�X�I�u�W�F�쐬
	input_mouse_ = new InputMouse();
	input_mouse_->Init(NULL, _hWnd);
	//�W���C�p�b�h�I�u�W�F���W���C�p�b�h�̌����쐬
	for (int i = 0; i < PLAYER_SUM; i++)
	{
		input_joypad_[i] = new InputJoypad();
		input_joypad_[i]->Init();
	}
	//X�p�b�h�I�u�W�F��X�p�b�h�̌����쐬
	for (int i = 0; i < PLAYER_SUM; i++)
	{
		input_x_ipad_[i] = new XIPad(i);
	}
	return true;
}

void InputManager::Finalize(void)
{
	
}

void InputManager::Update(void)
{
	//�}�E�X�L�[�{�[�h�X�V
	input_keyboard_->Update();
	input_mouse_->Update();

	//�W���C�p�b�h�������X�V
	for (int i = 0; i < PLAYER_SUM; i++)
	{
		input_joypad_[i]->Update();
		input_x_ipad_[i]->Update();
	}

	//�R�}���h�̏�ԍX�V
	for (int key = 0; key < (int)Command::MAX; key++)
	{
		//�v���C���[�����̌J��Ԃ�
		for (int i = 0; i < PLAYER_SUM; i++)
		{
			//�X�V
			Trigger[key][i] = input_keyboard_->GetTrigger(keyboard_button_name_[key]) | input_joypad_[i]->GetTrigger(joypad_button_name_[key])|input_x_ipad_[i]->IsTrigger((XIPad::KEY)xipad_button_name_[key]);
			Press[key][i] = input_keyboard_->GetPress(keyboard_button_name_[key]) | input_joypad_[i]->GetPress(joypad_button_name_[key]) | input_x_ipad_[i]->IsPress((XIPad::KEY)xipad_button_name_[key]);
			Release[key][i] = input_keyboard_->GetRelease(keyboard_button_name_[key]) | input_joypad_[i]->GetRelease(joypad_button_name_[key]) | input_x_ipad_[i]->IsRelease((XIPad::KEY)xipad_button_name_[key]);
			Repeat[key][i] = input_keyboard_->GetRepeat(keyboard_button_name_[key],60) | input_joypad_[i]->GetRepeat(joypad_button_name_[key]) | input_x_ipad_[i]->IsPress((XIPad::KEY)xipad_button_name_[key]);
		}
	}
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾 �����ɂė~�����v���C���[��ID���w��
//=============================================================================
bool InputManager::GetTrigger(Command command, int id)const
{
	return Trigger[(int)command][id];
}
//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾 
//=============================================================================
bool InputManager::GetPress(Command command, int id)const
{
	return Press[(int)command][id];
}
//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾 
//=============================================================================
bool InputManager::GetRelease(Command command, int id)const
{
	return Release[(int)command][id];
}
//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾 
//=============================================================================
bool InputManager::GetRepeat(Command command, int id)const
{
	return Repeat[(int)command][id];
}