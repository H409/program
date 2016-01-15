//*****************************************************************************
//
// score
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "game_score.h"
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
GameScore::GameScore(void)
{
	//スコア数字表示の設定
	num_size_._x = 20.0f;
	num_size_._y = 40.0f;
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		num_pos_[(unsigned int)TEAM::RED][i]._x = GET_DEFAULT_DISPLAY_SIZE()._x / 2 + num_size_._x*i;
		num_pos_[(unsigned int)TEAM::RED][i]._y = GET_DEFAULT_DISPLAY_SIZE()._y / 2;
		num_pos_[(unsigned int)TEAM::BLUE][i]._x = GET_DEFAULT_DISPLAY_SIZE()._x / 2 + num_size_._x*i;
		num_pos_[(unsigned int)TEAM::BLUE][i]._y = GET_DEFAULT_DISPLAY_SIZE()._y / 2;
	}

	//スコア数字表示の生成
	for (int j = 0; j < (unsigned int)TEAM::MAX; j++)
	{
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			num_sprite_[j][i] = std::make_shared<mesh::Sprite>(num_size_);
			num_sprite_[j][i]->SetAnchorPoint(float2(0.5f, 1.0f));
			num_object_[j][i] = std::make_shared<MeshObject>(num_sprite_[j][i]);
			num_object_[j][i]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/No.png"));
			num_object_[j][i]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/zero.png"));
			num_object_[j][i]->SetTexture(1, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/one.png"));
			num_object_[j][i]->SetTexture(2, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/two.png"));
			num_object_[j][i]->SetTexture(3, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/three.png"));
			num_object_[j][i]->SetTexture(4, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/four.png"));
			num_object_[j][i]->SetTexture(5, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/five.png"));
			num_object_[j][i]->SetTexture(6, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/six.png"));
			num_object_[j][i]->SetTexture(7, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/seven.png"));
			num_object_[j][i]->SetTexture(8, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/eight.png"));
			num_object_[j][i]->SetTexture(9, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/nine.png"));
			num_object_[j][i]->SetPosition(num_pos_[j][i]);
		}
	}
	team_score_[0] = 0;
	team_score_[1] = 0;
}

//=============================================================================
// destructor
//=============================================================================
GameScore::~GameScore(void)
{

}
//=============================================================================
// update
//=============================================================================
void GameScore::Update(void)
{
	//スコア数字設定
	for (int j = 0; j < (int)TEAM::MAX; j++)
	{
		unsigned int digit = 1;
		for (int i = 0; i < (SCORE_DIGIT - 1); i++)
		{
			digit *= 10;
		}
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			int number = team_score_[j] / digit % 10;
			digit_num_[j][i] = number;
			digit /= 10;
		}
	}
}
//=============================================================================
// draw
//=============================================================================
void GameScore::Draw(void)
{
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");

	//スコア数字の描画
	for (int j = 0; j < (unsigned int)TEAM::MAX; j++)
	{
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			basic_vs->SetValue("_world_matrix", (f32*)&num_object_[j][i]->GetMatrix(), sizeof(float4x4));
			basic_ps->SetTexture("_texture_sampler", num_object_[j][i]->GetTexture(digit_num_[j][i]));
			num_object_[j][i]->Draw();
		}
	}
}

//=============================================================================
// reset
//=============================================================================
void GameScore::Reset(void)
{
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		num_pos_[(unsigned int)TEAM::RED][i]._x = GET_DEFAULT_DISPLAY_SIZE()._x / 2 + num_size_._x*i;
		num_pos_[(unsigned int)TEAM::RED][i]._y = GET_DEFAULT_DISPLAY_SIZE()._y / 2;
		num_pos_[(unsigned int)TEAM::BLUE][i]._x = GET_DEFAULT_DISPLAY_SIZE()._x / 2 + num_size_._x*i;
		num_pos_[(unsigned int)TEAM::BLUE][i]._y = GET_DEFAULT_DISPLAY_SIZE()._y / 2;

		num_object_[(unsigned int)TEAM::RED][i]->SetPosition(num_pos_[(unsigned int)TEAM::RED][i]);
		num_object_[(unsigned int)TEAM::BLUE][i]->SetPosition(num_pos_[(unsigned int)TEAM::BLUE][i]);
	}

}