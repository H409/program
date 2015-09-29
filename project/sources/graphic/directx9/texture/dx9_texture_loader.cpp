//*****************************************************************************
//
// directx9 texture loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_texture_loader.h"
#include "dx9_texture.h"

namespace graphic
{
namespace directx9
{
namespace texture
{
//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
DX9TextureLoader::DX9TextureLoader(LPDIRECT3DDEVICE9 direct3ddevice9)
	:direct3ddevice9_(direct3ddevice9)
{
}

//=============================================================================
// destructor
//=============================================================================
DX9TextureLoader::~DX9TextureLoader(void)
{
}

//=============================================================================
// create
//=============================================================================
base::texture::BaseTexture* DX9TextureLoader::Create(const std::string& key)
{
	auto texture = new DX9Texture(key,direct3ddevice9_);

	DEBUG_ASSERT(texture != nullptr);

	return texture;
}

} // namespace texture
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
