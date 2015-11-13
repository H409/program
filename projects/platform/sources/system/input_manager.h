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
	bool GetTrigger(Command command);
	bool GetPress(Command command);
	bool GetRelease(Command command);
	bool GetRepeat(Command command);

private:
	InputKeyboard* input_keyboard_;	//�L�[�{�[�h�N���X
	InputMouse* input_mouse_;		//�}�E�X�N���X

	bool Trigger[(int)Command::MAX];	//�g���K�[���ۑ�
	bool Press[(int)Command::MAX];		//�v���X���ۑ�
	bool Release[(int)Command::MAX];	//�����[�X���ۑ�
	bool Repeat[(int)Command::MAX];		//���s�[�g���ۑ�
};
#endif
