//*****************************************************************************
//
// vertex buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace vertex
{
class VertexBuffer : public utility::base::Base
{
public:
	// destructor
	virtual ~VertexBuffer(void);

	// stream
	virtual void Stream(const void* in_buffer,const u32& in_offset,const u32& in_byte_count) = 0;

	// get buffer
	virtual void* GetBuffer(void)const = 0;

protected:
	// constructor
	VertexBuffer(const u32& in_size);

	u32 size_;
private:
};

} // namespace vertex
} // namespace graphic

#endif // _VERTEX_BUFFER_H_

//---------------------------------- EOF --------------------------------------

