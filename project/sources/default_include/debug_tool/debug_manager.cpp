//*****************************************************************************
//
// debug manager
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
// debug
#include "debug_manager.h"
#include "debug_console.h"
#include "debug_log.h"

// basic
#include "application_manager.h"

// common
#include "thread/thread.h"
#include "common.h"

//*****************************************************************************
// global variable
//*****************************************************************************
DebugManager DebugManager::instance_;

//=============================================================================
// constructor
//=============================================================================
DebugManager::DebugManager(void)
{
#ifndef _RELEASE
	application_manager_ = nullptr;
	debug_console_ = new DebugConsole();
	debug_log_ = new DebugLog();
	thread_ = new Thread();
#endif
}

//=============================================================================
// destructor
//=============================================================================
DebugManager::~DebugManager(void)
{
#ifndef _RELEASE
	SafeRelease(thread_);
	SafeRelease(debug_console_);
	SafeRelease(debug_log_);
#endif
}

//=============================================================================
// initialize
//=============================================================================
bool DebugManager::Initialize(void)
{
#ifndef _RELEASE
	SafeInitialize(debug_console_);
	SafeInitialize(debug_log_);
	SafeInitialize(thread_);

	is_run_ = true;
	is_update_ = true;
	is_live_ = true;
#endif
	return true;
}

//=============================================================================
// 更新
//=============================================================================
void DebugManager::Update(void)
{
#ifndef _RELEASE
#endif
}

//=============================================================================
// 描画
//=============================================================================
void DebugManager::Draw(void)
{
#ifndef _RELEASE
	// デバッグコンソールの描画
	debug_console_->Draw();
#endif
}

//=============================================================================
// 終了
//=============================================================================
void DebugManager::Uninitialize(void)
{
#ifndef _RELEASE
	SafeRelease(debug_console_);
	SafeRelease(debug_log_);
	is_live_ = false;
#endif
}


//=============================================================================
// スレッドの開始
//=============================================================================
void DebugManager::Run(ApplicationManager* in_application_manger)
{
#ifndef _RELEASE
	instance_.Initialize();
	instance_.application_manager_ = in_application_manger;
	instance_.thread_->Start(DebugThread,nullptr);
#endif
}

//=============================================================================
// スレッドの終了
//=============================================================================
void DebugManager::Stop(void)
{
#ifndef _RELEASE
	is_run_ = false;

	SafeRelease(thread_);

	Uninitialize();
#endif
}

//=============================================================================
// スレッドの開始
//=============================================================================
void DebugManager::DebugThread(void)
{
#ifndef _RELEASE
	while(instance_.is_run_)
	{
		if(instance_.is_update_)
		{
			instance_.Update();
			instance_.Draw();
			instance_.is_update_ = false;
		}
	}
#endif
}

//-----------------------------------EOF---------------------------------------
