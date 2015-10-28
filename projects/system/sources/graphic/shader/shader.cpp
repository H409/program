//*****************************************************************************
//
// shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "shader.h"

namespace graphic {
namespace shader {
//=============================================================================
// set value
//=============================================================================
bool Shader::SetValue(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count)
{
	return SetValue_(in_handle_name,in_value,in_byte_count);
}

//=============================================================================
// set texture
//=============================================================================
bool Shader::SetTexture(const std::string& in_handle_name,TTexture in_texture)
{
	return SetTexture_(in_handle_name,in_texture);
}

} // namespace shader
} // namespace graphic

//---------------------------------- EOF --------------------------------------
