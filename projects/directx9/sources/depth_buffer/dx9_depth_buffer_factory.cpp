//*****************************************************************************
//
// base depth buffer factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_depth_buffer_factory.h"
#include "dx9_depth_buffer.h"

namespace graphic
{
namespace directx9
{
namespace depth_buffer
{
//=============================================================================
// constructor
//=============================================================================
DX9DepthBufferFactory::DX9DepthBufferFactory(LPDIRECT3DDEVICE9 in_direct3ddevice9)
	:direct3ddevice9_(in_direct3ddevice9)
{
}

//=============================================================================
// destructor
//=============================================================================
DX9DepthBufferFactory::~DX9DepthBufferFactory(void)
{
}

//=============================================================================
// create
//=============================================================================
DX9DepthBufferFactory::TDepthBuffer DX9DepthBufferFactory::Create_(const u16 & in_width,const u16 & in_height,const graphic::depth_buffer::FORMAT& in_format)
{
	return std::make_shared<DX9DepthBuffer>(in_width,in_height,in_format,direct3ddevice9_);
}

} // namespace depth_buffer
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
