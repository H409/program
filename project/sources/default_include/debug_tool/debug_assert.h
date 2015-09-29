//*****************************************************************************
//
// assert
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _DEBUG_ASSERT_H_
#define _DEBUG_ASSERT_H_

//*****************************************************************************
// macro definition
//*****************************************************************************
#ifdef _DEBUG
void Assert(bool in_expression,const s8* in_filename,u32 in_line,const s8* in_message,...);

#define DEBUG_ASSERT_MESSAGE(expression,format,...) do\
{\
	Assert(!(expression),__FILE__,__LINE__,format,__VA_ARGS__);\
}while(0)

#define DEBUG_ASSERT(expression) DEBUG_ASSERT_MESSAGE (expression,#expression)

#else
#define DEBUG_ASSERT(expression)
#define DEBUG_ASSERT_MESSAGE(expression,format,...)
#endif // _DEBUG

#endif // _DEBUG_ASSERT_H_

//---------------------------------- EOF --------------------------------------
