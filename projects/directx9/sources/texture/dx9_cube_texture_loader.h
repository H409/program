//*****************************************************************************
//
// directx9 cube texture loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_CUBE_TEXTURE_LOADER_H_
#define _DX9_CUBE_TEXTURE_LOADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/texture/cube_texture_loader.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace texture
{
class DX9CuebTextureLoader : public graphic::texture::CubeTextureLoader
{
public:
	// constructor
	DX9CuebTextureLoader(LPDIRECT3DDEVICE9 direct3ddevice9);

	// destructor
	virtual ~DX9CuebTextureLoader(void);

private:
	LPDIRECT3DDEVICE9 direct3ddevice9_;
	virtual TTexture* Create(const std::string& key)override;
};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DX9_TEXTURE_LOADER_H_

//---------------------------------- EOF --------------------------------------
