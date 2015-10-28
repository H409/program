//*****************************************************************************
//
// directx9 depth buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_depth_buffer.h"

namespace graphic
{
namespace directx9
{
namespace depth_buffer
{
//*****************************************************************************
// constant definition
//*****************************************************************************
const graphic::depth_buffer::FORMAT DX9DepthBuffer::DEFAULT_FORMAT = graphic::depth_buffer::FORMAT::NONE;

//=============================================================================
// constructor
//=============================================================================
DX9DepthBuffer::DX9DepthBuffer(void)
{
}

//=============================================================================
// constructor
//=============================================================================
DX9DepthBuffer::DX9DepthBuffer(const u16 & in_width,const u16 & in_height,LPDIRECT3DDEVICE9 in_direct3ddevice9)
	:DX9DepthBuffer(in_width,in_height,DEFAULT_FORMAT,in_direct3ddevice9)
{
}

//=============================================================================
// constructor
//=============================================================================
DX9DepthBuffer::DX9DepthBuffer(const u16& in_width,const u16& in_height,const graphic::depth_buffer::FORMAT& in_format,LPDIRECT3DDEVICE9 in_direct3ddevice9)
{
	auto format = ConvertD3DFORMATFromFormat_(in_format);

	// HACK
	format = D3DFMT_D24S8;

	// zバッファとステンシルバッファの生成
	in_direct3ddevice9->CreateDepthStencilSurface(in_width,in_height,format,D3DMULTISAMPLE_NONE,0,true,&depth_buffer_,NULL);
}

//=============================================================================
// destructor
//=============================================================================
DX9DepthBuffer::~DX9DepthBuffer(void)
{
	SafeRelease(depth_buffer_);
}

//=============================================================================
// get buffer
//=============================================================================
void* DX9DepthBuffer::GetBuffer(void)const
{
	return depth_buffer_;
}

//=============================================================================
// convert D3DFORMAT from format
//=============================================================================
D3DFORMAT DX9DepthBuffer::ConvertD3DFORMATFromFormat_(const graphic::depth_buffer::FORMAT& in_format)
{
	D3DFORMAT d3dformat = D3DFMT_UNKNOWN;

	switch(in_format)
	{
		default:
		{
			break;
		}
	}
	return d3dformat;
}

} // namespace depth_buffer
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
