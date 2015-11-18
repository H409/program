//*****************************************************************************
//
// main
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "main.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "math/math.h"
#include "system/input_keyboard.h"
#include "system/input_mouse.h"
#include "scene/base/scene_manager.h"

//=============================================================================
// エントリーポイント
//=============================================================================
int main(int argc,char* argv)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	auto win_system = WinSystem::GetInstance();
	auto graphic_device = GET_GRAPHIC_DEVICE();
	bool is_loop = true;
	auto& scene_manager = SceneManager::Instance();

	win_system->SetCallbacks(WinSystem::EVENT::STOP,{ [&is_loop] {is_loop = false;} });

	while(is_loop)
	{
		auto start_time = std::chrono::system_clock::now();

		GET_INPUT_KEYBOARD()->Update();
		GET_INPUT_MOUSE()->Update();

		scene_manager.Update();

		graphic_device->BeginRendering();

		scene_manager.Draw();

		graphic_device->EndRendering();


		std::this_thread::sleep_until(start_time + std::chrono::milliseconds(1000 / 60));
	}

	return 0;
}

//---------------------------------- EOF --------------------------------------
