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

#ifdef _DEBUG
//=============================================================================
// assert
//=============================================================================
void Assert(bool in_expression,const s8* in_filename,u32 in_line,const s8* in_message,...)
{
	if(in_expression)
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

#ifdef _USING_WINDOWS_
		MessageBox(NULL,message,"error",MB_OK | MB_ICONEXCLAMATION);
		exit(0);
#endif // _USING_WINDOWS_
	}
}

#endif // _DEBUG

//-----------------------------------EOF---------------------------------------
