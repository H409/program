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
#include "system/win_system.h"
#include "fade/fade.h"

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

	fade_ = std::make_shared<Fade>();

	//カレントシーンに設定する
//	p_current_scene_ = p_game_;
	p_current_scene_ = p_title_;
	p_current_scene_->Initialize(this);
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

	fade_->Update();

#ifndef _RELEASE
	if(GET_INPUT_KEYBOARD()->GetPress(DIK_LSHIFT))
	{
		if(GET_INPUT_KEYBOARD()->GetPress(DIK_1))
		{
			set_p_next_scene(get_title());
			set_scene_change_flag(true);
		}
		if(GET_INPUT_KEYBOARD()->GetPress(DIK_2))
		{
			set_p_next_scene(get_tutorial());
			set_scene_change_flag(true);
		}
		if(GET_INPUT_KEYBOARD()->GetPress(DIK_3))
		{
			set_p_next_scene(get_demo());
			set_scene_change_flag(true);
		}
		if(GET_INPUT_KEYBOARD()->GetPress(DIK_4))
		{
			set_p_next_scene(get_game());
			set_scene_change_flag(true);
		}
		if(GET_INPUT_KEYBOARD()->GetPress(DIK_5))
		{
			set_p_next_scene(get_result());
			set_scene_change_flag(true);
		}
	}
#endif

	//シーン切り替えフラグがONになっていたらシーン切り替え
	if (SceneManager::Instance().get_scene_change_flag())
	{
		if(!fade_->IsWork())
		{
			fade_->Start(30,Fade::TYPE::FADE_OUT,[&]() {
				p_current_scene_->Finalize();
				p_current_scene_ = p_next_scene_;
				p_current_scene_->Initialize(&Instance());
				fade_->Start(30,Fade::TYPE::FADE_IN);
			});
		}
		scene_change_flag_ = false;
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

	fade_->Draw();
}

//eof