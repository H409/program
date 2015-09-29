//*****************************************************************************
//
// base device manager
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_DEVICE_MANAGER_H_
#define _BASE_DEVICE_MANAGER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/non_copyable.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace window
{
class BaseWindow;
} // namespace window
namespace render
{
class BaseRender;
} // namespace render
namespace device_holder
{
class BaseDeviceHolder;
} // namespace device_holder
namespace texture
{
enum class FORMAT;
class BaseTexture;
class BaseRenderTexture;
} // namespace texture
namespace depth_buffer
{
enum class FORMAT;
class BaseDepthBuffer;
}// namespace depth_buffer
namespace shader
{
class BaseShader;
} // namespace shader
} // namespace base
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace device_manager
{
class BaseDeviceManager : public common::base::NonCopyable
{
public:
	using TTexture = std::shared_ptr<base::texture::BaseTexture>;
	using TRenderTexture = std::shared_ptr<base::texture::BaseRenderTexture>;
	using TDepthBuffer = std::shared_ptr<base::depth_buffer::BaseDepthBuffer>;
	using TShader = std::shared_ptr<base::shader::BaseShader>;
	using TDeviceHolder = std::shared_ptr<base::device_holder::BaseDeviceHolder>;
	using TWindow = std::shared_ptr<base::window::BaseWindow>;
	using TRender = std::shared_ptr<base::render::BaseRender>;

	// load texture
	TTexture LoadTexture(const std::string& in_path);

	// load shader
	TShader LoadShader(const std::string& in_path);

	// create render texture
	TRenderTexture CreateRenderTexture(const std::string& in_key,const u16& in_width,const u16& in_height);
	TRenderTexture CreateRenderTexture(const std::string& in_key,const u16& in_width,const u16& in_height,const texture::FORMAT& in_format);

	// get render texture
	TRenderTexture GetRenderTexture(const std::string& in_key);

	// create depth buffer
	TDepthBuffer CreateDepthBuffer(const std::string& in_key,const u16& in_width,const u16& in_height,const depth_buffer::FORMAT& in_format);

	// get depth buffer
	TDepthBuffer GetDepthBuffer(const std::string& in_key);

	// create render
	TRender CreateRender(void);

	// destructor
	virtual ~BaseDeviceManager(void);

	// draw
	bool Draw(void);

	// accessor
	const bool& __is_stop(void)const{ return is_stop_; }

protected:
	// constructor
	BaseDeviceManager(void);

	static const texture::FORMAT DEFAULT_FORMAT;

	TWindow window_;
	TDeviceHolder device_holder_;
	std::vector<TRender> renders_;
	bool is_stop_;
};

} // namespace device_manager
} // namespace base
} // namespace graphic

#endif // _BASE_DEVICE_MANAGER_H_

//---------------------------------- EOF --------------------------------------
