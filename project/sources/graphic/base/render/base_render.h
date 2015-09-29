//*****************************************************************************
//
// base render
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_RENDER_H_
#define _BASE_RENDER_H_

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
namespace device_holder
{
class BaseDeviceHolder;
} // namespace device_holder
} // namespace base
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace render
{
class BaseRender : public common::base::NonCopyable
{
public:
	using TDeviceHolder = std::shared_ptr<device_holder::BaseDeviceHolder>;

	// constructor
	BaseRender(void);

	// destructor
	virtual ~BaseRender(void);

	// draw
	bool Draw(TDeviceHolder in_device_holder)const;

	// render target
protected:

private:
	float4 clear_color_;

	float4x4 projection_matrix_;
	float4x4 view_matrix_;

	//ObjectHolder* object_holder_;
};

} // namespace render
} // namespace base
} // namespace graphic

#endif // _BASE_RENDER_H_

//---------------------------------- EOF --------------------------------------
