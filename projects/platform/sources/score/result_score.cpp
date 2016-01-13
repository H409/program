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
	num_size_._x = back_ground_size_._x / 3.0f;
	num_size_._y = back_ground_size_._y;
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		num_pos_[(unsigned int)TEAM::RED][i]._x= back_ground_pos_[(unsigned int)TEAM::RED]._x + num_size_._x*i;
		num_pos_[(unsigned int)TEAM::RED][i]._y= back_ground_pos_[(unsigned int)TEAM::RED]._y;
		num_pos_[(unsigned int)TEAM::BLUE][i]._x = back_ground_pos_[(unsigned int)TEAM::BLUE]._x + num_size_._x*i;
		num_pos_[(unsigned int)TEAM::BLUE][i]._y = back_ground_pos_[(unsigned int)TEAM::BLUE]._y;
	}


	//スコア表示背景生成赤
	back_ground_sprite_[(unsigned int)TEAM::RED] = std::make_shared<mesh::Sprite>(back_ground_size_);
	back_ground_sprite_[(unsigned int)TEAM::RED]->SetAnchorPoint(float2(0.5f, 1.0f));
	back_ground_mesh_object_[(unsigned int)TEAM::RED] = std::make_shared<MeshObject>(back_ground_sprite_[(unsigned int)TEAM::RED]);
	back_ground_mesh_object_[(unsigned int)TEAM::RED]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/kari_window_256x384.png"));
	back_ground_mesh_object_[(unsigned int)TEAM::RED]->SetPosition(back_ground_pos_[(unsigned int)TEAM::RED]._x, back_ground_pos_[(unsigned int)TEAM::RED]._y, 0.0f);

	//スコア表示背景生成青
	back_ground_sprite_[(unsigned int)TEAM::BLUE] = std::make_shared<mesh::Sprite>(back_ground_size_);
	back_ground_sprite_[(unsigned int)TEAM::BLUE]->SetAnchorPoint(float2(0.5f, 1.0f));
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE] = std::make_shared<MeshObject>(back_ground_sprite_[(unsigned int)TEAM::BLUE]);
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/kari_window_256x384.png"));
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
			num_object_[j][i]->SetPosition(num_pos_[j][i]);
		}
	}
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
}