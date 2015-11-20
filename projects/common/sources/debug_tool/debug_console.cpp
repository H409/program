//*****************************************************************************
//
// デバッグコンソールクラス
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
const char* DebugConsole::TITLE = "デバッグウィンドウ";

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
DebugConsole::DebugConsole(void)
{
#ifndef _RELEASE
	// ログのinitializer
	memset(log_,0,STRING_MAX);

	// 変更フラグをinitializer
	change_flag_ = false;

	// 表示フラグ
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

	// コンソールの作成
	AllocConsole();

	// コンソールウィンドウのタイトル
	SetConsoleTitle(TITLE);

	// コンソールウィンドウハンドルの取得
	hwnd_ = GetConsoleWindow();

	// バッファサイズの設定
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coord);

	// ウィンドウサイズの設定
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),TRUE,&small_rect);

	// 変更フラグ
	change_flag_ = false;

	// 書き込み用ファイルパス
	//sprintf(log_file_path_,"log/%d.txt",time(NULL));
#endif
	return true;
}

//=============================================================================
// 更新
//=============================================================================
void DebugConsole::Update(void)
{
#ifndef _RELEASE
#endif
}

//=============================================================================
// 描画
//=============================================================================
void DebugConsole::Draw(void)
{
#ifndef _RELEASE
	if(change_flag_)
	{
		DWORD op;

		// 表示
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),log_,strlen(log_),&op,NULL);

		// ログファイルに書込

		// ログを破棄
		memset(log_,0,sizeof(log_));

		change_flag_ = false;
	}
#endif
}

//=============================================================================
// 終了
//=============================================================================
void DebugConsole::Uninitialize(void)
{
#ifndef _RELEASE
	FreeConsole();
#endif
}

//=============================================================================
// 表示
//=============================================================================
void DebugConsole::Show(void)
{
#ifndef _RELEASE
	ShowWindow(hwnd_,SW_SHOW);
	show_flag_ = true;
#endif
}

//=============================================================================
// 非表示
//=============================================================================
void DebugConsole::Hide(void)
{
#ifndef _RELEASE
	ShowWindow(hwnd_,SW_HIDE);
	show_flag_ = false;
#endif
}

//=============================================================================
// 表示切り換え
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
// 出力
//=============================================================================
void DebugConsole::Print(const char* pFormat,...)
{
#ifndef _RELEASE
	char work[STRING_MAX] = {NULL};
	va_list args;
	int nLogLen = 0;
	int nFormatLen = 0;

	// 可変引数の参照開始
	va_start(args,pFormat);

	// 文字列に変更
	vsprintf(work,pFormat,args);

	// 可変引数の参照終了
	va_end(args);

	nLogLen = strlen(log_);

	nFormatLen = strlen(work);

	if(nLogLen + nFormatLen > STRING_MAX)
	{
		// 過去ログの一部を削除
	}

	// ログに書込
	strcat(log_,work);

	// 変更フラグを立てる
	change_flag_ = true;

#endif
}

//-----------------------------------EOF---------------------------------------
