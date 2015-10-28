//*****************************************************************************
//
// windows system
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _WIN_SYSTEM_H_
#define _WIN_SYSTEM_H_

//*****************************************************************************
// include
//*****************************************************************************

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic {
namespace directx9 {
class DX9Device;
} // namespace directx9
} // namespace graphic

namespace windows {
namespace window {
class WinWindow;
} // namespace window
} // namespace windows

//*****************************************************************************
// class definition
//*****************************************************************************
class WinSystem// : public BaseSystem
{
public:
	using TWindow = std::shared_ptr<windows::window::WinWindow>;
	using TGraphicDevice = std::shared_ptr<graphic::directx9::DX9Device>;
	using TCallback = std::function<void(void)>;
	using TCallbacks = std::vector<TCallback>;
	enum class EVENT
	{
		STOP,
	};
	static WinSystem* GetInstance(void);

	// get graphic device
	TGraphicDevice GetGraphicDevice(void);

	// get directx9 device
	LPDIRECT3DDEVICE9 GetDirectx9Device(void);

	// set callback
	void SetCallbacks(EVENT in_event,const TCallbacks& in_callbacks);

protected:
	// constructor
	WinSystem(void);

	// destructor
	virtual ~WinSystem(void);
private:
	static const float2 DEFAULT_DISPLAY_SIZE;
	static const std::string DEFAULT_CAPTION_NAME;

	TWindow window_;
	TGraphicDevice graphic_device_;
	std::unordered_map<EVENT,TCallbacks> callbacks_;

	void Stop_(void);
};

#define GET_GRAPHIC_DEVICE() WinSystem::GetInstance()->GetGraphicDevice()
#define GET_DIRECTX9_DEVICE() WinSystem::GetInstance()->GetDirectx9Device()

#endif // _SYSTEM_H_

//---------------------------------- EOF --------------------------------------
