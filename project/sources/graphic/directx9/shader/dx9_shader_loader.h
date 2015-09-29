//*****************************************************************************
//
// directx9 shader loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DIRECTX9_SHADER_LOADER_H_
#define _DIRECTX9_SHADER_LOADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/base/shader/base_shader_loader.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace shader
{
class DX9ShaderLoader : public graphic::base::shader::BaseShaderLoader
{
public:
	// constructor
	DX9ShaderLoader(LPDIRECT3DDEVICE9 direct3ddevice9);

	// destructor
	virtual ~DX9ShaderLoader(void);

private:
	LPDIRECT3DDEVICE9 direct3ddevice9_;
	virtual base::shader::BaseShader* Create(const std::string& key)override;
};

} // namespace shader
} // namespace directx9
} // namespace graphic

#endif // _DIRECTX9_TEXTURE_LOADER_H_

//---------------------------------- EOF --------------------------------------
