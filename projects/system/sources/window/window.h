//*****************************************************************************
//
// window
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/non_copyable.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace window
{
class Window : public utility::base::NonCopyable
{
public:
	// destructor
	virtual ~Window(void);

	// set size
	bool SetSize(const u16& in_width,const u16& in_height);

	// accessor
	const u16& __width(void)const { return width_; }
	const u16& __height(void)const { return height_; }

protected:
	// constructor
	Window(void);

	u16 width_;
	u16 height_;

private:
	virtual bool SetSize_(const u16& in_width,const u16& in_height) = 0;
};

} // namespace window

#endif // _WINDOW_H_

//---------------------------------- EOF --------------------------------------
