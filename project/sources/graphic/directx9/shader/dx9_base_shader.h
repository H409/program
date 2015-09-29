//*****************************************************************************
//
// directx9 base shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_BASE_SHADER_H_
#define _DX9_BASE_SHADER_H_

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
namespace directx9
{
namespace shader
{
class DX9BaseShader : public common::base::NonCopyable
{
public:
	// constructor
	DX9BaseShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path,const std::string& in_function_name,const std::string& in_version_name);
	DX9BaseShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const u32& in_id,const std::string& in_function_name,const std::string& in_version_name);

	// destructor
	virtual ~DX9BaseShader(void);

	// set values
	bool SetValue(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count);

	// set texture
	bool SetTexture(const std::string& in_handle_name,std::shared_ptr<base::texture::BaseTexture> in_texture);
	bool SetTexture(const u32& in_handle,std::shared_ptr<base::texture::BaseTexture> in_texture);

protected:
	LPDIRECT3DDEVICE9 direct3ddevice9_;
	LPD3DXCONSTANTTABLE d3dxconstanttable_;
	LPD3DXBUFFER code_;
private:
	explicit DX9BaseShader(LPDIRECT3DDEVICE9 in_direct3ddevice9);
};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DX9_TEXTURE_H_

//---------------------------------- EOF --------------------------------------
