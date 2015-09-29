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

namespace graphic
{
namespace directx9
{
namespace shader
{
//*****************************************************************************
// constant definition
//*****************************************************************************
const s8* DX9PixelShader::VERSION_NAME = "vs_2_0";
const s8* DX9PixelShader::FUNCTION_NAME = "VS";

//=============================================================================
// constructor
//=============================================================================
DX9PixelShader::DX9PixelShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path)
	:DX9BaseShader(in_direct3ddevice9,in_path,FUNCTION_NAME,VERSION_NAME)
{
	LPD3DXBUFFER error;

	if(FAILED(in_direct3ddevice9->CreatePixelShader((DWORD*)code_->GetBufferPointer(),&direct3dpixelshader9_)))
	{
		DEBUG_ASSERT_MESSAGE(false,"error create pixel shader");
	}
}

//=============================================================================
// constructor
//=============================================================================
DX9PixelShader::DX9PixelShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const u32& in_id)
	:DX9BaseShader(in_direct3ddevice9,in_id,FUNCTION_NAME,VERSION_NAME)
{
}

//=============================================================================
// destructor
//=============================================================================
DX9PixelShader::~DX9PixelShader(void)
{
}

} // namespace shader
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
