//*****************************************************************************
//
// tutorial.cpp
//
// Author		: Masahiro Yamaguchi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "tutorial.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "system/input_mouse.h"
#include "system/input_manager.h"
#include "../base/scene_manager.h"
#include "../title/title.h"
#include "../game/game.h"

//=============================================================================
// constructor
//=============================================================================
Tutorial::Tutorial()
{

}

//=============================================================================
// destructor
//=============================================================================
Tutorial::~Tutorial()
{

}

//=============================================================================
// initialize
//=============================================================================
bool Tutorial::Initialize(SceneManager* p_scene_manager)
{
	return 0;
}
//=============================================================================
// finalize
//=============================================================================
void Tutorial::Finalize()
{

}

//=============================================================================
// update
//=============================================================================
void Tutorial::Update()
{
	auto p_input_manager = GET_INPUT_MANAGER();
	//if (p_input_manager->GetTrigger(InputManager::Command::A, 0))
	if(GET_INPUT_MOUSE()->GetPress(InputMouse::MOUSE_KEY::LEFT))
	{
		SceneManager::Instance().set_p_next_scene(SceneManager::Instance().get_game());
		SceneManager::Instance().set_scene_change_flag(true);
	}
}

//=============================================================================
// draw
//=============================================================================
void Tutorial::Draw()
{
	auto graphic_device = GET_GRAPHIC_DEVICE();
	graphic_device->Clear(float4(0.0f, 0.0f, 0.0f, 0.0f), 1.0f);
}
