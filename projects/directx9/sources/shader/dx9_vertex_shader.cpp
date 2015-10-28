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

namespace graphic {
namespace directx9 {
namespace shader {
//=============================================================================
// constructor
//=============================================================================
DX9VertexShader::DX9VertexShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path)
	:DX9Shader(in_direct3ddevice9,in_path)
{
	if(FAILED(in_direct3ddevice9->CreateVertexShader(program_,&direct3dvertexshader9_)))
	{
		DEBUG_ASSERT_MESSAGE(false,"error create vertex shader");
	}

	if(FAILED(D3DXGetShaderConstantTable(program_,&d3dxconstanttable_)))
	{
		DEBUG_ASSERT_MESSAGE(false,"failed get constant table");
	}
}

//=============================================================================
// constructor
//=============================================================================
DX9VertexShader::DX9VertexShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string & in_path,const std::string & in_function_name,const std::string& in_version)
	:DX9Shader(in_direct3ddevice9,in_path,in_function_name,in_version)
{
	if(FAILED(in_direct3ddevice9->CreateVertexShader(program_,&direct3dvertexshader9_)))
	{
		DEBUG_ASSERT_MESSAGE(false,"error create vertex shader");
	}
}

//=============================================================================
// destructor
//=============================================================================
DX9VertexShader::~DX9VertexShader(void)
{
}

//=============================================================================
// get buffer
//=============================================================================
LPDIRECT3DVERTEXSHADER9 DX9VertexShader::GetShader(void)const
{
	return direct3dvertexshader9_;
}

} // namespace shader
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
