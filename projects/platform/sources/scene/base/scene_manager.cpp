//*****************************************************************************
//
// scene_manager.cpp
//
// Author		: Masahiro Yamaguchi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "scene_base.h"
#include "scene_factory.h"
#include "scene_manager.h"
#include "../title/title.h"
#include "../tutorial/tutorial.h"
#include "../demo/demo.h"
#include "../game/game.h"
#include "../result/result.h"

//=============================================================================
// constructor
//=============================================================================
SceneManager::SceneManager()
	:
	p_current_scene_(nullptr),
	p_next_scene_(nullptr),
	p_title_(nullptr),
	p_tutorial_(nullptr),
	p_demo_(nullptr),
	p_game_(nullptr),
	p_result_(nullptr),
	scene_change_flag_(false)
{
	//各シーン生成
	p_title_ = std::make_shared<Title>();
	p_demo_ = std::make_shared<Demo>();
	p_tutorial_ = std::make_shared<Tutorial>();
	p_game_ = std::make_shared<Game>();
	p_result_ = std::make_shared<Result>();

	//カレントシーンに設定する
	p_current_scene_ = p_title_;
}

//=============================================================================
// destructor
//=============================================================================
SceneManager::~SceneManager()
{

}

//=============================================================================
// Update
//=============================================================================
void SceneManager::Update()
{
	//TODO:管理の仕方
	//各シーンでシーンを設定する
	

	//現在のシーンを更新
	if (p_current_scene_ != nullptr)
	{
		p_current_scene_->Update();
	}
}

//=============================================================================
// Draw
//=============================================================================
void SceneManager::Draw()
{
	//現在のシーンを更新
	if (p_current_scene_ != nullptr)
	{
		p_current_scene_->Draw();
	}
}

//eof