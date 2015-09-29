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
#ifndef _DIRECTX9_TEXTURE_LOADER_H_
#define _DIRECTX9_TEXTURE_LOADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/base/texture/base_texture_loader.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace texture
{
class DX9TextureLoader : public graphic::base::texture::BaseTextureLoader
{
public:
	// constructor
	DX9TextureLoader(LPDIRECT3DDEVICE9 direct3ddevice9);

	// destructor
	virtual ~DX9TextureLoader(void);

private:
	LPDIRECT3DDEVICE9 direct3ddevice9_;
	virtual base::texture::BaseTexture* Create(const std::string& key)override;
};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DIRECTX9_TEXTURE_LOADER_H_

//---------------------------------- EOF --------------------------------------
