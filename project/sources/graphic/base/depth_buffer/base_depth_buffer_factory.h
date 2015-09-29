//*****************************************************************************
//
// base depth buffer factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_DEPTH_BUFFER_FACTORY_H_
#define _BASE_DEPTH_BUFFER_FACTORY_H_

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
namespace depth_buffer
{
enum class FORMAT;
class BaseDepthBuffer;
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
namespace depth_buffer
{
class BaseDepthBufferFactory : public common::base::NonCopyable
{
public:
	using TBaseDepthBuffer = std::shared_ptr<BaseDepthBuffer>;

	// destructor
	virtual ~BaseDepthBufferFactory(void);

	// create
	TBaseDepthBuffer Create(const std::string& in_key,const u16& in_width,const u16& in_height,const FORMAT& in_format);

	// get
	TBaseDepthBuffer Get(const std::string& in_key);

protected:
	// constructor
	BaseDepthBufferFactory(void);

private:
	std::unordered_map<std::string,TBaseDepthBuffer> container_;

	virtual TBaseDepthBuffer Create_(const u16& in_width,const u16& in_height,const FORMAT& in_format) = 0;
};

} // namespace depth_buffer
} // namespace base
} // namespace graphic

#endif // _BASE_DEPTH_BUFFER_FACTORY_H_

//---------------------------------- EOF --------------------------------------
