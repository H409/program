//*****************************************************************************
//
// base shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_SHADER_H_
#define _BASE_SHADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/non_copyable.h"

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
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace shader
{
class BaseShader : public common::base::NonCopyable
{
public:
	// destructor
	virtual ~BaseShader(void) = default;

	// set value
	bool SetValue(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count);

	// set texture
	bool SetTexture(const std::string& in_handle_name,std::shared_ptr<texture::BaseTexture> in_texture);

	// set value to vertex
	virtual bool SetValueToVertex(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count) = 0;

	// set value to pixel
	virtual bool SetValueToPixel(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count) = 0;

	// set texture to vertex
	virtual bool SetTextureToVertex(const std::string& in_handle_name,std::shared_ptr<texture::BaseTexture> in_texture) = 0;

	// set texture to pixel
	virtual bool SetTextureToPixel(const std::string& in_handle_name,std::shared_ptr<texture::BaseTexture> in_texture) = 0;

protected:
	// constructor
	BaseShader(void) = default;

private:

};

} // namespace shader
} // namespace base
} // namespace graphic

#endif // _BASE_SHADER_H_

//---------------------------------- EOF --------------------------------------
