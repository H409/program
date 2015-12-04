//*****************************************************************************
//
// directx9 shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_shader.h"
#include "dx9_vertex_shader.h"
#include "dx9_pixel_shader.h"
#include "../texture/dx9_texture.h"

namespace graphic {
namespace directx9 {
namespace shader {
//=============================================================================
// constructor
//=============================================================================
DX9Shader::DX9Shader(LPDIRECT3DDEVICE9 in_direct3ddevice9)
	//:Shader()
	:direct3ddevice9_(in_direct3ddevice9)
	,d3dxconstanttable_(nullptr)
{
}

//=============================================================================
// constructor
//=============================================================================
DX9Shader::DX9Shader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path,const std::string& in_function_name,const std::string& in_version_name)
	:DX9Shader(in_direct3ddevice9)
{
	LPD3DXBUFFER error = nullptr;
	LPD3DXBUFFER code = nullptr;

	if(FAILED(D3DXCompileShaderFromFile(in_path.c_str(),nullptr,nullptr,in_function_name.c_str(),in_version_name.c_str(),0,&code,&error,&d3dxconstanttable_)))
	{
		std::string error_message;

		if(error != nullptr)
		{
			error_message = (char*)error->GetBufferPointer();
			SafeRelease(error);
		}
		else
		{
			error_message = "no such file";
		}
		DEBUG_ASSERT_MESSAGE(false,error_message.c_str());
	}
	program_ = (DWORD*)code->GetBufferPointer();
}

//=============================================================================
// constructor
//=============================================================================
DX9Shader::DX9Shader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string & in_path)
	:DX9Shader(in_direct3ddevice9)
{
	FILE* file = nullptr;
	fopen_s(&file,in_path.c_str(),"rb");
	if(file != nullptr)
	{
		fseek(file,0,SEEK_END);
		auto size = ftell(file);
		fseek(file,0,SEEK_SET);
		program_ = new DWORD[size];
		fread(program_,1,size,file);
		fclose(file);
	}
}

//=============================================================================
// destructor
//=============================================================================
DX9Shader::~DX9Shader(void)
{
	SafeDeleteArray(program_);
	SafeRelease(d3dxconstanttable_);
}

//=============================================================================
// set value
//=============================================================================
void DX9Shader::SetValue(const std::string & in_handle_name,const f32& in_value)
{
	d3dxconstanttable_->SetFloat(direct3ddevice9_,in_handle_name.c_str(),in_value);
}

//=============================================================================
// set value
//=============================================================================
void DX9Shader::SetValue(const std::string& in_handle_name,const f32* in_value,const u32& in_count)
{
	//DEBUG_ASSERT(d3dxconstanttable_->SetFloatArray(direct3ddevice9_,in_handle_name.c_str(),in_value,in_count) == S_OK);
	d3dxconstanttable_->SetFloatArray(direct3ddevice9_,in_handle_name.c_str(),in_value,in_count);
}

//=============================================================================
// get program
//=============================================================================
//const DWORD* DX9Shader::GetProgram(void)const
//{
//	return program_;
//}

//=============================================================================
// set texture
//=============================================================================
void DX9Shader::SetTexture(const std::string& in_handle_name,LPDIRECT3DTEXTURE9 in_direct3dtexture9)
{
	auto index = d3dxconstanttable_->GetSamplerIndex(in_handle_name.c_str());
	SetTexture(index,in_direct3dtexture9);
}

//=============================================================================
// set texture
//=============================================================================
void DX9Shader::SetTexture(const u32& in_handle,LPDIRECT3DTEXTURE9 in_direct3dtexture9)
{
	DEBUG_ASSERT(direct3ddevice9_->SetTexture(in_handle,in_direct3dtexture9) == S_OK);
}

//=============================================================================
// set texture
//=============================================================================
void DX9Shader::SetTexture(const std::string& in_handle_name,TTexture in_texture)
{
	SetTexture(in_handle_name,in_texture->GetTexture());
}

//=============================================================================
// get constant table
//=============================================================================
LPD3DXCONSTANTTABLE DX9Shader::GetConstantTable(void)const
{
	return d3dxconstanttable_;
}

} // namespace shader
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
