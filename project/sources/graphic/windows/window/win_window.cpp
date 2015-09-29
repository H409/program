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

namespace graphic
{
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
	:BaseWindow()
	,hwnd_(NULL)
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
			sizeof(WNDCLASSEX),				// �\���̂̃T�C�Y
			CS_CLASSDC,						// �X�^�C��
			WindowProcedure_,				// �v���V�[�W���̊֐��|�C���^
			0,								// 
			0,								// 
			NULL,							// �C���X�^���X
			NULL,							// �A�C�R��
			LoadCursor(NULL,IDC_ARROW),		// �}�E�X�J�[�\��
			(HBRUSH)(COLOR_WINDOW + 1),		// �w�i�F
			NULL,							// ���j���[
			in_class_name.c_str(),			// �E�B���h�E�̃N���X��
			NULL							// �A�C�R��
		};

		wndclassex_ = wndclassex;

		// �E�B���h�E�N���X�̓o�^
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
		DEBUG_ASSERT_MESSAGE(it == instances_.end(),"");
		instances_.insert(std::make_pair(hwnd_,this));

		// �E�C���h�E�̕\��
		ShowWindow(hwnd_,SW_SHOW);

		// �E�B���h�E�̍X�V�J�n
		UpdateWindow(hwnd_);

		condition_variable_.notify_one();

		Update();

		// �E�B���h�E�N���X�̓o�^�j��
		UnregisterClass(wndclassex_.lpszClassName,wndclassex_.hInstance);

		for(auto callback : callbacks_)
		{
			callback();
		}

		condition_variable_.notify_one();
	});
	//std::thread thread_(thread);

	//thread_id_ = thread.get_id();

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

		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE) == TRUE)
		{
			// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
			if(msg.message == WM_QUIT)
			{
				is_loop_ = false;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		//Sleep(static_cast<DWORD>(1000.0f / 60.0f));
	}
}

//=============================================================================
// set callback
//=============================================================================
void WinWindow::SetCallback(std::function<void(void)> callback)
{
	callbacks_.push_back(callback);
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
		case WM_DESTROY:			// �E�B���h�E��j��
		{
			PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN:			// �L�[����
		{
			switch(in_wparam)
			{
				case VK_ESCAPE:			// �G�X�P�[�v�L�[
										// �E�B���h�E�̔j��
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

//=============================================================================
// set size
//=============================================================================
bool WinWindow::SetSize_(const u16& in_width,const u16& in_height)
{
	return true;
}

} // namespace texture
} // namespace base
} // namespace graphic

//---------------------------------- EOF --------------------------------------
