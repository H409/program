//*****************************************************************************
//
// graphic
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace device_manager
{
class BaseDeviceManager;
} // namespace device_manager
} // namespace base
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
class Graphic : public common::base::Base
{
public:
	// constructor
	Graphic(void);

	// destructor
	virtual ~Graphic(void);

protected:

private:
	std::shared_ptr<base::device_manager::BaseDeviceManager> device_manager_;

};

} // namespace graphic

#endif // _GRAPHIC_H_

//---------------------------------- EOF --------------------------------------
