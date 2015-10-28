//*****************************************************************************
//
// directx9 vertex buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_vertex_buffer.h"

namespace graphic
{
namespace directx9
{
namespace vertex
{
//=============================================================================
// constructor
//=============================================================================
DX9VertexBuffer::DX9VertexBuffer(LPDIRECT3DDEVICE9 in_direct3ddevice9,const u32& in_size)
	:VertexBuffer(in_size)
	,direct3dvertexbuffer9_(nullptr)
{
	in_direct3ddevice9->CreateVertexBuffer(in_size,D3DUSAGE_WRITEONLY,0,D3DPOOL_MANAGED,&direct3dvertexbuffer9_,nullptr);
}

//=============================================================================
// destructor
//=============================================================================
DX9VertexBuffer::~DX9VertexBuffer(void)
{
	SafeRelease(direct3dvertexbuffer9_);
}

//=============================================================================
// get buffer
//=============================================================================
void* DX9VertexBuffer::GetBuffer(void) const
{
	return direct3dvertexbuffer9_;
}

//=============================================================================
// stream
//=============================================================================
void DX9VertexBuffer::Stream(const void* in_buffer,const u32& in_offset,const u32& in_byte_count)
{
	u8* buffer = nullptr;

	DEBUG_ASSERT(in_buffer != nullptr);

	direct3dvertexbuffer9_->Lock(0,0,(void**)&buffer,0);

	for(u32 i = in_offset;i < in_offset + in_byte_count;++i)
	{
		buffer[i] = ((u8*)(in_buffer))[i - in_offset];
	}

	direct3dvertexbuffer9_->Unlock();
}

} // namespace vertex
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
