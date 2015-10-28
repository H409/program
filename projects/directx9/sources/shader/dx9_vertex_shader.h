//*****************************************************************************
//
// directx9 vertex shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_VERTEX_SHADER_H_
#define _DX9_VERTEX_SHADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_shader.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic {
namespace directx9 {
namespace shader {
class DX9VertexShader : public DX9Shader
{
public:
	// constructor
	DX9VertexShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path);
	DX9VertexShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path,const std::string& in_function_name,const std::string& in_version);

	// destructor
	virtual ~DX9VertexShader(void);

	// get program
	LPDIRECT3DVERTEXSHADER9 GetShader(void)const;

private:
	LPDIRECT3DVERTEXSHADER9 direct3dvertexshader9_;
};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DX9_VERTEX_SHADER_H_

//---------------------------------- EOF --------------------------------------
