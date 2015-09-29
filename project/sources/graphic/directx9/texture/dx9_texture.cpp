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
DX9Texture::DX9Texture(void)
	:direct3dtexture9_(nullptr)
	,frame_buffer_(nullptr)
{

}

//=============================================================================
// constructor
//=============================================================================
DX9Texture::DX9Texture(const std::string& in_path,LPDIRECT3DDEVICE9 in_direct3ddevice9)
	:DX9Texture()
{
	DEBUG_ASSERT(in_direct3ddevice9 != nullptr);
	D3DXCreateTextureFromFile(in_direct3ddevice9,in_path.c_str(),&direct3dtexture9_);
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
DX9Texture::DX9Texture(const u16& in_width,const u16& in_height,const base::texture::FORMAT& in_format,LPDIRECT3DDEVICE9 in_direct3ddevice9)
	:DX9Texture()
{
	DEBUG_ASSERT(in_direct3ddevice9 != nullptr);

	D3DFORMAT format = ConvertD3DFORMATFromFormat_(in_format);
	in_direct3ddevice9->CreateTexture(in_width,in_height,1,D3DUSAGE_RENDERTARGET,format,D3DPOOL_DEFAULT,&direct3dtexture9_,NULL);

	// �T�[�t�F�[�X���x���̎擾
	direct3dtexture9_->GetSurfaceLevel(0,&frame_buffer_);
}

//=============================================================================
// destructor
//=============================================================================
DX9Texture::~DX9Texture(void)
{
	SafeRelease(frame_buffer_);
	SafeRelease(direct3dtexture9_);
}

//=============================================================================
// get buffer
//=============================================================================
void* DX9Texture::GetBuffer(void)const
{
	return direct3dtexture9_;
}

//=============================================================================
// get frame buffer
//=============================================================================
void* DX9Texture::GetFrameBuffer(void)const
{
	return frame_buffer_;
}

//=============================================================================
// convert D3DFORMAT from format
//=============================================================================
D3DFORMAT DX9Texture::ConvertD3DFORMATFromFormat_(const base::texture::FORMAT& in_format)
{
	auto d3dformat = D3DFMT_UNKNOWN;

	switch(in_format)
	{
		case base::texture::FORMAT::A8R8G8B8:
		{
			d3dformat = D3DFMT_A8R8G8B8;
			break;
		}
		case base::texture::FORMAT::R8G8B8:
		{
			d3dformat = D3DFMT_R8G8B8;
			break;
		}
		default:
		{
			d3dformat = D3DFMT_UNKNOWN;
			break;
		}
	}
	return d3dformat;
}

} // namespace texture
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------