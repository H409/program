//*****************************************************************************
//
// base device manager
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "base_device_manager.h"
#include "../texture/texture_format.h"
#include "../device_holder/base_device_holder.h"
#include "../render/base_render.h"

namespace graphic
{
namespace base
{
namespace device_manager
{
//*****************************************************************************
// using
//*****************************************************************************
using TTexture = std::shared_ptr<base::texture::BaseTexture>;
using TRenderTexture = std::shared_ptr<base::texture::BaseRenderTexture>;
using TDepthBuffer = std::shared_ptr<base::depth_buffer::BaseDepthBuffer>;
using TShader = std::shared_ptr<base::shader::BaseShader>;
using TDeviceHolder = std::shared_ptr<base::device_holder::BaseDeviceHolder>;
using TWindow = std::shared_ptr<base::window::BaseWindow>;
using TRender = std::shared_ptr<base::render::BaseRender>;

//*****************************************************************************
// constant definition
//*****************************************************************************
const texture::FORMAT BaseDeviceManager::DEFAULT_FORMAT = texture::FORMAT::NONE;

//=============================================================================
// constructor
//=============================================================================
BaseDeviceManager::BaseDeviceManager(void)
	:window_(nullptr)
	,device_holder_(nullptr)
	,is_stop_(false)
{
	auto render = std::make_shared<render::BaseRender>();

	renders_.push_back(render);
}

//=============================================================================
// destructor
//=============================================================================
BaseDeviceManager::~BaseDeviceManager(void)
{
}

//=============================================================================
// draw
//=============================================================================
bool BaseDeviceManager::Draw(void)
{
	if(device_holder_->BeginDraw())
	{
		for(auto render : renders_)
		{
			render->Draw(device_holder_);
		}
		if(device_holder_->EndDraw())
		{
			return true;
		}
	}

	return false;
}

//=============================================================================
// create texture
//=============================================================================
TTexture BaseDeviceManager::LoadTexture(const std::string& in_path)
{
	return device_holder_->LoadTexture(in_path);
}

//=============================================================================
// create texture
//=============================================================================
TShader BaseDeviceManager::LoadShader(const std::string& in_path)
{
	return device_holder_->LoadShader(in_path);
}

//=============================================================================
// create render texture
//=============================================================================
TRenderTexture BaseDeviceManager::CreateRenderTexture(const std::string & in_key,const u16 & in_width,const u16 & in_height)
{
	return CreateRenderTexture(in_key,in_width,in_height,DEFAULT_FORMAT);
}

//=============================================================================
// create render texture
//=============================================================================
TRenderTexture BaseDeviceManager::CreateRenderTexture(const std::string & in_key,const u16 & in_width,const u16 & in_height,const texture::FORMAT & in_format)
{
	auto render_texture = GetRenderTexture(in_key);

	if(render_texture == nullptr)
	{
		return device_holder_->CreateRenderTexture(in_key,in_width,in_height,in_format);
	}

	return render_texture;
}

//=============================================================================
// get render texture
//=============================================================================
TRenderTexture BaseDeviceManager::GetRenderTexture(const std::string & in_key)
{
	return device_holder_->GetRenderTexture(in_key);
}

//=============================================================================
// create depth buffer
//=============================================================================
TDepthBuffer BaseDeviceManager::CreateDepthBuffer(const std::string & in_key,const u16 & in_width,const u16 & in_height,const depth_buffer::FORMAT& in_format)
{
	auto depth_buffer = GetDepthBuffer(in_key);

	if(depth_buffer == nullptr)
	{
		return device_holder_->CreateDepthBuffer(in_key,in_width,in_height,in_format);
	}

	return depth_buffer;
}

//=============================================================================
// get depth buffer
//=============================================================================
TDepthBuffer BaseDeviceManager::GetDepthBuffer(const std::string & in_key)
{
	return device_holder_->GetDepthBuffer(in_key);
}

//=============================================================================
// create render
//=============================================================================
TRender BaseDeviceManager::CreateRender(void)
{
	return nullptr;
}

} // namespace device_manager
} // namespace base
} // namespace graphic

//---------------------------------- EOF --------------------------------------
