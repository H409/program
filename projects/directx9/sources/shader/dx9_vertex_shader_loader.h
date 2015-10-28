//*****************************************************************************
//
// directx9 vertex shader loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DIRECTX9_VERTEX_SHADER_LOADER_H_
#define _DIRECTX9_VERTEX_SHADER_LOADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/flyweight.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic {
namespace directx9 {
namespace shader {
class DX9VertexShader;
} // namespace shader
} // namespace directx9
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic {
namespace directx9 {
namespace shader {
class DX9VertexShaderLoader// : public utility::base::Flyweight<std::string,DX9VertexShader>
{
public:
	using TVertexShader = std::shared_ptr<shader::DX9VertexShader>;

	// constructor
	DX9VertexShaderLoader(LPDIRECT3DDEVICE9 direct3ddevice9);

	// destructor
	virtual ~DX9VertexShaderLoader(void);

	// get
	TVertexShader Load(const std::string& in_path);
	TVertexShader Load(const std::string& in_path,const std::string& in_function_name,const std::string& in_version);

private:
	LPDIRECT3DDEVICE9 direct3ddevice9_;
	std::unordered_map<std::string,TVertexShader> container_;
};

} // namespace shader
} // namespace directx9
} // namespace graphic

#endif // _DIRECTX9_VERTEX_SHADER_LOADER_H_

//---------------------------------- EOF --------------------------------------
