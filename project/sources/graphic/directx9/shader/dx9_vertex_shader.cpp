//*****************************************************************************
//
// directx9 vertex shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_vertex_shader.h"

namespace graphic
{
namespace directx9
{
namespace shader
{
//*****************************************************************************
// constant definition
//*****************************************************************************
const s8* DX9VertexShader::VERSION_NAME = "vs_2_0";
const s8* DX9VertexShader::FUNCTION_NAME = "VS";

//=============================================================================
// constructor
//=============================================================================
DX9VertexShader::DX9VertexShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path)
	:DX9BaseShader(in_direct3ddevice9,in_path,FUNCTION_NAME,VERSION_NAME)
{
	if(FAILED(in_direct3ddevice9->CreateVertexShader((DWORD*)code_->GetBufferPointer(),&direct3dvertexshader9_)))
	{
		DEBUG_ASSERT_MESSAGE(false,"error create vertex shader");
	}
}

//=============================================================================
// constructor
//=============================================================================
DX9VertexShader::DX9VertexShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const u32& in_id)
	:DX9BaseShader(in_direct3ddevice9,in_id,FUNCTION_NAME,VERSION_NAME)
{
}

//=============================================================================
// destructor
//=============================================================================
DX9VertexShader::~DX9VertexShader(void)
{
}

} // namespace shader
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
