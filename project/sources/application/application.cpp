//*****************************************************************************
//
// applicaton
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "application.h"
#include "application_system/application_system.h"
#include "scene/scene.h"

//=============================================================================
// constructor
//=============================================================================
Application::Application(ApplicationSystem* application_system)
	:application_system_(UApplicationSystem(application_system))
	,current_scene_(nullptr)
	,is_stop_(false)
{
	is_stop_ = false;

	current_scene_ = UScene(new Scene(Scene::TYPE_LOGO));
}

//=============================================================================
// destructor
//=============================================================================
Application::~Application(void)
{
}

//=============================================================================
// update
//=============================================================================
void Application::Update(void)
{
	// update application system
	application_system_->Update();

	// update scene
	current_scene_->Update();

	// draw scene
	current_scene_->Draw();
}

//---------------------------------- EOF --------------------------------------
