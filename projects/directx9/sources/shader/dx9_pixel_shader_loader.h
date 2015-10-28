//*****************************************************************************
//
// directx9 pixel shader loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DIRECTX9_PIXEL_SHADER_LOADER_H_
#define _DIRECTX9_PIXEL_SHADER_LOADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/non_copyable.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic {
namespace directx9 {
namespace shader {
class DX9PixelShader;
} // namespace shader
} // namespace directx9
} // namespace graphic
//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic {
namespace directx9 {
namespace shader {
class DX9PixelShaderLoader : public utility::base::NonCopyable
{
public:
	using TPixelShader = std::shared_ptr<DX9PixelShader>;

	// constructor
	DX9PixelShaderLoader(LPDIRECT3DDEVICE9 in_direct3ddevice9);

	// destructor
	virtual ~DX9PixelShaderLoader(void);

	// load
	TPixelShader Load(const std::string& in_path);
	TPixelShader Load(const std::string& in_path,const std::string& in_function_name,const std::string& in_version);

private:
	LPDIRECT3DDEVICE9 direct3ddevice9_;
	std::unordered_map<std::string,TPixelShader> container_;

};

} // namespace shader
} // namespace directx9
} // namespace graphic

#endif // _DIRECTX9_PIXEL_SHADER_LOADER_H_

//---------------------------------- EOF --------------------------------------
