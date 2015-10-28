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
#include "depth_buffer_factory.h"

namespace graphic
{
namespace depth_buffer
{
//=============================================================================
// constructor
//=============================================================================
DepthBufferFactory::DepthBufferFactory(void)
{
}

//=============================================================================
// destructor
//=============================================================================
DepthBufferFactory::~DepthBufferFactory(void)
{
}

//=============================================================================
// create
//=============================================================================
DepthBufferFactory::TDepthBuffer DepthBufferFactory::Create(const std::string & in_key,const u16 & in_width,const u16 & in_height,const FORMAT& in_format)
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
DepthBufferFactory::TDepthBuffer DepthBufferFactory::Get(const std::string & in_key)
{
	auto it = container_.find(in_key);

	if(it != container_.end())
	{
		return nullptr;
	}

	return it->second;
}

} // namespace depth_buffer
} // namespace graphic

//---------------------------------- EOF --------------------------------------
