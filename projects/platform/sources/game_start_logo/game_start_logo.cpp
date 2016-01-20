//*****************************************************************************
//
// game_timer
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "game_start_logo.h"
#include "mesh/sprite.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "object/mesh_object.h"
#include "shader/dx9_vertex_shader.h"
#include "shader/dx9_pixel_shader.h"
//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 GameStartLogo::DEFAULT_TIME_MAX = (u32)(30 * 3);	//フレーム数*一分の秒数*分数
																//=============================================================================
																// constructor
																//=============================================================================
GameStartLogo::GameStartLogo(void)
{
	//タイマー背景の設定
	back_ground_size_._x = GET_DEFAULT_DISPLAY_SIZE()._x / 6.0f;
	back_ground_size_._y = GET_DEFAULT_DISPLAY_SIZE()._y / 6.0f;
	back_ground_pos_._x = GET_DEFAULT_DISPLAY_SIZE()._x * 0.5f - (back_ground_size_._x / 2);
	back_ground_pos_._y = GET_DEFAULT_DISPLAY_SIZE()._y * 0.5f - (back_ground_size_._y / 2);

	//タイマー数字表示の設定
	num_size_._x = back_ground_size_._x / 3.0f;
	num_size_._y = back_ground_size_._y*0.8f;
	for (int i = 0; i < TIMER_DIGIT; i++)
	{
		num_pos_._x = (back_ground_pos_._x + back_ground_size_._x*0.05f) + num_size_._x*i;
		num_pos_._y = back_ground_pos_._y + back_ground_size_._y*0.15f;
	}


	//タイマー表示背景生成
	back_ground_sprite_ = std::make_shared<mesh::Sprite>(back_ground_size_);
	back_ground_sprite_->SetAnchorPoint(float2(0.5f, 1.0f));
	back_ground_mesh_object_ = std::make_shared<MeshObject>(back_ground_sprite_);
	//back_ground_mesh_object_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/No.png"));
	back_ground_mesh_object_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/window_256x384.png"));
	back_ground_mesh_object_->SetPosition(back_ground_pos_._x, back_ground_pos_._y, 0.0f);


	//タイマー数字表示の生成
	num_sprite_ = std::make_shared<mesh::Sprite>(num_size_);
	num_sprite_->SetAnchorPoint(float2(0.5f, 1.0f));
	num_object_ = std::make_shared<MeshObject>(num_sprite_);
	num_object_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/kaimaku.png"));
	num_object_->SetTexture(1, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/one.png"));
	num_object_->SetTexture(2, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/two.png"));
	num_object_->SetTexture(3, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/three.png"));
	num_object_->SetPosition(num_pos_);

	timer_max_ = DEFAULT_TIME_MAX;
	timer_count_ = 0;
	digit_num_ = 3;

}

//=============================================================================
// destructor
//=============================================================================
GameStartLogo::~GameStartLogo(void)
{

}
//=============================================================================
// update
//=============================================================================
void GameStartLogo::Update(void)
{
	timer_count_++;
	timer_left_ = (timer_max_ - timer_count_) / 30;	//(最大フレーム-カウント)/一秒のフレーム数
	if (timer_left_ < 0)
	{
		timer_left_ = 0;
	}
	back_ground_sprite_->SetAnchorPoint(float2(0.5f, 0.5f));


	num_sprite_->SetAnchorPoint(float2(0.5f, 0.5f));

	//タイマー数字設定
	unsigned int digit = 1;


	for (int i = 0; i < TIMER_DIGIT; i++)
	{
		int number = timer_left_ / digit % 10;
		digit_num_ = number;
		digit /= 10;
	}

}
//=============================================================================
// draw
//=============================================================================
void GameStartLogo::Draw(void)
{
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");

	//スコア背景の描画
	basic_vs->SetValue("_world_matrix", (f32*)&back_ground_mesh_object_->GetMatrix(), sizeof(float4x4));
	basic_ps->SetTexture("_texture_sampler", back_ground_mesh_object_->GetTexture(0));
	back_ground_mesh_object_->Draw();

	//スコア数字の描画
	basic_vs->SetValue("_world_matrix", (f32*)&num_object_->GetMatrix(), sizeof(float4x4));
	basic_ps->SetTexture("_texture_sampler", num_object_->GetTexture(digit_num_));
	num_object_->Draw();
}

void GameStartLogo::Reset(void)
{
	timer_count_ = 0;
	timer_max_ = DEFAULT_TIME_MAX;
	timer_count_ = 0;
}

u32 GameStartLogo::GetTimeLeft(void) const
{
	return timer_left_;
}
