//*****************************************************************************
//
// shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/non_copyable.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic
{
namespace texture
{
class Texture;
} // namespace texture
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace shader
{
class Shader : public utility::base::NonCopyable
{
public:
	using TTexture = std::shared_ptr<texture::Texture>;

	// destructor
	virtual ~Shader(void) = default;

	// get buffer
	virtual const void* GetBuffer(void)const = 0;

	// set value
	bool SetValue(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count);

	// set texture
	bool SetTexture(const std::string& in_handle_name,TTexture in_texture);

protected:
	// constructor
	Shader(void) = default;

private:
	virtual bool SetValue_(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count) = 0;
	virtual bool SetTexture_(const std::string& in_handle_name,TTexture in_texture) = 0;

};

} // namespace shader
} // namespace graphic

#endif // _SHADER_H_

//---------------------------------- EOF --------------------------------------
