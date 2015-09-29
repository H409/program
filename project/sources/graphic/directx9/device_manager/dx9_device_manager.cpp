//*****************************************************************************
//
// directx9 device manager
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_device_manager.h"
#include "../../windows/window/win_window.h"
#include "../device_holder/dx9_device_holder.h"
#include "../texture/dx9_texture.h"

namespace graphic
{
namespace directx9
{
namespace device_manager
{
//=============================================================================
// constructor
//=============================================================================
DX9DeviceManager::DX9DeviceManager(const u32& in_width,const u32& in_height)
	:BaseDeviceManager()
{
	auto window = std::make_shared<windows::window::WinWindow>(in_width,in_height);

	window_ = window;
	window->SetCallback([=](){is_stop_ = true;});

	auto hwnd = window->__hwnd();

	device_holder_ = std::make_shared<device_holder::DX9DeviceHolder>(hwnd,in_width,in_height);
}

//=============================================================================
// destructor
//=============================================================================
DX9DeviceManager::~DX9DeviceManager(void)
{
}

} // namespace device_manager
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
