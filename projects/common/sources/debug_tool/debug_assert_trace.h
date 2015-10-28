//*****************************************************************************
//
// assert trace
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DEBUG_ASSERT_TRACE_H_
#define _DEBUG_ASSERT_TRACE_H_

//*****************************************************************************
// macro definition
//*****************************************************************************
#ifdef _DEBUG
void AssertTrace(bool in_expression,const s8* in_filename,u32 in_line,const s8* in_message,...);

#define DEBUG_ASSERT_TRACE_EXP(expression,message,...) AssertTrace(expression,__FILE__,__LINE__,message,__VA_ARGS__)
#define DEBUG_ASSERT_TRACE(message,...) DEBUG_ASSERT_EXP(true,message,__VA_ARGS__)
#else
#define DEBUG_ASSERT_TRACE_EXP(expression,message,...)
#define DEBUG_ASSERT_TRACE(message,...)
#endif // _DEBUG

#endif // _DEBUG_ASSERT_TRACE_H_

//---------------------------------- EOF --------------------------------------
