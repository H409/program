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

namespace graphic {
namespace directx9 {
namespace texture {
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
// load
//=============================================================================
DX9TextureLoader::TTexture DX9TextureLoader::Load(const std::string & in_path)
{
	auto it = container_.find(in_path);

	if(it != container_.end())
	{
		return it->second;
	}

	auto texture = std::make_shared<DX9Texture>(in_path,direct3ddevice9_);
	DEBUG_ASSERT(texture != nullptr);
	container_.insert(std::make_pair(in_path,texture));
	return texture;
}

} // namespace texture
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
