//*****************************************************************************
//
// directx9 render texture factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_render_texture_factory.h"
#include "dx9_texture.h"

namespace graphic
{
namespace directx9
{
namespace texture
{
//=============================================================================
// constructor
//=============================================================================
DX9RenderTextureFactory::DX9RenderTextureFactory(LPDIRECT3DDEVICE9 in_direct3ddevice9)
	:direct3ddevice9_(in_direct3ddevice9)
{
}

//=============================================================================
// destructor
//=============================================================================
DX9RenderTextureFactory::~DX9RenderTextureFactory(void)
{
}

//=============================================================================
// create
//=============================================================================
DX9RenderTextureFactory::TRenderTexture DX9RenderTextureFactory::Create_(const u16 & in_width,const u16 & in_height,const TFormat& in_format)
{
	return std::make_shared<DX9Texture>(in_width,in_height,in_format,direct3ddevice9_);
}

} // namespace texture
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
