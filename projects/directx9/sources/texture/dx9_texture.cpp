//*****************************************************************************
//
// directx9 texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_texture.h"

namespace graphic {
namespace directx9 {
namespace texture {
//=============================================================================
// constructor
//=============================================================================
DX9Texture::DX9Texture(void)
	:direct3dtexture9_(nullptr)
	,direct3dsurface9_(nullptr)
{
}

//=============================================================================
// constructor
//=============================================================================
DX9Texture::DX9Texture(LPDIRECT3DSURFACE9 in_surface)
	:DX9Texture()
{
	direct3dsurface9_ = in_surface;
}

//=============================================================================
// constructor
//=============================================================================
DX9Texture::DX9Texture(const std::string& in_path,LPDIRECT3DDEVICE9 in_direct3ddevice9)
	:DX9Texture()
{
	DEBUG_ASSERT(in_direct3ddevice9 != nullptr);
	D3DXCreateTextureFromFile(in_direct3ddevice9,in_path.c_str(),&direct3dtexture9_);
	DEBUG_ASSERT(direct3dtexture9_ != nullptr);
}

//=============================================================================
// constructor
//=============================================================================
DX9Texture::DX9Texture(const u32& in_id,LPDIRECT3DDEVICE9 in_direct3ddevice9)
	:DX9Texture()
{
	DEBUG_ASSERT(in_direct3ddevice9 != nullptr);
	D3DXCreateTextureFromResource(in_direct3ddevice9,NULL,MAKEINTRESOURCE(in_id),&direct3dtexture9_);
}

//=============================================================================
// constructor
//=============================================================================
DX9Texture::DX9Texture(const u16 & in_width,const u16 & in_height,const D3DFORMAT& in_format,LPDIRECT3DDEVICE9 in_direct3ddevice9)
	:DX9Texture()
{
	in_direct3ddevice9->CreateTexture(in_width,in_height,1,D3DUSAGE_RENDERTARGET,in_format,D3DPOOL_DEFAULT,&direct3dtexture9_,NULL);

	direct3dtexture9_->GetSurfaceLevel(0,&direct3dsurface9_);
}

//=============================================================================
// constructor
//=============================================================================
//DX9Texture::DX9Texture(const u16& in_width,const u16& in_height,const TFormat& in_format,LPDIRECT3DDEVICE9 in_direct3ddevice9)
//	:DX9Texture()
//{
//	DEBUG_ASSERT(in_direct3ddevice9 != nullptr);
//
//	D3DFORMAT format = ConvertD3DFORMATFromFormat_(in_format);
//	in_direct3ddevice9->CreateTexture(in_width,in_height,1,D3DUSAGE_RENDERTARGET,format,D3DPOOL_DEFAULT,&direct3dtexture9_,NULL);
//
//	// サーフェースレベルの取得
//	direct3dtexture9_->GetSurfaceLevel(0,&frame_buffer_);
//}

//=============================================================================
// destructor
//=============================================================================
DX9Texture::~DX9Texture(void)
{
	SafeRelease(direct3dsurface9_);
	SafeRelease(direct3dtexture9_);
}

//=============================================================================
// get texture
//=============================================================================
LPDIRECT3DTEXTURE9 DX9Texture::GetTexture(void)const
{
	return direct3dtexture9_;
}

//=============================================================================
// get surface
//=============================================================================
LPDIRECT3DSURFACE9 DX9Texture::GetSurface(void) const
{
	return direct3dsurface9_;
}

//=============================================================================
// get buffer
//=============================================================================
//void* DX9Texture::GetBuffer(void)const
//{
//	return direct3dtexture9_;
//}

//=============================================================================
// get frame buffer
//=============================================================================
//void* DX9Texture::GetFrameBuffer(void)const
//{
//	return frame_buffer_;
//}

} // namespace texture
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
