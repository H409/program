//*****************************************************************************
//
// noncopyable
//
// Author		: Kenji Kabutomori
//
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _NON_COPYABLE_H_
#define _NON_COPYABLE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/base.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace common
{
namespace base
{

class NonCopyable : public Base
{
protected:
	// constructor
	NonCopyable(void) = default;

	// destructor
	virtual ~NonCopyable(void) = default;

private:
	// copy constructer
	NonCopyable(const NonCopyable& non_copyable) = delete;
	NonCopyable(NonCopyable&& non_copyable) = delete;
	NonCopyable& operator =(NonCopyable const& non_copyable) = delete;
	NonCopyable& operator =(NonCopyable&& non_copyable) = delete;
};

}	// namespace base
}	// namespace common

#endif	// _NON_COPYABLE_H_

//---------------------------------- EOF --------------------------------------
