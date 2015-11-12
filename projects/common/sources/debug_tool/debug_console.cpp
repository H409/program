//*****************************************************************************
//
// �f�o�b�O�R���\�[���N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "debug_console.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

//*****************************************************************************
// macro definition
//*****************************************************************************

//*****************************************************************************
// constant definition
//*****************************************************************************
const char* DebugConsole::TITLE = "�f�o�b�O�E�B���h�E";

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
DebugConsole::DebugConsole(void)
{
#ifndef _RELEASE
	// ���O��initializer
	memset(log_,0,STRING_MAX);

	// �ύX�t���O��initializer
	change_flag_ = false;

	// �\���t���O
	show_flag_ = true;

#endif
}

//=============================================================================
// destructor
//=============================================================================
DebugConsole::~DebugConsole(void)
{
#ifndef _RELEASE
#endif
}

//=============================================================================
// initializer
//=============================================================================
bool DebugConsole::Initialize(void)
{
#ifndef _RELEASE
	SMALL_RECT small_rect = {0,0,80,25};
	COORD coord={80,25};

	// �R���\�[���̍쐬
	AllocConsole();

	// �R���\�[���E�B���h�E�̃^�C�g��
	SetConsoleTitle(TITLE);

	// �R���\�[���E�B���h�E�n���h���̎擾
	hwnd_ = GetConsoleWindow();

	// �o�b�t�@�T�C�Y�̐ݒ�
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coord);

	// �E�B���h�E�T�C�Y�̐ݒ�
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),TRUE,&small_rect);

	// �ύX�t���O
	change_flag_ = false;

	// �������ݗp�t�@�C���p�X
	//sprintf(log_file_path_,"log/%d.txt",time(NULL));
#endif
	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void DebugConsole::Update(void)
{
#ifndef _RELEASE
#endif
}

//=============================================================================
// �`��
//=============================================================================
void DebugConsole::Draw(void)
{
#ifndef _RELEASE
	if(change_flag_)
	{
		DWORD op;

		// �\��
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),log_,strlen(log_),&op,NULL);

		// ���O�t�@�C���ɏ���

		// ���O��j��
		memset(log_,0,sizeof(log_));

		change_flag_ = false;
	}
#endif
}

//=============================================================================
// �I��
//=============================================================================
void DebugConsole::Uninitialize(void)
{
#ifndef _RELEASE
	FreeConsole();
#endif
}

//=============================================================================
// �\��
//=============================================================================
void DebugConsole::Show(void)
{
#ifndef _RELEASE
	ShowWindow(hwnd_,SW_SHOW);
	show_flag_ = true;
#endif
}

//=============================================================================
// ��\��
//=============================================================================
void DebugConsole::Hide(void)
{
#ifndef _RELEASE
	ShowWindow(hwnd_,SW_HIDE);
	show_flag_ = false;
#endif
}

//=============================================================================
// �\���؂芷��
//=============================================================================
void DebugConsole::SwitchWindow(void)
{
#ifndef _RELEASE
	if(show_flag_)
	{
		Hide();
	}
	else
	{
		Show();
	}
#endif
}

//=============================================================================
// �o��
//=============================================================================
void DebugConsole::Print(const char* pFormat,...)
{
#ifndef _RELEASE
	char work[STRING_MAX] = {NULL};
	va_list args;
	int nLogLen = 0;
	int nFormatLen = 0;

	// �ψ����̎Q�ƊJ�n
	va_start(args,pFormat);

	// ������ɕύX
	vsprintf(work,pFormat,args);

	// �ψ����̎Q�ƏI��
	va_end(args);

	nLogLen = strlen(log_);

	nFormatLen = strlen(work);

	if(nLogLen + nFormatLen > STRING_MAX)
	{
		// �ߋ����O�̈ꕔ���폜
	}

	// ���O�ɏ���
	strcat(log_,work);

	// �ύX�t���O�𗧂Ă�
	change_flag_ = true;

#endif
}

//-----------------------------------EOF---------------------------------------
