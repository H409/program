//*****************************************************************************
//
// base depth buffer factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "base_depth_buffer_factory.h"

namespace graphic
{
namespace base
{
namespace depth_buffer
{
//*****************************************************************************
// using
//*****************************************************************************
using TBaseDepthBuffer = std::shared_ptr<BaseDepthBuffer>;

//=============================================================================
// constructor
//=============================================================================
BaseDepthBufferFactory::BaseDepthBufferFactory(void)
{
}

//=============================================================================
// destructor
//=============================================================================
BaseDepthBufferFactory::~BaseDepthBufferFactory(void)
{
}

//=============================================================================
// create
//=============================================================================
TBaseDepthBuffer BaseDepthBufferFactory::Create(const std::string & in_key,const u16 & in_width,const u16 & in_height,const FORMAT& in_format)
{
	auto depth_buffer = Get(in_key);

	if(depth_buffer == nullptr)
	{
		auto depth_buffer = Create_(in_width,in_height,in_format);

		container_.insert(std::make_pair(in_key,depth_buffer));
		return depth_buffer;
	}

	return depth_buffer;
}

//=============================================================================
// get
//=============================================================================
TBaseDepthBuffer BaseDepthBufferFactory::Get(const std::string & in_key)
{
	auto it = container_.find(in_key);

	if(it != container_.end())
	{
		return nullptr;
	}

	return it->second;
}

} // namespace depth_buffer
} // namespace base
} // namespace graphic

//---------------------------------- EOF --------------------------------------
