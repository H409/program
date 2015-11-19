//*****************************************************************************
//
// title.cpp
//
// Author		: Masahiro Yamaguchi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "title.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "system/input_mouse.h"
#include "system/input_manager.h"
#include "../base/scene_manager.h"
#include "../tutorial/tutorial.h"

//=============================================================================
// constructor
//=============================================================================
Title::Title()
{

}

//=============================================================================
// destructor
//=============================================================================
Title::~Title()
{

}

//=============================================================================
// initialize
//=============================================================================
bool Title::Initialize(SceneManager* p_scene_manager)
{
	return 0;
}
//=============================================================================
// finalize
//=============================================================================
void Title::Finalize()
{

}

//=============================================================================
// update
//=============================================================================
void Title::Update()
{
	auto p_input_manager = GET_INPUT_MANAGER();

	//if (p_input_manager->GetTrigger(InputManager::Command::A, 0))
	if(GET_INPUT_MOUSE()->GetPress(InputMouse::MOUSE_KEY::LEFT))
	{
		SceneManager::Instance().set_p_next_scene(SceneManager::Instance().get_tutorial());
		SceneManager::Instance().set_scene_change_flag(true);
	}
}

//=============================================================================
// draw
//=============================================================================
void Title::Draw()
{
	auto graphic_device = GET_GRAPHIC_DEVICE();
	graphic_device->Clear(float4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
}
