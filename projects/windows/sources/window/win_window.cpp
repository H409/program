//*****************************************************************************
//
// windows window
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "win_window.h"

namespace windows
{
namespace window
{
//=============================================================================
// constant definition
//=============================================================================
const s8* WinWindow::DEFAULT_CLASS_NAME = "default class name";
const s8* WinWindow::DEFAULT_CAPTION_NAME = "Hello world";

//=============================================================================
// static variable definition
//=============================================================================
std::unordered_map<HWND,WinWindow*> WinWindow::instances_;

//=============================================================================
// constructor
//=============================================================================
WinWindow::WinWindow(void)
	:hwnd_(NULL)
	,wndclassex_()
	,is_loop_(false)
{
}

//=============================================================================
// constructor
//=============================================================================
WinWindow::WinWindow(const u16& in_width,const u16& in_height)
	:WinWindow(DEFAULT_CAPTION_NAME,in_width,in_height)
{
}

//=============================================================================
// constructor
//=============================================================================
WinWindow::WinWindow(const std::string& in_caption_name,const u16& in_width,const u16& in_height)
	:WinWindow(in_caption_name.c_str(),DEFAULT_CLASS_NAME,in_width,in_height)
{

}

//=============================================================================
// constructor
//=============================================================================
WinWindow::WinWindow(const std::string& in_caption_name,const std::string& in_class_name,const u16& in_width,const u16& in_height)
	:WinWindow()
{
	std::thread thread([=]()
	{
		is_loop_ = true;
		WNDCLASSEX wndclassex =
		{
			sizeof(WNDCLASSEX),				// 構造体のサイズ
			CS_CLASSDC,						// スタイル
			WindowProcedure_,				// プロシージャの関数ポインタ
			0,								// 
			0,								// 
			NULL,							// インスタンス
			NULL,							// アイコン
			LoadCursor(NULL,IDC_ARROW),		// マウスカーソル
			(HBRUSH)(COLOR_WINDOW + 1),		// 背景色
			NULL,							// メニュー
			in_class_name.c_str(),			// ウィンドウのクラス名
			NULL							// アイコン
		};

		wndclassex_ = wndclassex;

		// ウィンドウクラスの登録
		RegisterClassEx(&wndclassex_);

		hwnd_ = CreateWindowEx(0,
			wndclassex_.lpszClassName,
			in_caption_name.c_str(),
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZE | WS_MINIMIZEBOX | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			in_width + GetSystemMetrics(SM_CXDLGFRAME) * 2,
			in_height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
			NULL,
			NULL,
			NULL,
			NULL);

		auto it = instances_.find(hwnd_);
		DEBUG_ASSERT_MESSAGE(it == instances_.end(),"exist this window handle");
		instances_.insert(std::make_pair(hwnd_,this));

		// ウインドウの表示
		ShowWindow(hwnd_,SW_SHOW);

		// ウィンドウの更新開始
		UpdateWindow(hwnd_);

		condition_variable_.notify_one();

		Update();

		// ウィンドウクラスの登録破棄
		UnregisterClass(wndclassex_.lpszClassName,wndclassex_.hInstance);

		for(auto callback : callbacks_)
		{
			callback();
		}

		condition_variable_.notify_one();
	});

	thread.detach();

	std::unique_lock<std::mutex> lock(mutex_);
	condition_variable_.wait(lock);

}

//=============================================================================
// destructor
//=============================================================================
WinWindow::~WinWindow(void)
{
	if(is_loop_)
	{
		{
			std::lock_guard <std::mutex> lock_gurad(mutex_);
			is_loop_ = false;
		}
		std::unique_lock<std::mutex> lock(mutex_);
		condition_variable_.wait(lock);
	}

	//callbacks_.clear();

	//instances_.erase(hwnd_);

}

//=============================================================================
// update
//=============================================================================
void WinWindow::Update(void)
{
	MSG msg;

	while(is_loop_)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		auto start_time = std::chrono::system_clock::now();

		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE) == TRUE)
		{
			// PostQuitMessage()が呼ばれたらループ終了
			if(msg.message == WM_QUIT)
			{
				is_loop_ = false;
				return;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		// sleep
		std::this_thread::sleep_until(start_time + std::chrono::milliseconds(1000 / 60));
	}
}

//=============================================================================
// set size
//=============================================================================
bool WinWindow::SetSize(const u16& in_width,const u16& in_height)
{
	DEBUG_TRACE("TODO : SetWindowSize");
	return true;
}

//=============================================================================
// set callback
//=============================================================================
void WinWindow::SetCallback(std::function<void(void)> in_callback)
{
	callbacks_.push_back(in_callback);
}

//=============================================================================
// procedure
//=============================================================================
LRESULT CALLBACK WinWindow::Procedure_(HWND in_hwnd,UINT in_message,WPARAM in_wparam,LPARAM in_lparam)
{
	return DefWindowProc(in_hwnd,in_message,in_wparam,in_lparam);
}

//=============================================================================
// window procedure
//=============================================================================
LRESULT CALLBACK WinWindow::WindowProcedure_(HWND in_hwnd,UINT in_message,WPARAM in_wparam,LPARAM in_lparam)
{
	switch(in_message)
	{
		case WM_CREATE:
		{
			break;
		}
		case WM_DESTROY:			// ウィンドウを破棄
		{
			PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN:			// キー入力
		{
			switch(in_wparam)
			{
				case VK_ESCAPE:			// エスケープキー
										// ウィンドウの破棄
					DestroyWindow(in_hwnd);
					break;
			}
			break;
		}
		case WM_DEVICECHANGE:
		{
			//PostMessage(in_hwnd,in_message,in_wparam,in_lparam);
			break;
		}
		default:
		{
			auto it = instances_.find(in_hwnd);
			if(it != instances_.end())
			{
				return it->second->Procedure_(in_hwnd,in_message,in_wparam,in_lparam);
			}
			break;
		}
	}

	return DefWindowProc(in_hwnd,in_message,in_wparam,in_lparam);
}

} // namespace window
} // namespace windows

//---------------------------------- EOF --------------------------------------
