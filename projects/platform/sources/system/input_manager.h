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
	//���̓R�}���h
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
	
	//�R���X�g���N�^
	InputManager();

	//�f�X�g���N�^
	virtual ~InputManager();

	//�}�l�[�W��������
	bool Initialize(HWND _hWnd);

	//�}�l�[�W���I������
	void Finalize(void);

	//�X�V����
	void Update(void);

	//�R�}���h���擾
	bool GetTrigger(Command command, int id)const;
	bool GetPress(Command command, int id)const;
	bool GetRelease(Command command, int id)const;
	bool GetRepeat(Command command, int id)const;

	InputKeyboard* GetKeyboard(void) { return input_keyboard_; };
	InputMouse* GetMouse(void) { return input_mouse_; };

private:
	InputKeyboard* input_keyboard_;					//�L�[�{�[�h�N���X
	InputMouse* input_mouse_;						//�}�E�X�N���X
	InputJoypad* input_joypad_[PLAYER_SUM];			//�W���C�p�b�h�N���X

	BYTE Trigger[(int)Command::MAX][PLAYER_SUM];	//�g���K�[���ۑ�
	BYTE Press[(int)Command::MAX][PLAYER_SUM];		//�v���X���ۑ�
	BYTE Release[(int)Command::MAX][PLAYER_SUM];	//�����[�X���ۑ�
	BYTE Repeat[(int)Command::MAX][PLAYER_SUM];		//���s�[�g���ۑ�
};
#endif
