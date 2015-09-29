//*****************************************************************************
//
// directx9 base shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_base_shader.h"
#include "graphic/base/texture/base_texture.h"

namespace graphic
{
namespace directx9
{
namespace shader
{
//=============================================================================
// constructor
//=============================================================================
DX9BaseShader::DX9BaseShader(LPDIRECT3DDEVICE9 in_direct3ddevice9)
	:direct3ddevice9_(in_direct3ddevice9)
	,d3dxconstanttable_(nullptr)
	,code_(nullptr)
{
}

//=============================================================================
// constructor
//=============================================================================
DX9BaseShader::DX9BaseShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path,const std::string& in_function_name,const std::string& in_version_name)
	:DX9BaseShader(in_direct3ddevice9)
{
	LPD3DXBUFFER error = nullptr;

	if(FAILED(D3DXCompileShaderFromFile(in_path.c_str(),nullptr,nullptr,in_function_name.c_str(),in_version_name.c_str(),0,&code_,&error,&d3dxconstanttable_)))
	{
		std::string error_message = (char*)error->GetBufferPointer();
		SafeRelease(error);
		DEBUG_ASSERT_MESSAGE(false,error_message.c_str());
	}
}

//=============================================================================
// constructor
//=============================================================================
DX9BaseShader::DX9BaseShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const u32& in_id,const std::string& in_function_name,const std::string& in_version_name)
	:DX9BaseShader(in_direct3ddevice9)
{

}

//=============================================================================
// destructor
//=============================================================================
DX9BaseShader::~DX9BaseShader(void)
{
	SafeRelease(d3dxconstanttable_);
	SafeRelease(code_);
}

//=============================================================================
// set values
//=============================================================================
bool DX9BaseShader::SetValue(const std::string& in_handle_name,const void* in_value,const u32& in_byte_count)
{
	return d3dxconstanttable_->SetValue(direct3ddevice9_,in_handle_name.c_str(),in_value,in_byte_count);
}

//=============================================================================
// set texture
//=============================================================================
bool DX9BaseShader::SetTexture(const std::string& in_handle_name,std::shared_ptr<base::texture::BaseTexture> in_texture)
{
	auto handle = d3dxconstanttable_->GetSamplerIndex(in_handle_name.c_str());
	return SetTexture(handle,in_texture);
}

//=============================================================================
// set texture
//=============================================================================
bool DX9BaseShader::SetTexture(const u32& in_handle,std::shared_ptr<base::texture::BaseTexture> in_texture)
{
	return direct3ddevice9_->SetTexture(in_handle,(LPDIRECT3DTEXTURE9)in_texture->GetBuffer());
}

} // namespace shader
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
