//*****************************************************************************
//
// render texture factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _RENDER_TEXTURE_FACTORY_H_
#define _RENDER_TEXTURE_FACTORY_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/non_copyable.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic
{
namespace texture
{
enum class FORMAT;
class RenderTexture;
} // namespace texture
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace texture
{
class RenderTextureFactory : public utility::base::NonCopyable
{
public:
	using TRenderTexture = std::shared_ptr<RenderTexture>;
	using TFormat = FORMAT;

	// destructor
	virtual ~RenderTextureFactory(void) = default;

	// create
	TRenderTexture Create(const std::string& in_key,const u16& in_width,const u16& in_height,const TFormat& in_format);

	// get
	TRenderTexture Get(const std::string& in_ket);

protected:
	// constructor
	RenderTextureFactory(void) = default;

private:
	std::unordered_map<std::string,TRenderTexture> container_;

	virtual TRenderTexture Create_(const u16& in_width,const u16& in_height,const TFormat& in_format) = 0;
};

} // namespace texture
} // namespace graphic

#endif // _BASE_RENDER_TEXTURE_FACTORY_H_

//---------------------------------- EOF --------------------------------------
