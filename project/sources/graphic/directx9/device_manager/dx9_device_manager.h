//*****************************************************************************
//
// directx9 device manager
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_DEVICE_MANAGER_H_
#define _DX9_DEVICE_MANAGER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/base/device_manager/base_device_manager.h"

namespace graphic
{
namespace directx9
{
namespace device_holder
{
class DX9DeviceHolder;
} // namespace device_holder
} // namespace directx9
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace device_manager
{
class DX9DeviceManager : public graphic::base::device_manager::BaseDeviceManager
{
public:
	// constructor
	DX9DeviceManager(const u32& in_width,const u32& in_height);

	// destructor
	virtual ~DX9DeviceManager(void);
private:
};

} // namespace device_manager
} // namespace directx9
} // namespace graphic

#endif // _DX9_DEVICE_MANAGER_H_

//---------------------------------- EOF --------------------------------------
