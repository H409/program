//*****************************************************************************
//
// base window
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_WINDOW_H_
#define _BASE_WINDOW_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/non_copyable.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace window
{
class BaseWindow : public common::base::NonCopyable
{
public:
	// destructor
	virtual ~BaseWindow(void);

	// set size
	bool SetSize(const u16& in_width,const u16& in_height);

	// accessor
	const u16& __width(void)const { return width_; }
	const u16& __height(void)const { return height_; }

protected:
	// constructor
	BaseWindow(void);

	u16 width_;
	u16 height_;

private:
	virtual bool SetSize_(const u16& in_width,const u16& in_height) = 0;
};

} // namespace window
} // namespace base
} // namespace graphic

#endif // _BASE_WINDOW_H_

//---------------------------------- EOF --------------------------------------
