//*****************************************************************************
//
// デバッグマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once

#ifndef _DEBUG_MANAGER_H_
#define _DEBUG_MANAGER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ApplicationManager;
class DebugConsole;
class Thread;
class DebugLog;

//*****************************************************************************
// class definition
//*****************************************************************************
class DebugManager : public Basic
{
public:
	// インスタンスの取得
	static DebugManager& instance(void){return instance_;}

	// デバッグスレッドを立てる
	void Run(ApplicationManager* in_application_manger);

	// デバッグスレッドを終了させる
	void Stop(void);

	// 更新メッセージ
	void UpdateMessage(void){is_update_ = true;}

	// デバッグコンソールの取得
	DebugConsole* debug_console(void)const{return debug_console_;}

	// 
	DebugLog* debug_log(void)const{return debug_log_;}
private:
	// constructor
	DebugManager(void);

	// destructor
	virtual ~DebugManager(void);

	// initializer
	bool Initialize(void);

	// Uninitializer
	void Uninitialize(void);

	// 更新
	void Update(void);
	// 描画
	void Draw(void);

	static DebugManager instance_;

	volatile bool is_run_;
	volatile bool is_update_;
	volatile bool is_live_;

	DebugConsole* debug_console_;
	DebugLog* debug_log_;
	Thread* thread_;
	ApplicationManager* application_manager_;
	static void DebugThread(void);
};

#endif // _DEBUG_MANAGER_H_

//---------------------------------- EOF --------------------------------------
