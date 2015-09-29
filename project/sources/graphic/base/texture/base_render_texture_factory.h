//*****************************************************************************
//
// base render texture factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_RENDER_TEXTURE_FACTORY_H_
#define _BASE_RENDER_TEXTURE_FACTORY_H_

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
class BaseRenderTexture;
class BaseRenderTextureFactory;
} // namespace texture
} // namespace base
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace texture
{
class BaseRenderTextureFactory : public common::base::NonCopyable
{
public:
	using TRenderTexture = std::shared_ptr<BaseRenderTexture>;

	// destructor
	virtual ~BaseRenderTextureFactory(void);

	// create
	TRenderTexture Create(const std::string& in_key,const u16& in_width,const u16& in_height,const FORMAT& in_format);

	// get
	TRenderTexture Get(const std::string& in_ket);

protected:
	// constructor
	BaseRenderTextureFactory(void);

private:
	std::unordered_map<std::string,TRenderTexture> container_;

	virtual TRenderTexture Create_(const u16& in_width,const u16& in_height,const FORMAT& in_format) = 0;
};

} // namespace texture
} // namespace base
} // namespace graphic

#endif // _BASE_RENDER_TEXTURE_FACTORY_H_

//---------------------------------- EOF --------------------------------------
