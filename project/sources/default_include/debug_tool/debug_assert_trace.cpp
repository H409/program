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

	// �ψ����̎Q�ƊJ�n
	va_start(args,in_message);

	// ������ɕύX
	vsprintf(work,in_message,args);

	// �ψ����̎Q�ƏI��
	va_end(args);

	sprintf(message,"file : %s\nline : %d\nmessage : %s",in_filename,in_line,work);

	OutputDebugString(message);
}

#endif // _DEBUG

//-----------------------------------EOF---------------------------------------
