//*****************************************************************************
//
// directx9 device
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_DEVICE_H_
#define _DX9_DEVICE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/non_copyable.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic {
namespace directx9 {
namespace texture {
class DX9Texture;
class DX9TextureLoader;
} // namespace texture
namespace shader {
class DX9VertexShader;
class DX9VertexShaderLoader;
class DX9PixelShader;
class DX9PixelShaderLoader;
} // namespace shader
} // namespace directx9
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic {
namespace directx9 {
class DX9Device : public utility::base::NonCopyable
{
public:
	using TTexture = std::shared_ptr<texture::DX9Texture>;
	using TTextureLoader = std::shared_ptr<texture::DX9TextureLoader>;
	using TVertexShader = std::shared_ptr<shader::DX9VertexShader>;
	using TVertexShaderLoader = std::shared_ptr<shader::DX9VertexShaderLoader>;
	using TPixelShader = std::shared_ptr<shader::DX9PixelShader>;
	using TPixelShaderLoader = std::shared_ptr<shader::DX9PixelShaderLoader>;

	// constructor
	DX9Device(const HWND& in_hwnd,const u16& in_width,const u16& in_height);

	// destructor
	virtual ~DX9Device(void);

	// begin rendering
	bool BeginRendering(void);

	// end rendering
	bool EndRendering(void);

	// clear
	bool Clear(const float4& in_color);
	bool Clear(const float4& in_color,const f32& in_z);
	bool Clear(const float4& in_color,const f32& in_z,const u32& in_stencil);

	// get direct device
	LPDIRECT3DDEVICE9 GetDevice(void);

	// load texture
	TTexture LoadTexture(const std::string& in_path);

	// create texture
	TTexture CreateTexture(const u16& in_width,const u16& in_height,const D3DFORMAT& in_format);

	// set render target
	void SetRenderTarget(const u32& in_index,TTexture in_texture);

	// get render target
	TTexture GetRenderTarget(const u32& in_index);

	// load vertex shader
	TVertexShader LoadVertexShader(const std::string& in_path);
	TVertexShader LoadVertexShader(const std::string& in_path,const std::string& in_function,const std::string& in_version);

	// load pixel shader
	TPixelShader LoadPixelShader(const std::string& in_path);
	TPixelShader LoadPixelShader(const std::string& in_path,const std::string& in_function,const std::string& in_version);

	// set vertex shader
	void SetVertexShader(TVertexShader in_vertex_shader);

	// set pixel shader
	void SetPixelShader(TPixelShader in_pixel_shader);

private:
	// constructor
	explicit DX9Device(const HWND& in_hwnd);

	HWND hwnd_;
	LPDIRECT3DDEVICE9 direct3ddevice9_;
	LPDIRECT3D9 direct3d9_;
	D3DPRESENT_PARAMETERS d3dpresent_parameters_;
	D3DDISPLAYMODE d3ddisplaymode_;
	LPDIRECT3DSURFACE9 default_render_target_;
	LPDIRECT3DSURFACE9 default_depthStencil_;

	TTextureLoader texture_loader_;
	TVertexShaderLoader vertex_shader_loader_;
	TPixelShaderLoader pixel_shader_loader_;

	// デフォルトレンダーステートの設定
	void SetDefaultRenderState_(void);

	// デフォルトサンプラーステートの設定
	void SetDefaultSamplerState_(void);

	// デフォルトテクスチャステージステートの設定
	void SetDefaultTextureStageState_(void);
};

} // namespace directx9
} // namespace graphic

#endif // _DX9_DEVICE_HOLDER_H_

//---------------------------------- EOF --------------------------------------
