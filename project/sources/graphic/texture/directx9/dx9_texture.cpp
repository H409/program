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
DX9Texture::DX9Texture(const std::string& in_path,LPDIRECT3DDEVICE9 in_direct3ddevice9)
{
	D3DXCreateTextureFromFile(in_direct3ddevice9,in_path.c_str(),&direct3dtexture9_);
}

//=============================================================================
// constructor
//=============================================================================
DX9Texture::DX9Texture(const u32& in_id,LPDIRECT3DDEVICE9 in_direct3ddevice9)
{
	D3DXCreateTextureFromResource(in_direct3ddevice9,NULL,MAKEINTRESOURCE(in_id),&direct3dtexture9_);
}

//=============================================================================
// destructor
//=============================================================================
DX9Texture::~DX9Texture(void)
{
	SafeRelease(direct3dtexture9_);
}

//=============================================================================
// get buffer
//=============================================================================
void* DX9Texture::GetBuffer(void)
{
	return direct3dtexture9_;
}

} // namespace texture
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
