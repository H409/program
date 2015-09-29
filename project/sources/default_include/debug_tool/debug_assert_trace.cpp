//*****************************************************************************
//
// assert trace
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "debug_assert_trace.h"

#ifdef _DEBUG
//=============================================================================
// trace
//=============================================================================
void AssertTrace(bool in_expression,const s8* in_filename,u32 in_line,const s8* in_message,...)
{
	s8 message[_MAX_FNAME + _MAX_EXT + 256];
	s8 work[256] = {NULL};
	va_list args;

	// 可変引数の参照開始
	va_start(args,in_message);

	// 文字列に変更
	vsprintf(work,in_message,args);

	// 可変引数の参照終了
	va_end(args);

	sprintf(message,"file : %s\nline : %d\nmessage : %s",in_filename,in_line,work);

	OutputDebugString(message);
}

#endif // _DEBUG

//-----------------------------------EOF---------------------------------------
