//*****************************************************************************
//
// depth buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DEPTH_BUFFER_H_
#define _DEPTH_BUFFER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/non_copyable.h"
#include "depth_buffer_format.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace depth_buffer
{
class DepthBuffer : public utility::base::NonCopyable
{
public:
	// get buffer
	virtual void* GetBuffer(void)const = 0;

	// destructor
	virtual ~DepthBuffer(void);

protected:
	// constructor
	DepthBuffer(void);

private:

};

} // namespace depth_buffer
} // namespace graphic

#endif // _DEPTH_BUFFER_H_

//---------------------------------- EOF --------------------------------------
