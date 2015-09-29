//*****************************************************************************
//
// base device holder
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_DEVICE_HOLDER_H_
#define _BASE_DEVICE_HOLDER_H_

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
namespace texture
{
enum class FORMAT;
class BaseTextureLoader;
class BaseTexture;
class BaseRenderTexture;
class BaseRenderTextureFactory;
} // namespace texture
namespace shader
{
class BaseShaderLoader;
class BaseShader;
} // namespace shader
namespace depth_buffer
{
enum class FORMAT;
class BaseDepthBuffer;
class BaseDepthBufferFactory;
} // namespace depth_buffer
} // namespace base
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace device_holder
{
class BaseDeviceHolder : public common::base::NonCopyable
{
public:
	using TTexture = std::shared_ptr<texture::BaseTexture>;
	using TRenderTexture = std::shared_ptr<texture::BaseRenderTexture>;
	using TShader = std::shared_ptr<shader::BaseShader>;
	using TDepthBuffer = std::shared_ptr<depth_buffer::BaseDepthBuffer>;
	using TDepthBufferFactory = std::shared_ptr<depth_buffer::BaseDepthBufferFactory>;
	using TTextureLoader = std::shared_ptr<texture::BaseTextureLoader>;
	using TShaderLoader = std::shared_ptr<shader::BaseShaderLoader>;
	using TRenderTextureFactory = std::shared_ptr<texture::BaseRenderTextureFactory>;

	enum class CLEAR_TARGET
	{
		COLOR	= 0x01,
		DEPTH	= 0x02,
		STENCIL	= 0x04,
		ALL		= 0x07,
	};

	// begin draw
	bool BeginDraw(void);

	// end draw
	bool EndDraw(void);

	// clear
	bool Clear(void);
	bool Clear(const float4& in_color,const f32& in_z);

	// set render target
	bool SetRenderTarget(const u32& in_index,TRenderTexture in_texture_target);

	// set depth buffer
	bool SetDepthBuffer(TDepthBuffer in_depth_buffer);

	// load texture
	TTexture LoadTexture(const std::string& in_path);

	// load shader
	TShader LoadShader(const std::string& in_path);

	// create render texture
	TRenderTexture CreateRenderTexture(const std::string& in_name,const u16& in_width,const u16& in_height,const texture::FORMAT& in_format);

	// get render texture
	TRenderTexture GetRenderTexture(const std::string& in_name);

	// create depth buffer
	TDepthBuffer CreateDepthBuffer(const std::string& in_key,const u16& in_width,const u16&in_height,const depth_buffer::FORMAT& in_format);

	// get Depth buffer
	TDepthBuffer GetDepthBuffer(const std::string& in_key);

protected:
	// constructor
	BaseDeviceHolder(void);

	// destructor
	virtual ~BaseDeviceHolder(void);

	TTextureLoader texture_loader_;
	TShaderLoader shader_loader_;
	TRenderTextureFactory render_texture_factory_;
	TDepthBufferFactory depth_buffer_factory_;

private:
	static const u32 DEFAULT_CLEAR_TARGET;
	static const float4 DEFAULT_CLEAR_COLOR;
	static const f32 DEFAULT_CLEAR_Z;
	static const u32 DEFAULT_CLEAR_STENCIL;

	virtual bool BeginDraw_(void) = 0;
	virtual bool EndDraw_(void) = 0;
	virtual bool Clear_(const u32& in_count,const float4* in_rects,const u32& in_target,const float4& in_color,const f32& in_z,const u32& in_stencil) = 0;
	virtual bool SetRenderTarget_(const u32& in_index,TRenderTexture in_render_texture) = 0;
	virtual bool SetDepthBuffer_(TDepthBuffer in_depth_buffer) = 0;
};

} // namespace device_holder
} // namespace base
} // namespace graphic

#endif // _BASE_DEVICE_HOLDER_H_

//---------------------------------- EOF --------------------------------------
