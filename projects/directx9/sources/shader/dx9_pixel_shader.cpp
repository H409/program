//*****************************************************************************
//
// directx9 pixel shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_pixel_shader.h"

namespace graphic {
namespace directx9 {
namespace shader {
//=============================================================================
// constructor
//=============================================================================
DX9PixelShader::DX9PixelShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path)
	:DX9Shader(in_direct3ddevice9,in_path)
{
	DEBUG_ASSERT(in_direct3ddevice9->CreatePixelShader(program_,&direct3dpixelshader9_) == S_OK);

	DEBUG_ASSERT(D3DXGetShaderConstantTable(program_,&d3dxconstanttable_) == S_OK);
}

DX9PixelShader::DX9PixelShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path,const std::string& in_function_name,const std::string& in_version)
	:DX9Shader(in_direct3ddevice9,in_path,in_function_name,in_version)
{
	DEBUG_ASSERT(in_direct3ddevice9->CreatePixelShader(program_,&direct3dpixelshader9_) == S_OK);
}

//=============================================================================
// destructor
//=============================================================================
DX9PixelShader::~DX9PixelShader(void)
{
	SafeRelease(direct3dpixelshader9_);
}

//=============================================================================
// get shader
//=============================================================================
LPDIRECT3DPIXELSHADER9 DX9PixelShader::GetShader(void) const
{
	return direct3dpixelshader9_;
}

} // namespace shader
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
