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
#include "application/application.h"
#include "application_system/application_system.h"

// HACK
#include "graphic/directx9/device_manager/dx9_device_manager.h"

//=============================================================================
// エントリーポイント
//=============================================================================
int main(int argc,char* argv)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	bool is_loop = true;
	std::unique_ptr<Application> application(new Application(new ApplicationSystem()));
	auto device_manager = std::make_unique<graphic::directx9::device_manager::DX9DeviceManager>(800,600);

	// main loop
	while(is_loop)
	{
		// update appication
		application->Update();

		// stop device manager
		if(device_manager->__is_stop())
		{
			is_loop = false;
		}
		// stop application
		if(application->__is_stop())
		{
			is_loop = false;
		}

		device_manager->Draw();
	}

	return 0;
}

//---------------------------------- EOF --------------------------------------
