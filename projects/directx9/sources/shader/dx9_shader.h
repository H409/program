//*****************************************************************************
//
// directx9 shader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_SHADER_H_
#define _DX9_SHADER_H_

//*****************************************************************************
// include
//*****************************************************************************


//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic {
namespace directx9 {
namespace shader {
class DX9Shader
{
public:
	// destructor
	virtual ~DX9Shader(void);

	// set value
	void SetValue(const std::string& in_handle_name,const f32& in_value);
	void SetValue(const std::string& in_handle_name,const f32* in_value,const u32& in_count);

	// set texture
	void SetTexture(const std::string& in_handle_name,LPDIRECT3DTEXTURE9 in_direct3dtexture9);
	void SetTexture(const u32& in_handle,LPDIRECT3DTEXTURE9 in_direct3dtexture9);

	// get constant table
	LPD3DXCONSTANTTABLE GetConstantTable(void)const;

protected:
	// constructor
	DX9Shader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path,const std::string& in_function_name,const std::string& in_version_name);
	DX9Shader(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_path);

	LPDIRECT3DDEVICE9 direct3ddevice9_;
	LPD3DXCONSTANTTABLE d3dxconstanttable_;
	DWORD* program_;

private:
	explicit DX9Shader(LPDIRECT3DDEVICE9 in_direct3ddevice9);

};

} // namespace shader
} // namespace directx9
} // namespace graphic

#endif // _DX9_Shader_H_

//---------------------------------- EOF --------------------------------------
