//*****************************************************************************
//
// base shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "base_shader.h"

namespace graphic
{
namespace base
{
namespace shader
{
//=============================================================================
// set value
//=============================================================================
bool BaseShader::SetValue(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count)
{
	if(!SetValueToVertex(in_handle_name,in_value,in_byte_count))
	{
		return false;
	}

	if(!SetValueToPixel(in_handle_name,in_value,in_byte_count))
	{
		return false;
	}

	return true;
}

//=============================================================================
// set texture
//=============================================================================
bool BaseShader::SetTexture(const std::string& in_handle_name,std::shared_ptr<texture::BaseTexture> in_texture)
{
	if(!SetTextureToVertex(in_handle_name,in_texture))
	{
		return false;
	}

	if(!SetTextureToPixel(in_handle_name,in_texture))
	{
		return false;
	}

	return true;
}

} // namespace shader
} // namespace base
} // namespace graphic

//---------------------------------- EOF --------------------------------------
