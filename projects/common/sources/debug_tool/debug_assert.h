//*****************************************************************************
//
// assert
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DEBUG_ASSERT_H_
#define _DEBUG_ASSERT_H_

//*****************************************************************************
// macro definition
//*****************************************************************************
#ifdef _DEBUG
namespace debug_tool {
void Assert(bool in_expression,const s8* in_filename,u32 in_line,const s8* in_message,...);
} // debug_tool
#define BREAK(expression) do\
{\
	if((expression))\
	{\
		_asm int 3\
	}\
}while(0)

#define DEBUG_ASSERT_MESSAGE(expression,format,...) do\
{\
	debug_tool::Assert(!(expression),__FILE__,__LINE__,format,__VA_ARGS__);\
	BREAK(!(expression));\
}while(0)

#define DEBUG_ASSERT(expression) DEBUG_ASSERT_MESSAGE (expression,#expression)

#else
#define BREAK(expression) (expression)
#define DEBUG_ASSERT(expression) (expression)
#define DEBUG_ASSERT_MESSAGE(expression,format,...) (expression)
#endif // _DEBUG

#endif // _DEBUG_ASSERT_H_

//---------------------------------- EOF --------------------------------------
