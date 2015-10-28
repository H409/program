//*****************************************************************************
//
// directx9 vertex buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_VERTEX_BUFFER_H_
#define _DX9_VERTEX_BUFFER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/vertex/vertex_buffer.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace vertex
{
class DX9VertexBuffer : public graphic::vertex::VertexBuffer
{
public:
	// constructor
	DX9VertexBuffer(LPDIRECT3DDEVICE9 in_direct3ddevice9,const u32& in_size);

	// destructor
	virtual ~DX9VertexBuffer(void);

	// get buffer
	void* GetBuffer(void)const override;

	// stream
	void Stream(const void* in_buffer,const u32& in_offset,const u32& in_byte_count)override;

protected:

private:
	LPDIRECT3DVERTEXBUFFER9 direct3dvertexbuffer9_;

};

} // namespace vertex
} // namespace directx9
} // namespace graphic

#endif // _DX9_VERTEX_BUFFER_H_

//---------------------------------- EOF --------------------------------------

