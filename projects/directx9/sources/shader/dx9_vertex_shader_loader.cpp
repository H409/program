//*****************************************************************************
//
// directx9 vertex shader loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_vertex_shader_loader.h"
#include "dx9_vertex_shader.h"

namespace graphic {
namespace directx9 {
namespace shader {
//=============================================================================
// constructor
//=============================================================================
DX9VertexShaderLoader::DX9VertexShaderLoader(LPDIRECT3DDEVICE9 direct3ddevice9)
	:direct3ddevice9_(direct3ddevice9)
{
}

//=============================================================================
// destructor
//=============================================================================
DX9VertexShaderLoader::~DX9VertexShaderLoader(void)
{
}

//=============================================================================
// load
//=============================================================================
DX9VertexShaderLoader::TVertexShader DX9VertexShaderLoader::Load(const std::string& in_path)
{
	auto it = container_.find(in_path);

	if(it == container_.end())
	{
		auto pixel_shader = std::make_shared<DX9VertexShader>(direct3ddevice9_,in_path);

		container_.insert(std::make_pair(in_path,pixel_shader));

		return pixel_shader;
	}

	return it->second;
}

//=============================================================================
// load
//=============================================================================
DX9VertexShaderLoader::TVertexShader DX9VertexShaderLoader::Load(const std::string& in_path,const std::string& in_function_name,const std::string& in_version)
{
	auto key = in_path + in_function_name + in_version;

	auto it = container_.find(key);

	if(it == container_.end())
	{
		auto pixel_shader = std::make_shared<DX9VertexShader>(direct3ddevice9_,in_path,in_function_name,in_version);

		container_.insert(std::make_pair(in_path,pixel_shader));

		return pixel_shader;
	}

	return it->second;

}

} // namespace texture
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
