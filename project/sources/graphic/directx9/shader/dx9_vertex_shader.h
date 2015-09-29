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
#include "dx9_base_shader.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace shader
{
class DX9VertexShader : public DX9BaseShader
{
public:
	// constructor
	DX9VertexShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path);
	DX9VertexShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const u32& in_id);

	// destructor
	virtual ~DX9VertexShader(void);

private:
	static const s8* VERSION_NAME;
	static const s8* FUNCTION_NAME;

	LPDIRECT3DVERTEXSHADER9 direct3dvertexshader9_;
	LPD3DXCONSTANTTABLE d3dxconstanttable_;
};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DX9_VERTEX_SHADER_H_

//---------------------------------- EOF --------------------------------------
