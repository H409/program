//=============================================================================
//
// �Q�[���p�b�h���͏����w�b�_�[ [input_joypad.h]
// Author : 
//
//=============================================================================
#pragma once
#ifndef _INPUTJOYPAD_H_
#define _INPUTJOYPAD_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
//*****************************************************************************
// �萔��`
//*****************************************************************************


#define JOYSTICK_NEWTRAL (32767)	//�W���C�X�e�B�b�N�̃j���[�g������Ԃ̐���
#define JOYSTICK_MINUS (0)			//�W���C�X�e�B�b�N�̃}�C�i�X���
#define JOYSTICK_MAXIMUM (65535)	//�W���C�X�e�B�b�N�̃}�b�N�X���

class InputJoypad
{

public:
	InputJoypad();
	~InputJoypad();

	//�L�[�R�[�h
	enum class KEY_CODE
	{
		KEY_CROSS_UP = 0,
		KEY_CROSS_RIGHT,
		KEY_CROSS_DOWN,
		KEY_CROSS_LEFT,

		KEY_UP,					// �A�i���O�X�e�B�b�N
		KEY_RIGHT,
		KEY_DOWN,
		KEY_LEFT,

		KEY_RIGHT_UP,
		KEY_RIGHT_RIGHT,
		KEY_RIGHT_DOWN,
		KEY_RIGHT_LEFT,

		KEY_A,		// ���{�^�� JOY_BUTTON1
		KEY_B,		// ���{�^�� JOY_BUTTON2
		KEY_C,		// �~�{�^�� JOY_BUTTON3
		KEY_D,		// ���{�^�� JOY_BUTTON4

		KEY_L,		// L�{�^�� JOY_BUTTON5
		KEY_R,		// R�{�^�� JOY_BUTTON6

		KEY_L2,		// L2�{�^�� JOY_BUTTON7
		KEY_R2,		// R2�{�^�� JOY_BUTTON8

		KEY_SELECT,	// SELECT�{�^�� JOY_BUTTON9
		KEY_START,	// START�{�^�� JOY_BUTTON10

		KEY_L3,		// L3�{�^�� JOY_BUTTON11
		KEY_R3,		// R3�{�^�� JOY_BUTTON12

		KEY_NUM,	// �L�[�̐�
	};


	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);								// �v���X�L�[���擾
	bool GetTrigger(int nKey);								// �g���K�[�L�[���擾
	bool GetRepeat(int nKey);								// ���s�[�g�L�[���擾
	bool GetHold(int nKey);									// �z�[���h�L�[���擾
	bool GetRelease(int nKey);								// �����[�X�L�[���擾
	float GetRightAnalogStick(void);						// �E�A�i���O�X�e�B�b�N�p�x�擾

private:
	JOYINFOEX				m_joyState;							// �p�b�h���ۑ��p
	int						m_nJoyButtonID[(int)KEY_CODE::KEY_NUM - (int)KEY_CODE::KEY_A];	// �{�^���}�N���i�[
	BYTE					m_aKeyState[(int)KEY_CODE::KEY_NUM];				// �L�[�{�[�h�̉�����Ԃ��󂯎��
	BYTE					m_aTriggerKey[(int)KEY_CODE::KEY_NUM];				// �L�[�{�[�h���������u�Ԃ̔���
	BYTE					m_aReleaseKey[(int)KEY_CODE::KEY_NUM];				// �L�[�{�[�h�𗣂����u�Ԃ̔���
	BYTE					m_aHoldKey[(int)KEY_CODE::KEY_NUM];				// �L�[�{�[�h�����������Ă邩�̔���
	BYTE					m_aRepeatKey[(int)KEY_CODE::KEY_NUM];				// ���s�[�g�L�[����
	int						m_aCountKey[(int)KEY_CODE::KEY_NUM];				// ���s�[�g�L�[�p�̃J�E���^
	int						m_this_id;							//����JoyPad��ID
	static int				m_joyNum;							// �ݒ肳�ꂽ�p�b�h��
};

#endif