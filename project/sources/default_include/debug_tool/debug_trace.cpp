//*****************************************************************************
//
// trace
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "debug_trace.h"

#ifdef _DEBUG
//=============================================================================
// trace
//=============================================================================
void Trace(const s8* in_message,...)
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

	sprintf(message,"trace : %s",work);

	OutputDebugString(message);
}

#endif // _DEBUG

//-----------------------------------EOF---------------------------------------