//*****************************************************************************
//
// windows window
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _WINDOWS_WINDOW_H_
#define _WINDOWS_WINDOW_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/base/window/base_window.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace windows
{
namespace window
{
class WinWindow : public graphic::base::window::BaseWindow
{
public:
	// constructor
	WinWindow(const u16& in_width,const u16& in_height);
	WinWindow(const std::string& in_caption_name,const u16& in_width,const u16& in_height);
	WinWindow(const std::string& in_caption_name,const std::string& in_class_name,const u16& in_width,const u16& in_height);

	// destructor
	virtual ~WinWindow(void);

	// HACK update
	void Update(void);

	// set callback
	void SetCallback(std::function<void(void)> callback);

	// accessor
	const HWND& __hwnd(void)const{ return hwnd_; }

private:
	static const s8* DEFAULT_CLASS_NAME;
	static const s8* DEFAULT_CAPTION_NAME;

	HWND hwnd_;
	WNDCLASSEX wndclassex_;
	bool is_loop_;
	std::vector<std::function<void(void)>> callbacks_;
	std::mutex mutex_;
	std::condition_variable condition_variable_;

	std::thread::id thread_id_;

	static std::unordered_map<HWND,WinWindow*> instances_;

	WinWindow(void);
	bool SetSize_(const u16& in_width,const u16& in_height)override;
	virtual LRESULT CALLBACK Procedure_(HWND in_hwnd,UINT in_message,WPARAM in_wparam,LPARAM in_lparam);

	static LRESULT CALLBACK WindowProcedure_(HWND in_hwnd,UINT in_message,WPARAM in_wparam,LPARAM in_lparam);
};

} // namespace window
} // namespace windows
} // namespace graphic

#endif // _BASE_WINDOW_H_

//---------------------------------- EOF --------------------------------------
