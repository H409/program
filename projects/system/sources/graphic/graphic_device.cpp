//*****************************************************************************
//
// graphic device
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic_device.h"
#include "vertex/vertex_buffer.h"
#include "texture/texture_loader.h"
#include "texture/cube_texture_loader.h"
#include "texture/render_texture_factory.h"
#include "shader/shader_loader.h"
#include "depth_buffer/depth_buffer_factory.h"

namespace graphic {
//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 GraphicDevice::DEFAULT_CLEAR_TARGET = (u32)CLEAR_TARGET::COLOR | (u32)CLEAR_TARGET::DEPTH;
const float4 GraphicDevice::DEFAULT_CLEAR_COLOR = float4(1.0f,1.0f,0.0f,1.0f);
const f32 GraphicDevice::DEFAULT_CLEAR_Z = 0.0f;
const u32 GraphicDevice::DEFAULT_CLEAR_STENCIL = 0;

//=============================================================================
// constructor
//=============================================================================
GraphicDevice::GraphicDevice(void)
	:texture_loader_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
GraphicDevice::~GraphicDevice(void)
{
}

//=============================================================================
// begin draw
//=============================================================================
bool GraphicDevice::BeginDraw(void)
{
	return BeginDraw_();
}

//=============================================================================
// end draw
//=============================================================================
bool GraphicDevice::EndDraw(void)
{
	return EndDraw_();
}

//=============================================================================
// draw
//=============================================================================
bool GraphicDevice::Draw(const PRIMITIVE_TYPE & in_primitive_type,const u32 & in_offset,const u32 & in_primitive_count)
{
	return Draw_(in_primitive_type,in_offset,in_primitive_count);
}

//=============================================================================
// clear
//=============================================================================
bool GraphicDevice::Clear(void)
{
	return Clear_(0,nullptr,DEFAULT_CLEAR_TARGET,DEFAULT_CLEAR_COLOR,DEFAULT_CLEAR_Z,DEFAULT_CLEAR_STENCIL);
}

//=============================================================================
// clear
//=============================================================================
bool GraphicDevice::Clear(const float4& in_color,const f32& in_z)
{
	return Clear_(0,nullptr,(u32)CLEAR_TARGET::COLOR | (u32)CLEAR_TARGET::DEPTH,in_color,in_z,0);
}

//=============================================================================
// set vertex declaration
//=============================================================================
bool GraphicDevice::SetVertexDeclaration(TVertexDeclaration in_vertex_declaration)
{
	return SetVertexDeclaration_(in_vertex_declaration);
}

//=============================================================================
// set vertex buffer
//=============================================================================
bool GraphicDevice::SetVertexBuffer(TVertexBuffer in_vertex_buffer,const u32& in_offset,const u32& in_stride)
{
	return SetVertexBuffer_(in_vertex_buffer,in_offset,in_stride);
}

//=============================================================================
// set render target
//=============================================================================
bool GraphicDevice::SetRenderTarget(const u32& in_index,TRenderTexture in_render_texture)
{
	return SetRenderTarget_(in_index,in_render_texture);
}

//=============================================================================
// set depth buffer
//=============================================================================
bool GraphicDevice::SetDepthBuffer(TDepthBuffer in_depth_buffer)
{
	return SetDepthBuffer_(in_depth_buffer);
}

//=============================================================================
// set vertex shader
//=============================================================================
bool GraphicDevice::SetVertexShader(TShader in_shader)
{
	return SetVertexShader_(in_shader);
}

//=============================================================================
// set pixel shader
//=============================================================================
bool GraphicDevice::SetPixelShader(TShader in_shader)
{
	return SetPixelShader_(in_shader);
}

//=============================================================================
// create vertex buffer
//=============================================================================
GraphicDevice::TVertexBuffer GraphicDevice::CreateVertexBuffer(const u32 & in_size)
{
	return CreateVertexBuffer_(in_size);
}

//=============================================================================
// create vertex declaration
//=============================================================================
GraphicDevice::TVertexDeclaration GraphicDevice::CreateVertexDeclaration(const TVertexElements& in_vertex_elements)
{
	return CreateVertexDeclaration_(in_vertex_elements);
}

//=============================================================================
// load texture
//=============================================================================
GraphicDevice::TTexture GraphicDevice::LoadTexture(const std::string& in_path)
{
	DEBUG_ASSERT(texture_loader_ != nullptr);
	return texture_loader_->Get(in_path);
}

//=============================================================================
// load cube texture
//=============================================================================
GraphicDevice::TTexture GraphicDevice::LoadCubeTexture(const std::string & in_path)
{
	DEBUG_ASSERT(cube_texture_loader_ != nullptr);
	return cube_texture_loader_->Get(in_path);
}

//=============================================================================
// load vertex shader
//=============================================================================
GraphicDevice::TShader GraphicDevice::LoadVertexShader(const std::string& in_path)
{
	DEBUG_ASSERT(vertex_shader_loader_ != nullptr);
	return vertex_shader_loader_->Get(in_path);
}

//=============================================================================
// load pixel shader
//=============================================================================
GraphicDevice::TShader GraphicDevice::LoadPixelShader(const std::string & in_path)
{
	DEBUG_ASSERT(pixel_shader_loader_ != nullptr);
	return pixel_shader_loader_->Get(in_path);
}

//=============================================================================
// create render texture
//=============================================================================
GraphicDevice::TRenderTexture GraphicDevice::CreateRenderTexture(const std::string & in_name,const u16 & in_width,const u16 & in_height,const texture::FORMAT & in_format)
{
	DEBUG_ASSERT(render_texture_factory_ != nullptr);
	auto render_texture = GetRenderTexture(in_name);

	if(render_texture == nullptr)
	{
		return render_texture_factory_->Create(in_name,in_width,in_height,in_format);
	}

	return render_texture;
}

//=============================================================================
// get render texture
//=============================================================================
GraphicDevice::TRenderTexture GraphicDevice::GetRenderTexture(const std::string & in_name)
{
	DEBUG_ASSERT(render_texture_factory_ != nullptr);
	return render_texture_factory_->Get(in_name);
}
//=============================================================================
// create depth buffer
//=============================================================================
GraphicDevice::TDepthBuffer GraphicDevice::CreateDepthBuffer(const std::string & in_key,const u16 & in_width,const u16 & in_height,const depth_buffer::FORMAT & in_format)
{
	DEBUG_ASSERT(depth_buffer_factory_ != nullptr);
	auto depth_buffer = GetDepthBuffer(in_key);

	if(depth_buffer == nullptr)
	{
		return depth_buffer_factory_->Create(in_key,in_width,in_height,in_format);
	}

	return depth_buffer;
}

//=============================================================================
// create depth buffer
//=============================================================================
GraphicDevice::TDepthBuffer GraphicDevice::GetDepthBuffer(const std::string & in_key)
{
	DEBUG_ASSERT(depth_buffer_factory_ != nullptr);
	return depth_buffer_factory_->Get(in_key);
}

} // namespace graphic

//---------------------------------- EOF --------------------------------------
