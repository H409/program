//*****************************************************************************
//
// system
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_SYSTEM_H_
#define _BASE_SYSTEM_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic
{
class GraphicDevice;
} // namespace graphic

namespace window
{
class Window;
} // namespace window

//*****************************************************************************
// class definition
//*****************************************************************************
class BaseSystem : public utility::base::Base
{
public:
	enum class EVENT
	{
		NONE = -1,
		STOP,
		MAX,
	};

	using TGraphicDevice = std::shared_ptr<graphic::GraphicDevice>;
	using TWindow = std::shared_ptr<window::Window>;
	using TCallback = std::function<void(void)>;
	using TCallbacks = std::vector<TCallback>;

	// destructor
	virtual ~BaseSystem(void);

	// set callback
	void SetCallback(const EVENT& in_event,TCallback in_callback);

	// get graphic device
	TGraphicDevice GetGraphicDevice(void);

protected:
	// constructor
	BaseSystem(void);

	TGraphicDevice graphic_device_;
	TWindow window_;
	void Stop(void);

private:
	std::unordered_map<EVENT,TCallbacks> callbacks_;

};

#endif // _SYSTEM_H_

//---------------------------------- EOF --------------------------------------
