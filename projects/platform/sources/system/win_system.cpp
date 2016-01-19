//*****************************************************************************
//
// windows system
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "win_system.h"

// windows
#include "window/win_window.h"

// directx9
#include "dx9_device.h"

#include "input_keyboard.h"
#include "input_mouse.h"
#include "input_manager.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
//const float2 WinSystem::DEFAULT_DISPLAY_SIZE = float2(1280.0f,720.0f);
const float2 WinSystem::DEFAULT_DISPLAY_SIZE = float2(1920.0f,1080.0f);
const std::string WinSystem::DEFAULT_CAPTION_NAME = "";

//=============================================================================
// get instance
//=============================================================================
WinSystem* WinSystem::GetInstance(void)
{
	static WinSystem instance;
	return &instance;
}

WinSystem::TWindow WinSystem::GetWindow(void)
{
	return window_;
}

//=============================================================================
// get graphic device
//=============================================================================
WinSystem::TGraphicDevice WinSystem::GetGraphicDevice(void)
{
	return graphic_device_;
}

//=============================================================================
// get directx9 device
//=============================================================================
LPDIRECT3DDEVICE9 WinSystem::GetDirectx9Device(void)
{
	return graphic_device_->GetDevice();
}

//=============================================================================
// set callbacks
//=============================================================================
void WinSystem::SetCallbacks(EVENT in_event,const TCallbacks& in_callbacks)
{
	auto it = callbacks_.find(in_event);

	if(it == callbacks_.end())
	{
		callbacks_.insert(std::make_pair(in_event,in_callbacks));
	}
	else
	{
		for(auto callback : in_callbacks)
		{
			it->second.push_back(callback);
		}
	}
}

//=============================================================================
// get input_keyboard_
//=============================================================================
WinSystem::TInputKeyboard WinSystem::GetKeyboard(void)
{
	return input_keyboard_;
}

//=============================================================================
// get input_mouse_
//=============================================================================
WinSystem::TInputMouse WinSystem::GetMouse(void)
{
	return input_mouse_;
}

//=============================================================================
// get input_manager_
//=============================================================================
WinSystem::TInputManager WinSystem::GetInputManager(void)
{
	return input_manager_;
}
//=============================================================================
// constructor
//=============================================================================
WinSystem::WinSystem(void)
{
	auto window = std::make_shared<windows::window::WinWindow>((u16)DEFAULT_DISPLAY_SIZE._x,(u16)DEFAULT_DISPLAY_SIZE._y);

	auto hwnd_ = window->__hwnd();

	window_ = window;

	window->SetCallback([&](){Stop_();});

	graphic_device_ = std::make_shared<graphic::directx9::DX9Device>(hwnd_,(u16)DEFAULT_DISPLAY_SIZE._x,(u16)DEFAULT_DISPLAY_SIZE._y);
	//graphic_device_ = std::make_shared<graphic::directx9::DX9Device>(hwnd_,(u16)1920,(u16)1080);

	input_keyboard_ = std::make_shared<InputKeyboard>();

	input_keyboard_->Init(NULL, hwnd_);

	input_mouse_ = std::make_shared<InputMouse>();

	input_mouse_->Init(NULL, hwnd_);

	input_manager_ = std::make_shared<InputManager>();

	input_manager_->Initialize(hwnd_);
}

//=============================================================================
// destructor
//=============================================================================
WinSystem::~WinSystem(void)
{
	input_manager_->Finalize();
}

//=============================================================================
// stop
//=============================================================================
void WinSystem::Stop_(void)
{
	auto it = callbacks_.find(EVENT::STOP);

	if(it != callbacks_.end())
	{
		for(auto callback : it->second)
		{
			callback();
		}
	}
}

//---------------------------------- EOF --------------------------------------
