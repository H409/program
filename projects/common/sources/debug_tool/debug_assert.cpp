//*****************************************************************************
//
// assert
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "debug_assert.h"
#include <Windows.h>

#ifdef _DEBUG
namespace debug_tool {
//=============================================================================
// assert
//=============================================================================
void Assert(bool in_expression,const s8* in_filename,u32 in_line,const s8* in_message,...)
{
	if(in_expression)
	{
		s8 message[_MAX_FNAME + _MAX_EXT + 256];
		s8 work[256] = { 0 };
		va_list args;

		// �ψ����̎Q�ƊJ�n
		va_start(args,in_message);

		// ������ɕύX
		vsprintf_s(work,in_message,args);

		// �ψ����̎Q�ƏI��
		va_end(args);

		sprintf_s(message,"file : %s\nline : %d\nmessage : %s",in_filename,in_line,work);

		//#ifdef _USING_WINDOWS_
		//MessageBox(NULL,message,"error",MB_OK | MB_ICONEXCLAMATION);
		//#endif // _USING_WINDOWS_
	}
}
} // namespace debug_tool

#endif // _DEBUG

//-----------------------------------EOF---------------------------------------
