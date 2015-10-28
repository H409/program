//*****************************************************************************
//
// directx9 cube texture loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_cube_texture_loader.h"
#include "dx9_cube_texture.h"

namespace graphic
{
namespace directx9
{
namespace texture
{
//=============================================================================
// constructor
//=============================================================================
DX9CuebTextureLoader::DX9CuebTextureLoader(LPDIRECT3DDEVICE9 direct3ddevice9)
	:direct3ddevice9_(direct3ddevice9)
{
}

//=============================================================================
// destructor
//=============================================================================
DX9CuebTextureLoader::~DX9CuebTextureLoader(void)
{
}

//=============================================================================
// create
//=============================================================================
DX9CuebTextureLoader::TTexture* DX9CuebTextureLoader::Create(const std::string& in_key)
{
	auto texture = new DX9CubeTexture(in_key,direct3ddevice9_);

	DEBUG_ASSERT(texture != nullptr);

	return texture;
}

} // namespace texture
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
