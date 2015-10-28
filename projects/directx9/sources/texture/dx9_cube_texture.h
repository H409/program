//*****************************************************************************
//
// directx9 cube texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_CUBE_TEXTURE_H_
#define _DX9_CUBE_TEXTURE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/texture/texture.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace texture
{
class DX9CubeTexture : public graphic::texture::Texture
{
public:
	// constructor
	DX9CubeTexture(const std::string& path,LPDIRECT3DDEVICE9 in_direct3ddevice9);
	DX9CubeTexture(const u32& in_id,LPDIRECT3DDEVICE9 in_direct3ddevice9);

	// destructor
	virtual ~DX9CubeTexture(void);

	// get buffer
	void* GetBuffer(void)const override;

private:
	LPDIRECT3DCUBETEXTURE9 direct3dcubetexture9_;
	DX9CubeTexture(void);
};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DX9_TEXTURE_H_

//---------------------------------- EOF --------------------------------------
