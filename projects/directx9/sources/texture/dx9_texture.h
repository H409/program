//*****************************************************************************
//
// directx9 texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_TEXTURE_H_
#define _DX9_TEXTURE_H_

//*****************************************************************************
// include
//*****************************************************************************
//#include "graphic/texture/render_texture.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic {
namespace directx9 {
namespace texture {
class DX9Texture// : public graphic::texture::RenderTexture
{
public:
	//using TFormat = graphic::texture::FORMAT;

	// constructor
	explicit DX9Texture(LPDIRECT3DSURFACE9 in_surface);
	DX9Texture(const std::string& in_path,LPDIRECT3DDEVICE9 in_direct3ddevice9);
	DX9Texture(const u32& in_id,LPDIRECT3DDEVICE9 in_direct3ddevice9);
	DX9Texture(const u16& in_width,const u16& in_height,const D3DFORMAT& in_format,LPDIRECT3DDEVICE9 in_direct3ddevice9);

	// destructor
	virtual ~DX9Texture(void);

	// get texture
	LPDIRECT3DTEXTURE9 GetTexture(void)const;

	// get surface
	LPDIRECT3DSURFACE9 GetSurface(void)const;

	// get buffer
	//void* GetBuffer(void)const override;

	// get frame buffer
	//void* GetFrameBuffer(void)const override;

private:
	LPDIRECT3DTEXTURE9 direct3dtexture9_;
	LPDIRECT3DSURFACE9 direct3dsurface9_;
	DX9Texture(void);
	//D3DFORMAT ConvertD3DFORMATFromFormat_(const TFormat& in_format);

};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DX9_TEXTURE_H_

//---------------------------------- EOF --------------------------------------
