//*****************************************************************************
//
// depth buffer factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DEPTH_BUFFER_FACTORY_H_
#define _DEPTH_BUFFER_FACTORY_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/non_copyable.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic
{
namespace depth_buffer
{
enum class FORMAT;
class DepthBuffer;
} // namespace depth_buffer
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace depth_buffer
{
class DepthBufferFactory : public utility::base::NonCopyable
{
public:
	using TDepthBuffer = std::shared_ptr<DepthBuffer>;

	// destructor
	virtual ~DepthBufferFactory(void);

	// create
	TDepthBuffer Create(const std::string& in_key,const u16& in_width,const u16& in_height,const FORMAT& in_format);

	// get
	TDepthBuffer Get(const std::string& in_key);

protected:
	// constructor
	DepthBufferFactory(void);

private:
	std::unordered_map<std::string,TDepthBuffer> container_;

	virtual TDepthBuffer Create_(const u16& in_width,const u16& in_height,const FORMAT& in_format) = 0;
};

} // namespace depth_buffer
} // namespace graphic

#endif // _DEPTH_BUFFER_FACTORY_H_

//---------------------------------- EOF --------------------------------------
