//*****************************************************************************
//
// directx9 shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_SHADER_H_
#define _DX9_SHADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/base/shader/base_shader.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace texture
{
class BaseTexture;
} // namespace texture
} // namespace base
namespace directx9
{
namespace shader
{
class DX9BaseShader;
} // namespace directx9
} // namespace shader
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace shader
{
class DX9Shader : public graphic::base::shader::BaseShader
{
public:
	// constructor
	DX9Shader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path);
	DX9Shader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const u32& in_id);

	// destructor
	virtual ~DX9Shader(void);

	// set value to vertex
	bool SetValueToVertex(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count)override;

	// set value to pixel
	bool SetValueToPixel(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count)override;

	// set texture to vertex
	bool SetTextureToVertex(const std::string& in_handle_name,std::shared_ptr<base::texture::BaseTexture> in_texture)override;

	// set texture to pixel
	bool SetTextureToPixel(const std::string& in_handle_name,std::shared_ptr<base::texture::BaseTexture> in_texture)override;

private:
	DX9Shader(void);
	std::shared_ptr<DX9BaseShader> vertex_shader_;
	std::shared_ptr<DX9BaseShader> pixel_shader_;
};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DX9_TEXTURE_H_

//---------------------------------- EOF --------------------------------------
