//*****************************************************************************
//
// directx9 shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_shader.h"
#include "dx9_vertex_shader.h"
#include "dx9_pixel_shader.h"
#include "graphic/base/texture/base_texture.h"

namespace graphic
{
namespace directx9
{
namespace shader
{
//=============================================================================
// constructor
//=============================================================================
DX9Shader::DX9Shader(void)
	:BaseShader()
	,vertex_shader_()
	,pixel_shader_()
{
}

//=============================================================================
// constructor
//=============================================================================
DX9Shader::DX9Shader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path)
	:DX9Shader()
{
	vertex_shader_ = std::make_shared<DX9VertexShader>(in_direct3ddevice9,in_path);
	pixel_shader_ = std::make_shared<DX9PixelShader>(in_direct3ddevice9,in_path);
}

//=============================================================================
// constructor
//=============================================================================
DX9Shader::DX9Shader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const u32& in_id)
	:DX9Shader()
{

}

//=============================================================================
// destructor
//=============================================================================
DX9Shader::~DX9Shader(void)
{
}

//=============================================================================
// set value to vertex
//=============================================================================
bool DX9Shader::SetValueToVertex(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count)
{
	return vertex_shader_->SetValue(in_handle_name,in_value,in_byte_count);
}

//=============================================================================
// set value to pixel
//=============================================================================
bool DX9Shader::SetValueToPixel(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count)
{
	return pixel_shader_->SetValue(in_handle_name,in_value,in_byte_count);
}

//=============================================================================
// set texture to vertex
//=============================================================================
bool DX9Shader::SetTextureToVertex(const std::string& in_handle_name,std::shared_ptr<base::texture::BaseTexture> in_texture)
{
	return vertex_shader_->SetTexture(in_handle_name,in_texture);
}

//=============================================================================
// set texture to pixel
//=============================================================================
bool DX9Shader::SetTextureToPixel(const std::string& in_handle_name,std::shared_ptr<base::texture::BaseTexture> in_texture)
{
	return pixel_shader_->SetTexture(in_handle_name,in_texture);
}

} // namespace shader
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
