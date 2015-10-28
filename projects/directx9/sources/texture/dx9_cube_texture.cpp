//*****************************************************************************
//
// directx9 cube texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_cube_texture.h"

namespace graphic
{
namespace directx9
{
namespace texture
{
//=============================================================================
// constructor
//=============================================================================
DX9CubeTexture::DX9CubeTexture(void)
	:direct3dcubetexture9_(nullptr)
{

}

//=============================================================================
// constructor
//=============================================================================
DX9CubeTexture::DX9CubeTexture(const std::string& in_path,LPDIRECT3DDEVICE9 in_direct3ddevice9)
	:DX9CubeTexture()
{
	DEBUG_ASSERT(in_direct3ddevice9 != nullptr);
	D3DXCreateCubeTextureFromFile(in_direct3ddevice9,in_path.c_str(),&direct3dcubetexture9_);
}

//=============================================================================
// constructor
//=============================================================================
DX9CubeTexture::DX9CubeTexture(const u32& in_id,LPDIRECT3DDEVICE9 in_direct3ddevice9)
	:DX9CubeTexture()
{
	DEBUG_ASSERT(in_direct3ddevice9 != nullptr);
	D3DXCreateCubeTextureFromResource(in_direct3ddevice9,NULL,MAKEINTRESOURCE(in_id),&direct3dcubetexture9_);
}

//=============================================================================
// destructor
//=============================================================================
DX9CubeTexture::~DX9CubeTexture(void)
{
	SafeRelease(direct3dcubetexture9_);
}

//=============================================================================
// get buffer
//=============================================================================
void* DX9CubeTexture::GetBuffer(void)const
{
	return direct3dcubetexture9_;
}

} // namespace texture
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
