//=============================================================================
//
// ���͏��� [input.h]
// Author :
//
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

#include "input.h"
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
class InputKeyboard :public Input
{
public:
	InputKeyboard(void);
	~InputKeyboard(void);
	void Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	void ReInit();

	bool GetPress(int nKey)const;
	bool GetTrigger(int nKey)const;
	bool GetRepeat(int nKey, int count)const;	//�L�[�{�[�h�̃��s�[�g���擾����AnKey�ɃL�[�R�[�h�Acount�Ƀ��s�[�g���肷�邽�߂̍Œ�t���[����������
	bool GetRelease(int nKey)const;
private:
	static const u32 KEYBOARD_MAX = 256;
	static const u32 KEY_BIT = 0x80;
	BYTE m_aKeyState[KEYBOARD_MAX];
	BYTE m_aKeyTrigger[KEYBOARD_MAX];
	BYTE m_aKeyRelease[KEYBOARD_MAX];
	BYTE m_aKeyRepeat[KEYBOARD_MAX];
	int m_KeyCount[KEYBOARD_MAX];
};
#endif