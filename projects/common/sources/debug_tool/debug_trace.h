//*****************************************************************************
//
// trace
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TRACE_H_
#define _TRACE_H_

//*****************************************************************************
// macro definition
//*****************************************************************************
#ifdef _DEBUG
void Trace(const s8* in_message,...);

#define DEBUG_TRACE(message,...) Trace(message,__VA_ARGS__)
#else
#define DEBUG_TRACE(message,...)
#endif // _DEBUG

#endif // _ASSERT_H_

//---------------------------------- EOF --------------------------------------
