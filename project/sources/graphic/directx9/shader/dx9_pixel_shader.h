//*****************************************************************************
//
// directx9 pixel shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_PIXEL_SHADER_H_
#define _DX9_PIXEL_SHADER_H_

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
class DX9PixelShader : public DX9BaseShader
{
public:
	// constructor
	DX9PixelShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path);
	DX9PixelShader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const u32& in_id);

	// destructor
	virtual ~DX9PixelShader(void);

private:
	static const s8* VERSION_NAME;
	static const s8* FUNCTION_NAME;

	LPDIRECT3DPIXELSHADER9 direct3dpixelshader9_;
	LPD3DXCONSTANTTABLE d3dxconstanttable_;
};

} // namespace shader
} // namespace directx9
} // namespace graphic

#endif // _DX9_PIXEL_SHADER_H_

//---------------------------------- EOF --------------------------------------
