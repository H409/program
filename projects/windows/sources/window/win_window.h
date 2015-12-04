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
//#include "window/window.h"
#include <Windows.h>

//*****************************************************************************
// class definition
//*****************************************************************************
namespace windows
{
namespace window
{
class WinWindow// : public ::window::Window
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

	// set size
	bool SetSize(const u16& in_width,const u16& in_height);

	// set callback
	void SetCallback(std::function<void(void)> in_callback);

	// accessor
	const HWND& __hwnd(void)const{ return hwnd_; }

	//
	u16 GetWidth(void)const;

	u16 GetHeight(void)const;

private:
	static const s8* DEFAULT_CLASS_NAME;
	static const s8* DEFAULT_CAPTION_NAME;

	HWND hwnd_;
	WNDCLASSEX wndclassex_;
	bool is_loop_;
	std::vector<std::function<void(void)>> callbacks_;
	std::mutex mutex_;
	std::condition_variable condition_variable_;
	u16 width_;
	u16 height_;
	std::thread::id thread_id_;

	static std::unordered_map<HWND,WinWindow*> instances_;

	WinWindow(void);
	virtual LRESULT CALLBACK Procedure_(HWND in_hwnd,UINT in_message,WPARAM in_wparam,LPARAM in_lparam);

	static LRESULT CALLBACK WindowProcedure_(HWND in_hwnd,UINT in_message,WPARAM in_wparam,LPARAM in_lparam);
};

} // namespace window
} // namespace windows

#endif // _WINDOW_H_

//---------------------------------- EOF --------------------------------------
