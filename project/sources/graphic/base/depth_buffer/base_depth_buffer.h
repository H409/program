//*****************************************************************************
//
// base depth buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_DEPTH_BUFFER_H_
#define _BASE_DEPTH_BUFFER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/non_copyable.h"
#include "depth_buffer_format.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace depth_buffer
{
class BaseDepthBuffer : public common::base::NonCopyable
{
public:
	// get buffer
	virtual void* GetBuffer(void)const = 0;

	// destructor
	virtual ~BaseDepthBuffer(void);

protected:
	// constructor
	BaseDepthBuffer(void);

private:

};

} // namespace depth_buffer
} // namespace base
} // namespace graphic

#endif // _BASE_DEPTH_BUFFER_H_

//---------------------------------- EOF --------------------------------------
