//*****************************************************************************
//
// デバッグログクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "debug_log.h"
#include <stdio.h>
#include <time.h>
#include <windows.h>

//*****************************************************************************
// macro definition
//*****************************************************************************

//*****************************************************************************
// constant definition
//*****************************************************************************
const s8* DebugLog::LOG_FILE_PATH = "log/";

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
DebugLog::DebugLog(void)
{
#ifndef _RELEASE
	// ログのinitializer
	log_ = "";
#endif
}

//=============================================================================
// destructor
//=============================================================================
DebugLog::~DebugLog(void)
{
#ifndef _RELEASE
#endif
}

//=============================================================================
// initializer
//=============================================================================
bool DebugLog::Initialize(void)
{
#ifndef _RELEASE
#endif
	return true;
}

//=============================================================================
// 更新
//=============================================================================
void DebugLog::Update(void)
{
#ifndef _RELEASE
#endif
}

//=============================================================================
// 描画
//=============================================================================
void DebugLog::Draw(void)
{
#ifndef _RELEASE
#endif
}

//=============================================================================
// 終了
//=============================================================================
void DebugLog::Uninitialize(void)
{
	std::string path = LOG_FILE_PATH;
	char work[STRING_MAX];

	time_t timer;
	struct tm *t_st;

	// 現在時刻の取得
	time(&timer);

	// 現在時刻を構造体に変換
	t_st = localtime(&timer);
	sprintf(work,"%d%02d%02d_%02d%02d%02d",t_st->tm_year + 1900,t_st->tm_mon+1,t_st->tm_mday,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
	path += work;
	path += ".txt";

	FILE* file = fopen(path.c_str(),"wt");

	if(file != nullptr)
	{
		fprintf(file,log_.c_str());
		fclose(file);
	}
}

//=============================================================================
// 出力
//=============================================================================
void DebugLog::Print(const s8* format,...)
{
#ifndef _RELEASE
	char work[STRING_MAX] = {NULL};
	va_list args;

	// 可変引数の参照開始
	va_start(args,format);

	// 文字列に変更
	vsprintf(work,format,args);

	// 可変引数の参照終了
	va_end(args);

	// ログに書込
	log_ += work;

#endif
}

//-----------------------------------EOF---------------------------------------
