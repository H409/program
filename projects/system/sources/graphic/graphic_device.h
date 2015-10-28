//*****************************************************************************
//
// graphic device
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GRAPHIC_DEVICE_H_
#define _GRAPHIC_DEVICE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/non_copyable.h"
#include "vertex/vertex_element.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic {
namespace vertex {
class VertexBuffer;
class VertexDeclaration;
} // namespace
namespace texture {
enum class FORMAT;
class Texture;
class TextureLoader;
class CubeTextureLoader;
class RenderTexture;
class RenderTextureFactory;
} // namespace texture
namespace shader {
class ShaderLoader;
class Shader;
} // namespace shader
namespace depth_buffer {
enum class FORMAT;
class DepthBuffer;
class DepthBufferFactory;
} // namespace depth_buffer
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic {
class GraphicDevice : public utility::base::NonCopyable
{
public:
	using TVertexBuffer = std::shared_ptr<vertex::VertexBuffer>;
	using TVertexDeclaration = std::shared_ptr<vertex::VertexDeclaration>;
	using TVertexElement = vertex::VERTEX_ELEMENT;
	using TVertexElements = std::vector<TVertexElement>;
	using TTexture = std::shared_ptr<texture::Texture>;
	using TRenderTexture = std::shared_ptr<texture::RenderTexture>;
	using TShader = std::shared_ptr<shader::Shader>;
	using TDepthBuffer = std::shared_ptr<depth_buffer::DepthBuffer>;
	using TTextureLoader = std::shared_ptr<texture::TextureLoader>;
	using TCubeTextureLoader = std::shared_ptr<texture::CubeTextureLoader>;
	using TRenderTextureFactory = std::shared_ptr<texture::RenderTextureFactory>;
	using TShaderLoader = std::shared_ptr<shader::ShaderLoader>;
	using TDepthBufferFactory = std::shared_ptr<depth_buffer::DepthBufferFactory>;

	enum class CLEAR_TARGET
	{
		COLOR = 0x01,
		DEPTH = 0x02,
		STENCIL = 0x04,
		ALL = 0x07,
	};

	enum class PRIMITIVE_TYPE
	{
		NONE = -1,
		POINTLIST,
		LINELIST,
		LINESTRIP,
		TRIANGLELIST,
		TRIANGLESTRIP,
		TRIANGLEFAN,
		FORCE_DWORD,
	};

	// destructor
	virtual ~GraphicDevice(void);

	// begin draw
	bool BeginDraw(void);

	// end draw
	bool EndDraw(void);

	// HACK
	virtual bool Draw(void) { return false; }

	// draw
	bool Draw(const PRIMITIVE_TYPE& in_primitive_type,const u32& in_offset,const u32& in_primitive_count);

	// clear
	bool Clear(void);
	bool Clear(const float4& in_color,const f32& in_z);

	// set vertex declaration
	bool SetVertexDeclaration(TVertexDeclaration in_vertex_declaration);

	// set vertex buffer
	bool SetVertexBuffer(TVertexBuffer in_vertex_buffer,const u32& in_offset,const u32& in_stride);

	// set render target
	bool SetRenderTarget(const u32& in_index,TRenderTexture in_texture_target);

	// set depth buffer
	bool SetDepthBuffer(TDepthBuffer in_depth_buffer);

	// set vertex shader
	bool SetVertexShader(TShader in_shader);

	// set pixel shader
	bool SetPixelShader(TShader in_shader);

	// create vertex buffer
	TVertexBuffer CreateVertexBuffer(const u32& in_size);

	// create vertex declaration
	TVertexDeclaration CreateVertexDeclaration(const TVertexElements& in_vertex_elements);

	// load texture
	TTexture LoadTexture(const std::string& in_path);

	// load cube texture
	TTexture LoadCubeTexture(const std::string& in_path);

	// create render texture
	TRenderTexture CreateRenderTexture(const std::string& in_name,const u16& in_width,const u16& in_height,const texture::FORMAT& in_format);

	// load vertex shader
	TShader LoadVertexShader(const std::string& in_path);

	// load pixel shader
	TShader LoadPixelShader(const std::string& in_path);

	// create depth buffer
	TDepthBuffer CreateDepthBuffer(const std::string& in_key,const u16& in_width,const u16&in_height,const depth_buffer::FORMAT& in_format);

	// get render texture
	TRenderTexture GetRenderTexture(const std::string& in_name);

	// get Depth buffer
	TDepthBuffer GetDepthBuffer(const std::string& in_key);

protected:
	// constructor
	GraphicDevice(void);

	TTextureLoader texture_loader_;
	TCubeTextureLoader cube_texture_loader_;
	TRenderTextureFactory render_texture_factory_;
	TShaderLoader vertex_shader_loader_;
	TShaderLoader pixel_shader_loader_;
	TDepthBufferFactory depth_buffer_factory_;

private:
	static const u32 DEFAULT_CLEAR_TARGET;
	static const float4 DEFAULT_CLEAR_COLOR;
	static const f32 DEFAULT_CLEAR_Z;
	static const u32 DEFAULT_CLEAR_STENCIL;

	virtual bool BeginDraw_(void) = 0;
	virtual bool EndDraw_(void) = 0;
	virtual bool Clear_(const u32& in_count,const float4* in_rects,const u32& in_target,const float4& in_color,const f32& in_z,const u32& in_stencil) = 0;
	virtual bool Draw_(const PRIMITIVE_TYPE& in_primitive_type,const u32& in_offset,const u32& in_primitive_count) = 0;
	virtual bool SetVertexShader_(TShader in_shader) = 0;
	virtual bool SetPixelShader_(TShader in_shader) = 0;
	virtual bool SetVertexDeclaration_(TVertexDeclaration in_vertex_declaration) = 0;
	virtual bool SetVertexBuffer_(TVertexBuffer in_vertex_buffer,const u32& in_offset,const u32& in_stride) = 0;
	virtual bool SetRenderTarget_(const u32& in_index,TRenderTexture in_render_texture) = 0;
	virtual bool SetDepthBuffer_(TDepthBuffer in_depth_buffer) = 0;
	virtual TVertexBuffer CreateVertexBuffer_(const u32& in_size) = 0;
	virtual TVertexDeclaration CreateVertexDeclaration_(const TVertexElements& in_vertex_elements) = 0;

};

} // namespace graphic

#endif // _GRAPHIC_DEVICE_H_

	//---------------------------------- EOF --------------------------------------
