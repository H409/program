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
#include "game_timer.h"
#include "mesh/sprite.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "object/mesh_object.h"
#include "shader/dx9_vertex_shader.h"
#include "shader/dx9_pixel_shader.h"
//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
GameTimer::GameTimer(void)
{
	//タイマー背景の設定
	back_ground_size_._x = GET_DEFAULT_DISPLAY_SIZE()._x / 5.0f;
	back_ground_size_._y = GET_DEFAULT_DISPLAY_SIZE()._y / 5.0f;
	back_ground_pos_._x = GET_DEFAULT_DISPLAY_SIZE()._x * 0.8f;
	back_ground_pos_._y = GET_DEFAULT_DISPLAY_SIZE()._y * 0.1f;

	//タイマー数字表示の設定
	num_size_._x = back_ground_size_._x / 4.0f;
	num_size_._y = back_ground_size_._y;
	for (int i = 0; i < TIMER_DIGIT; i++)
	{
		num_pos_[i]._x = (back_ground_pos_._x + 10.0f )+ num_size_._x*i;
		num_pos_[i]._y = back_ground_pos_._y;
	}


	//タイマー表示背景生成
	back_ground_sprite_ = std::make_shared<mesh::Sprite>(back_ground_size_);
	back_ground_sprite_->SetAnchorPoint(float2(0.5f, 1.0f));
	back_ground_mesh_object_ = std::make_shared<MeshObject>(back_ground_sprite_);
	//back_ground_mesh_object_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/No.png"));
	back_ground_mesh_object_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/window_256x384.png"));
	back_ground_mesh_object_->SetPosition(back_ground_pos_._x, back_ground_pos_._y, 0.0f);


	//タイマー数字表示の生成
	for (int i = 0; i < TIMER_DIGIT; i++)
	{
		num_sprite_[i] = std::make_shared<mesh::Sprite>(num_size_);
		num_sprite_[i]->SetAnchorPoint(float2(0.5f, 1.0f));
		num_object_[i] = std::make_shared<MeshObject>(num_sprite_[i]);
		num_object_[i]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/zero.png"));
		num_object_[i]->SetTexture(1, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/one.png"));
		num_object_[i]->SetTexture(2, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/two.png"));
		num_object_[i]->SetTexture(3, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/three.png"));
		num_object_[i]->SetTexture(4, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/four.png"));
		num_object_[i]->SetTexture(5, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/five.png"));
		num_object_[i]->SetTexture(6, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/six.png"));
		num_object_[i]->SetTexture(7, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/seven.png"));
		num_object_[i]->SetTexture(8, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/eight.png"));
		num_object_[i]->SetTexture(9, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/nine.png"));
		num_object_[i]->SetPosition(num_pos_[i]);
	}

	timer_count_ = 180;
	digit_num_[0] = 1;
	digit_num_[1] = 8;
	digit_num_[2] = 0;

}

//=============================================================================
// destructor
//=============================================================================
GameTimer::~GameTimer(void)
{

}
//=============================================================================
// update
//=============================================================================
void GameTimer::Update(void)
{
	back_ground_sprite_->SetAnchorPoint(float2(0.5f, 0.5f));

	for (int i = 0; i < TIMER_DIGIT; i++)
	{
		num_sprite_[i]->SetAnchorPoint(float2(0.5f, 0.5f));
	}

	//タイマー数字設定
	unsigned int digit = 1;

	for (int i = 0; i < (TIMER_DIGIT - 1); i++)
	{
		digit *= 10;
	}

	for (int i = 0; i < TIMER_DIGIT; i++)
	{
		int number = timer_count_ / digit % 10;
		digit_num_[i] = number;
		digit /= 10;
	}
	
}
//=============================================================================
// draw
//=============================================================================
void GameTimer::Draw(void)
{
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");

	//スコア背景の描画
	basic_vs->SetValue("_world_matrix", (f32*)&back_ground_mesh_object_->GetMatrix(), sizeof(float4x4));
	basic_ps->SetTexture("_texture_sampler", back_ground_mesh_object_->GetTexture(0));
	back_ground_mesh_object_->Draw();

	//スコア数字の描画
	for (int i = 0; i < TIMER_DIGIT; i++)
	{
		basic_vs->SetValue("_world_matrix", (f32*)&num_object_[i]->GetMatrix(), sizeof(float4x4));
		basic_ps->SetTexture("_texture_sampler", num_object_[i]->GetTexture(digit_num_[i]));
		num_object_[i]->Draw();
	}
}