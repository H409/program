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
	auto sprite_logo = std::make_shared<mesh::Sprite>(float2(600, 300));
	logo_ = std::make_shared<MeshObject>(sprite_logo);
	sprite_logo->SetAnchorPoint(float2(0.0f, 0.0f));
	sprite_logo->Apply();
	logo_->SetPosition(350.0f, 150.0f, 0.0f);
	logo_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/title_logo.png"));

	//ボタン
	auto sprite_button = std::make_shared<mesh::Sprite>(float2(400, 200));
	button_ = std::make_shared<MeshObject>(sprite_button);
	sprite_button->SetAnchorPoint(float2(0.0f, 0.0f));
	sprite_logo->Apply();
	button_->SetPosition(400.0f, 500.0f, 0.0f);
	button_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/Push.png"));

	//2D用カメラ設定
	observer_2d_ = std::make_shared<Observer2D>(window->GetWidth(), window->GetHeight());

	//BGM
	Sound::Instance().PlaySound(SOUND_LABEL_BGM000);
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
	Sound::Instance().StopSound();
}

//=============================================================================
// update
//=============================================================================
void Title::Update()
{
	auto p_input_manager = GET_INPUT_MANAGER();

	//効果音デバッグ
	if (GET_INPUT_KEYBOARD()->GetTrigger(DIK_O))
	{
		{
			Sound::Instance().PlaySeSound(SOUND_LABEL_SE_SHOT, 0);
		}
	}

	//if (p_input_manager->GetTrigger(InputManager::Command::A, 0))
	if(GET_INPUT_MOUSE()->GetPress(InputMouse::MOUSE_KEY::LEFT))
	{
		//効果音再生
		Sound::Instance().PlaySeSound(SOUND_LABEL_SE_YES, 0);

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

	basic_vs->SetValue("_world_matrix", (f32*)&logo_->GetMatrix(), 16);
	basic_vs->SetValue("_color", (f32*)&color, 4);

	basic_ps->SetTexture("_texture_sampler", logo_->GetTexture(0)->GetTexture());
	//ロゴ
	logo_->Draw();
	
	basic_vs->SetValue("_world_matrix", (f32*)&button_->GetMatrix(), 16);
	basic_vs->SetValue("_color", (f32*)&color, 4);

	basic_ps->SetTexture("_texture_sampler", button_->GetTexture(0)->GetTexture());
	//ボタン
	button_->Draw();

}
