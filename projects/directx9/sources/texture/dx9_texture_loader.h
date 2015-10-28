//*****************************************************************************
//
// directx9 texture loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_TEXTURE_LOADER_H_
#define _DX9_TEXTURE_LOADER_H_

//*****************************************************************************
// include
//*****************************************************************************
//#include "graphic/texture/texture_loader.h"

namespace graphic {
namespace directx9 {
namespace texture {
class DX9Texture;
} // namespace texture
} // namespace directx9
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic {
namespace directx9 {
namespace texture {
class DX9TextureLoader// : public graphic::texture::TextureLoader
{
public:
	using TTexture = std::shared_ptr<DX9Texture>;

	// constructor
	DX9TextureLoader(LPDIRECT3DDEVICE9 direct3ddevice9);

	// destructor
	virtual ~DX9TextureLoader(void);

	// load
	TTexture Load(const std::string& in_path);

private:
	LPDIRECT3DDEVICE9 direct3ddevice9_;
	std::unordered_map<std::string,TTexture> container_;
};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DX9_TEXTURE_LOADER_H_

//---------------------------------- EOF --------------------------------------
