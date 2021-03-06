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
#include "system/xi_pad.h"
#include "../base/scene_manager.h"
#include "../tutorial/tutorial.h"
#include "../game/game.h"
#include "system/input_keyboard.h"
#include "shader/dx9_vertex_shader.h"
#include "shader/dx9_pixel_shader.h"
#include "texture/dx9_texture.h"
#include "mesh/sprite.h"
#include "observer/observer_2d.h"
#include "observer/follower_observer.h"
#include "mesh/sprite_3d.h"
#include "object/mesh_object.h"
#include "object/object.h"
#include "object/mesh_object.h"
#include "math/math.h"
#include "sound/sound.h"

//=============================================================================
// constructor
//=============================================================================
Title::Title()
{
	//ウィンドウ
	auto window = GET_WINDOW();

	//とりあえず背景
	auto sprite = std::make_shared<mesh::Sprite>(float2(window->GetWidth(), window->GetHeight()));

	background_ = std::make_shared<MeshObject>(sprite);
	sprite->SetAnchorPoint(float2(0.0f, 0.0f));
	sprite->Apply();
	background_->SetPosition(0.0f, 0.0f, 0.0f);
	background_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/title_background.png"));
	
	//ロゴ
	auto sprite_logo = std::make_shared<mesh::Sprite>(float2(800, 400));
	logo_ = std::make_shared<MeshObject>(sprite_logo);
	sprite_logo->SetAnchorPoint(float2(0.0f, 0.0f));
	sprite_logo->Apply();
	logo_->SetPosition(window->GetWidth()/2-400.0f, window->GetHeight()/2-250.0f, 0.0f);
	logo_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/title_logo.png"));

	//ボタン
	auto sprite_button = std::make_shared<mesh::Sprite>(float2(400, 200));
	button_ = std::make_shared<MeshObject>(sprite_button);
	sprite_button->SetAnchorPoint(float2(0.0f, 0.0f));
	sprite_logo->Apply();
	button_->SetPosition(window->GetWidth() / 2 - 210.0f, window->GetHeight() - 250.0f, 0.0f);
	button_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/Start.png"));

	//ボタン背景
	auto sprite_button_interface_ = std::make_shared<mesh::Sprite>(float2(300, 100));
	button_interface_ = std::make_shared<MeshObject>(sprite_button_interface_);
	sprite_button_interface_->SetAnchorPoint(float2(0.0f, 0.0f));
	sprite_button_interface_->Apply();
	button_interface_->SetPosition(window->GetWidth() / 2 - 150.0f, window->GetHeight() - 200.0f, 0.0f);
	button_interface_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/window_256x512.png"));

	//パーティクル
	for (u32 i = 0; i < PARTICUL_MAX; ++i)
	{
		auto sprite_particul = std::make_shared<mesh::Sprite>(float2(30,30));
		particul_[i].particul_ = std::make_shared<MeshObject>(sprite_particul);
		sprite->SetAnchorPoint(float2(0.0f, 0.0f));
		particul_[i].particul_->SetPosition(f32((rand() % window->GetWidth())), -30.0f, 0.0f);
		particul_[i].particul_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/petal.png"));
		particul_[i].particul_angle_ = 0.0f;
		particul_[i].start_cnt_ = i * 10;
		particul_[i].start_flag_ = false;
	}

	//2D用カメラ設定
	observer_2d_ = std::make_shared<Observer2D>(window->GetWidth(), window->GetHeight());

	//BGM
	Sound::Instance().PlaySound(SOUND_LABEL_BGM000);

	draw_cnt_ = 0;
	use_flag_ = false;
	particul_cnt_ = 0;
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
	draw_cnt_ = 0;
	use_flag_ = false;

	Sound::Instance().StopSound();
}

//=============================================================================
// update
//=============================================================================
void Title::Update()
{
	auto p_input_manager = GET_INPUT_MANAGER();
	auto window = GET_WINDOW();

	//効果音デバッグ
	if (GET_INPUT_KEYBOARD()->GetTrigger(DIK_O))
	{
		{
			Sound::Instance().PlaySeSound(SOUND_LABEL_SE_PMOVE, 0);
		}
	}

	//if (p_input_manager->GetTrigger(InputManager::Command::A, 0))
	if(GET_INPUT_MOUSE()->GetPress(InputMouse::MOUSE_KEY::LEFT))
	{
		//効果音再生
		Sound::Instance().PlaySeSound(SOUND_LABEL_SE_YES, 0);

		SceneManager::Instance().set_p_next_scene(SceneManager::Instance().get_game());
		SceneManager::Instance().set_scene_change_flag(true);
	}

	//パーティクル
	for (u32 i = 0; i < PARTICUL_MAX; ++i)
	{
		
		if (particul_cnt_ == particul_[i].start_cnt_)
		{
			particul_[i].start_flag_ = true;

		}	
		if (particul_[i].start_flag_)
		{
			auto position = particul_[i].particul_->GetPosition();
			particul_[i].particul_angle_ -= D3DX_PI*0.01f;
			position._x -= sinf(particul_[i].particul_angle_);
			position._y += 0.5f;

			auto rotate = particul_[i].particul_->GetRotation();
			rotate._z = 1.2f;

			
			if (particul_[i].particul_angle_ < -D3DX_PI)
			{
				particul_[i].particul_angle_ += 2 * D3DX_PI;
			}
			else if (particul_[i].particul_angle_ > D3DX_PI)
			{
				particul_[i].particul_angle_ -= 2 * D3DX_PI;
			}
			
			if (position._y > window->GetHeight())
			{
				position._x = (rand() % window->GetWidth());
				position._y = -10.0f;
			}
			
			particul_[i].particul_->SetPosition(position._x, position._y, position._z);
			particul_[i].particul_->SetRotation(rotate);
		}
	}
	particul_cnt_++;

	for (int i = 0; i < PLAYER_SUM; i++)
	{
		if (GET_INPUT_XPAD(i)->GetPress(XIPad::KEY::A) || GET_INPUT_XPAD(i)->GetPress(XIPad::KEY::B))
		{
			//効果音再生
			Sound::Instance().PlaySeSound(SOUND_LABEL_SE_YES, 0);

			SceneManager::Instance().set_p_next_scene(SceneManager::Instance().get_game());
			SceneManager::Instance().set_scene_change_flag(true);
		}
	}
}

//=============================================================================
// draw
//=============================================================================
void Title::Draw()
{
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto gb_vs = graphic_device->LoadVertexShader("resources/shader/graphics_buffer.vsc");
	auto gb_ps = graphic_device->LoadPixelShader("resources/shader/graphics_buffer.psc");
	auto d_vs = graphic_device->LoadVertexShader("resources/shader/deferred.vsc");
	auto d_ps = graphic_device->LoadPixelShader("resources/shader/deferred.psc");

	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");

	//画面クリア
	graphic_device->Clear(float4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);

	//デバッグワイヤーフレーム
//	graphic_device->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	float4 color(1.0f, 1.0f, 1.0f, 1.0f);
	//シェーダ設定
	graphic_device->SetVertexShader(basic_vs);
	graphic_device->SetPixelShader(basic_ps);

	basic_vs->SetValue("_view_matrix", (f32*)&observer_2d_->GetViewMatrix(), 16);
	basic_vs->SetValue("_projection_matrix", (f32*)&observer_2d_->GetProjectionMatrix(), 16);
	basic_vs->SetValue("_world_matrix", (f32*)&background_->GetMatrix(), 16);
	basic_vs->SetValue("_color", (f32*)&color,4);

	basic_ps->SetTexture("_texture_sampler", background_->GetTexture(0)->GetTexture());
	//背景
	background_->Draw();

	//パーティクル
	for (u32 i = 0; i < PARTICUL_MAX; ++i)
	{
		basic_vs->SetValue("_world_matrix", (f32*)&particul_[i].particul_->GetMatrix(), 16);
		basic_vs->SetValue("_color", (f32*)&color, 4);

		basic_ps->SetTexture("_texture_sampler", particul_[i].particul_->GetTexture(0)->GetTexture());
		//ロゴ
		particul_[i].particul_->Draw();
	}
	basic_vs->SetValue("_world_matrix", (f32*)&logo_->GetMatrix(), 16);
	basic_vs->SetValue("_color", (f32*)&color, 4);

	basic_ps->SetTexture("_texture_sampler", logo_->GetTexture(0)->GetTexture());
	//ロゴ
	logo_->Draw();


	draw_cnt_++;
	if (draw_cnt_ > 100)
	{
		use_flag_ = true;
	}
	if (draw_cnt_ > 200)
	{
		draw_cnt_ = 0;
		use_flag_ = false;
	}
	if (use_flag_)
	{
		//ボタン背景
		basic_vs->SetValue("_world_matrix", (f32*)&button_interface_->GetMatrix(), 16);
		basic_vs->SetValue("_color", (f32*)&color, 4);

		basic_ps->SetTexture("_texture_sampler", button_interface_->GetTexture(0)->GetTexture());
		//ボタン背景
		button_interface_->Draw();

		basic_vs->SetValue("_world_matrix", (f32*)&button_->GetMatrix(), 16);
		basic_vs->SetValue("_color", (f32*)&color, 4);

		basic_ps->SetTexture("_texture_sampler", button_->GetTexture(0)->GetTexture());
		//ボタン
		button_->Draw();
	}

}
