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
#include "result_score.h"
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
Score::Score(void)
{
	//スコア背景の設定
	back_ground_size_._x = GET_DEFAULT_DISPLAY_SIZE()._x / 3;
	back_ground_size_._y = GET_DEFAULT_DISPLAY_SIZE()._y / 3;
	back_ground_pos_[(unsigned int)TEAM::RED]._x = GET_DEFAULT_DISPLAY_SIZE()._x * 0.1f;
	back_ground_pos_[(unsigned int)TEAM::RED]._y = GET_DEFAULT_DISPLAY_SIZE()._y * 0.3f;
	back_ground_pos_[(unsigned int)TEAM::BLUE]._x = GET_DEFAULT_DISPLAY_SIZE()._x * 0.6f;
	back_ground_pos_[(unsigned int)TEAM::BLUE]._y = GET_DEFAULT_DISPLAY_SIZE()._y * 0.3f;

	//スコア数字表示の設定
	num_size_._x = back_ground_size_._x / 4.0f;
	num_size_._y = back_ground_size_._y * 0.7f;
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		num_pos_[(unsigned int)TEAM::RED][i]._x= back_ground_pos_[(unsigned int)TEAM::RED]._x + back_ground_size_._x*0.15f + num_size_._x*i;
		num_pos_[(unsigned int)TEAM::RED][i]._y = back_ground_pos_[(unsigned int)TEAM::RED]._y + back_ground_size_._y*0.15f;
		num_pos_[(unsigned int)TEAM::BLUE][i]._x = back_ground_pos_[(unsigned int)TEAM::BLUE]._x + back_ground_size_._x*0.15f + num_size_._x*i;
		num_pos_[(unsigned int)TEAM::BLUE][i]._y = back_ground_pos_[(unsigned int)TEAM::BLUE]._y + back_ground_size_._y*0.15f;
	}


	//スコア表示背景生成赤
	back_ground_sprite_[(unsigned int)TEAM::RED] = std::make_shared<mesh::Sprite>(back_ground_size_);
	back_ground_sprite_[(unsigned int)TEAM::RED]->SetAnchorPoint(float2(0.5f, 1.0f));
	back_ground_mesh_object_[(unsigned int)TEAM::RED] = std::make_shared<MeshObject>(back_ground_sprite_[(unsigned int)TEAM::RED]);
	back_ground_mesh_object_[(unsigned int)TEAM::RED]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/window_256x384.png"));
	back_ground_mesh_object_[(unsigned int)TEAM::RED]->SetPosition(back_ground_pos_[(unsigned int)TEAM::RED]._x, back_ground_pos_[(unsigned int)TEAM::RED]._y, 0.0f);

	//スコア表示背景生成青
	back_ground_sprite_[(unsigned int)TEAM::BLUE] = std::make_shared<mesh::Sprite>(back_ground_size_);
	back_ground_sprite_[(unsigned int)TEAM::BLUE]->SetAnchorPoint(float2(0.5f, 1.0f));
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE] = std::make_shared<MeshObject>(back_ground_sprite_[(unsigned int)TEAM::BLUE]);
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/window_256x384.png"));
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->SetPosition(GET_DEFAULT_DISPLAY_SIZE()._x * 0.6f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.3, 0.0f);

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

	state_ = STATE::NEUTRAL;
	easingcount = 0;

	moved_pos_win = float2(GET_DEFAULT_DISPLAY_SIZE()._x / 2.0f - back_ground_size_._x / 2.0f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.3f);
	moved_pos_lose_red = float2(0.0f - 800.0f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.3f);
	moved_pos_lose_blue = float2(GET_DEFAULT_DISPLAY_SIZE()._x + 800.0f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.3f);
	Score::moving_easingtime = 60;

	score[0] = 0;
	score[1] = 0;
}

//=============================================================================
// destructor
//=============================================================================
Score::~Score(void)
{

}
//=============================================================================
// update
//=============================================================================
void Score::Update(void)
{
	back_ground_sprite_[(unsigned int)TEAM::RED]->SetAnchorPoint(float2(0.5f, 0.5f));
	back_ground_sprite_[(unsigned int)TEAM::BLUE]->SetAnchorPoint(float2(0.5f, 0.5f));

	if (state_ == STATE::NEUTRAL)
	{

	}
	else if (state_ == STATE::MOVE)
	{
		easingcount++;
		float2 red_neutralpos = float2(GET_DEFAULT_DISPLAY_SIZE()._x * 0.1f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.3);
		float2 blue_neutralpos = float2(GET_DEFAULT_DISPLAY_SIZE()._x * 0.6f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.3);

		//赤が中央に青が右側に
		if (win_team_ == TEAM::RED)
		{
			float2 red_easinglong = moved_pos_win - red_neutralpos;
			float2 blue_easinglong = moved_pos_lose_blue - blue_neutralpos;
			float2 pos = red_neutralpos + (red_easinglong)*((float)easingcount / (float)moving_easingtime);

			back_ground_mesh_object_[(unsigned int)TEAM::RED]->SetPosition(red_neutralpos + (red_easinglong)*((float)easingcount / (float)moving_easingtime));
			back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->SetPosition(blue_neutralpos + (blue_easinglong)*((float)easingcount / (float)moving_easingtime));

			for (int i = 0; i < SCORE_DIGIT; i++)
			{
				float2 pos;
				pos._x = back_ground_mesh_object_[(unsigned int)TEAM::RED]->GetPosition()._x + back_ground_size_._x*0.15f + num_size_._x*i;
				pos._y = back_ground_mesh_object_[(unsigned int)TEAM::RED]->GetPosition()._y + back_ground_size_._y*0.15f;
				num_object_[(unsigned int)TEAM::RED][i]->SetPosition(pos);

				pos._x = back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->GetPosition()._x + back_ground_size_._x*0.15f + num_size_._x*i;
				pos._y = back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->GetPosition()._y + back_ground_size_._y*0.15f;
				num_object_[(unsigned int)TEAM::BLUE][i]->SetPosition(pos);
			}
		}
		//青が中央に赤が左側に
		else if (win_team_ == TEAM::BLUE)
		{
			float2 red_easinglong = moved_pos_lose_red - red_neutralpos;
			float2 blue_easinglong = moved_pos_win - blue_neutralpos;

			back_ground_mesh_object_[(unsigned int)TEAM::RED]->SetPosition(red_neutralpos + (red_easinglong)*((float)easingcount / (float)moving_easingtime));
			back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->SetPosition(blue_neutralpos + (blue_easinglong)*((float)easingcount / (float)moving_easingtime));

			for (int i = 0; i < SCORE_DIGIT; i++)
			{
				float2 pos;
				pos._x = back_ground_mesh_object_[(unsigned int)TEAM::RED]->GetPosition()._x + back_ground_size_._x*0.15f + num_size_._x*i;
				pos._y = back_ground_mesh_object_[(unsigned int)TEAM::RED]->GetPosition()._y + back_ground_size_._y*0.15f;
				num_object_[(unsigned int)TEAM::RED][i]->SetPosition(pos);

				pos._x = back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->GetPosition()._x + back_ground_size_._x*0.15f+ num_size_._x*i;
				pos._y = back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->GetPosition()._y + back_ground_size_._y*0.15f;
				num_object_[(unsigned int)TEAM::BLUE][i]->SetPosition(pos);
			}
		}

		else {

		}

		//線形補間のカウントが規定値に達した時
		if (easingcount == moving_easingtime)
		{
			state_ = STATE::MOVED;
			easingcount = 0;
		}
	}
	else if (state_ == STATE::MOVED)
	{

	}

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
			int number = score[j] / digit % 10;
			digit_num_[j][i] = number;
			digit /= 10;
		}
	}
}
//=============================================================================
// draw
//=============================================================================
void Score::Draw(void)
{
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");

	//スコア背景の描画
	basic_vs->SetValue("_world_matrix", (f32*)&back_ground_mesh_object_[(unsigned int)TEAM::RED]->GetMatrix(), sizeof(float4x4));
	basic_ps->SetTexture("_texture_sampler", back_ground_mesh_object_[(unsigned int)TEAM::RED]->GetTexture(0));
	back_ground_mesh_object_[(unsigned int)TEAM::RED]->Draw();

	basic_vs->SetValue("_world_matrix", (f32*)&back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->GetMatrix(), sizeof(float4x4));
	basic_ps->SetTexture("_texture_sampler", back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->GetTexture(0));
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->Draw();

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
void Score::Reset(void)
{

	back_ground_pos_[(unsigned int)TEAM::RED]._x = GET_DEFAULT_DISPLAY_SIZE()._x * 0.1f;
	back_ground_pos_[(unsigned int)TEAM::RED]._y = GET_DEFAULT_DISPLAY_SIZE()._y * 0.3f;
	back_ground_pos_[(unsigned int)TEAM::BLUE]._x = GET_DEFAULT_DISPLAY_SIZE()._x * 0.6f;
	back_ground_pos_[(unsigned int)TEAM::BLUE]._y = GET_DEFAULT_DISPLAY_SIZE()._y * 0.3f;

	back_ground_mesh_object_[(unsigned int)TEAM::RED]->SetPosition(back_ground_pos_[(unsigned int)TEAM::RED]);
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->SetPosition(back_ground_pos_[(unsigned int)TEAM::BLUE]);


	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		num_pos_[(unsigned int)TEAM::RED][i]._x = back_ground_pos_[(unsigned int)TEAM::RED]._x + back_ground_size_._x*0.15f + num_size_._x*i;
		num_pos_[(unsigned int)TEAM::RED][i]._y = back_ground_pos_[(unsigned int)TEAM::RED]._y + back_ground_size_._y*0.15f;
		num_pos_[(unsigned int)TEAM::BLUE][i]._x = back_ground_pos_[(unsigned int)TEAM::BLUE]._x + back_ground_size_._x*0.15f + num_size_._x*i;
		num_pos_[(unsigned int)TEAM::BLUE][i]._y = back_ground_pos_[(unsigned int)TEAM::BLUE]._y + back_ground_size_._y*0.15f;

		num_object_[(unsigned int)TEAM::RED][i]->SetPosition(num_pos_[(unsigned int)TEAM::RED][i]);
		num_object_[(unsigned int)TEAM::BLUE][i]->SetPosition(num_pos_[(unsigned int)TEAM::BLUE][i]);
	}

}