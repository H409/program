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
#include "system/input_manager.h"
#include "system/input_keyboard.h"
#include "system/input_mouse.h"
#include "scene/base/scene_manager.h"
#include "develop_tool/develop_tool.h"

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
	auto fps = 0;
	win_system->SetCallbacks(WinSystem::EVENT::STOP,{ [&is_loop] {is_loop = false;} });

	auto sum_time = 0;
	u32 frame_count = 0;
	auto st = timeGetTime();

	while(is_loop)
	{
		auto start_time = std::chrono::system_clock::now();
		frame_count++;
		sum_time = timeGetTime() - st;

		if(sum_time >= 500)
		{
			auto now = timeGetTime();
			fps = frame_count * 1000 / sum_time;
			sum_time = 0;
			frame_count = 0;
			st = now;
		}

		DEVELOP_DISPLAY("FPS : %d\n",fps);

		GET_INPUT_MANAGER()->Update();

		DEVELOP_TOOL_UPDATE();

		scene_manager.Update();

		graphic_device->BeginRendering();

		scene_manager.Draw();

		DEVELOP_TOOL_DRAW();
		graphic_device->EndRendering();

		std::this_thread::sleep_until(start_time + std::chrono::milliseconds(16));
	}

	return 0;
}

//---------------------------------- EOF --------------------------------------
