//*****************************************************************************
//
// base device holder
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "base_device_holder.h"
#include "../texture/base_texture_loader.h"
#include "../texture/base_render_texture_factory.h"
#include "../shader/base_shader_loader.h"
#include "../depth_buffer/base_depth_buffer_factory.h"

namespace graphic
{
namespace base
{
namespace device_holder
{
//*****************************************************************************
// using
//*****************************************************************************
using TTexture = std::shared_ptr<texture::BaseTexture>;
using TDepthBuffer = std::shared_ptr<depth_buffer::BaseDepthBuffer>;
using TRenderTexture = std::shared_ptr<texture::BaseRenderTexture>;
using TShader = std::shared_ptr<shader::BaseShader>;

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 BaseDeviceHolder::DEFAULT_CLEAR_TARGET = (u32)CLEAR_TARGET::COLOR | (u32)CLEAR_TARGET::DEPTH;
const float4 BaseDeviceHolder::DEFAULT_CLEAR_COLOR = float4(1.0f,1.0f,0.0f,1.0f);
const f32 BaseDeviceHolder::DEFAULT_CLEAR_Z = 0.0f;
const u32 BaseDeviceHolder::DEFAULT_CLEAR_STENCIL = 0;

//=============================================================================
// constructor
//=============================================================================
BaseDeviceHolder::BaseDeviceHolder(void)
	:texture_loader_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
BaseDeviceHolder::~BaseDeviceHolder(void)
{
}

//=============================================================================
// begin draw
//=============================================================================
bool BaseDeviceHolder::BeginDraw(void)
{
	return BeginDraw_();
}

//=============================================================================
// end draw
//=============================================================================
bool BaseDeviceHolder::EndDraw(void)
{
	return EndDraw_();
}

//=============================================================================
// clear
//=============================================================================
bool BaseDeviceHolder::Clear(void)
{
	return Clear_(0,nullptr,DEFAULT_CLEAR_TARGET,DEFAULT_CLEAR_COLOR,DEFAULT_CLEAR_Z,DEFAULT_CLEAR_STENCIL);
}

//=============================================================================
// clear
//=============================================================================
bool BaseDeviceHolder::Clear(const float4& in_color,const f32& in_z)
{
	return Clear_(0,nullptr,(u32)CLEAR_TARGET::COLOR | (u32)CLEAR_TARGET::DEPTH,in_color,in_z,0);
}

//=============================================================================
// set render target
//=============================================================================
bool BaseDeviceHolder::SetRenderTarget(const u32& in_index,TRenderTexture in_render_texture)
{
	return SetRenderTarget_(in_index,in_render_texture);
}

//=============================================================================
// set depth buffer
//=============================================================================
bool BaseDeviceHolder::SetDepthBuffer(TDepthBuffer in_depth_buffer)
{
	return SetDepthBuffer_(in_depth_buffer);
}

//=============================================================================
// load texture
//=============================================================================
TTexture BaseDeviceHolder::LoadTexture(const std::string& in_path)
{
	DEBUG_ASSERT(texture_loader_ != nullptr);
	return texture_loader_->Get(in_path);
}

//=============================================================================
// load shader
//=============================================================================
TShader BaseDeviceHolder::LoadShader(const std::string& in_path)
{
	DEBUG_ASSERT(shader_loader_ != nullptr);
	return shader_loader_->Get(in_path);
}

//=============================================================================
// create render texture
//=============================================================================
TRenderTexture BaseDeviceHolder::CreateRenderTexture(const std::string & in_name,const u16 & in_width,const u16 & in_height,const texture::FORMAT & in_format)
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
TRenderTexture BaseDeviceHolder::GetRenderTexture(const std::string & in_name)
{
	DEBUG_ASSERT(render_texture_factory_ != nullptr);
	return render_texture_factory_->Get(in_name);
}
//=============================================================================
// create depth buffer
//=============================================================================
TDepthBuffer BaseDeviceHolder::CreateDepthBuffer(const std::string & in_key,const u16 & in_width,const u16 & in_height,const depth_buffer::FORMAT & in_format)
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
TDepthBuffer BaseDeviceHolder::GetDepthBuffer(const std::string & in_key)
{
	DEBUG_ASSERT(depth_buffer_factory_ != nullptr);
	return depth_buffer_factory_->Get(in_key);
}

} // namespace device_holder
} // namespace base
} // namespace graphic

//---------------------------------- EOF --------------------------------------
