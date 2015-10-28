//*****************************************************************************
//
// directx9 pixel shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_PIXEL_SHADER_H_
#define _DX9_PIXEL_SHADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_shader.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic {
namespace directx9 {
namespace shader {
class DX9PixelShader : public DX9Shader
{
public:
	// constructor
	DX9PixelShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path);
	DX9PixelShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path,const std::string& in_function_name,const std::string& in_version);

	// destructor
	virtual ~DX9PixelShader(void);

	// get program
	LPDIRECT3DPIXELSHADER9 GetShader(void)const;

private:
	LPDIRECT3DPIXELSHADER9 direct3dpixelshader9_;
};

} // namespace shader
} // namespace directx9
} // namespace graphic

#endif // _DX9_PIXEL_SHADER_H_

//---------------------------------- EOF --------------------------------------
