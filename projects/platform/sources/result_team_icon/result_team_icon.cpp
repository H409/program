//*****************************************************************************
//
// result_team_icon
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "result_team_icon.h"
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
ResultTeamIcon::ResultTeamIcon(void)
{
	//スコア背景の設定
	size_._x = GET_DEFAULT_DISPLAY_SIZE()._x / 6;
	size_._y = GET_DEFAULT_DISPLAY_SIZE()._y / 6;

	//スコア表示背景生成赤
	sprite_[(unsigned int)TEAM::RED] = std::make_shared<mesh::Sprite>(size_);
	sprite_[(unsigned int)TEAM::RED]->SetAnchorPoint(float2(0.5f, 1.0f));
	object_[(unsigned int)TEAM::RED] = std::make_shared<MeshObject>(sprite_[(unsigned int)TEAM::RED]);
	object_[(unsigned int)TEAM::RED]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/wall.png"));
	object_[(unsigned int)TEAM::RED]->SetPosition(GET_DEFAULT_DISPLAY_SIZE()._x * 0.15f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.1, 0.0f);


	//スコア表示背景生成青
	sprite_[(unsigned int)TEAM::BLUE] = std::make_shared<mesh::Sprite>(size_);
	sprite_[(unsigned int)TEAM::BLUE]->SetAnchorPoint(float2(0.5f, 1.0f));
	object_[(unsigned int)TEAM::BLUE] = std::make_shared<MeshObject>(sprite_[(unsigned int)TEAM::BLUE]);
	object_[(unsigned int)TEAM::BLUE]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/wall.png"));
	object_[(unsigned int)TEAM::BLUE]->SetPosition(GET_DEFAULT_DISPLAY_SIZE()._x * 0.7f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.1, 0.0f);
}

//=============================================================================
// destructor
//=============================================================================
ResultTeamIcon::~ResultTeamIcon(void)
{

}
//=============================================================================
// update
//=============================================================================
void ResultTeamIcon::Update(void)
{
	sprite_[(unsigned int)TEAM::RED]->SetAnchorPoint(float2(0.5f, 0.5f));
	sprite_[(unsigned int)TEAM::BLUE]->SetAnchorPoint(float2(0.5f, 0.5f));
}
//=============================================================================
// draw
//=============================================================================
void ResultTeamIcon::Draw(void)
{
	//シェーダーを取得
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");

	
	basic_vs->SetValue("_world_matrix", (f32*)&object_[(unsigned int)TEAM::RED]->GetMatrix(), sizeof(float4x4));	//シェーダーに値を設定
	basic_ps->SetTexture("_texture_sampler", object_[(unsigned int)TEAM::RED]->GetTexture(0));

	object_[(unsigned int)TEAM::RED]->Draw();

	basic_vs->SetValue("_world_matrix", (f32*)&object_[(unsigned int)TEAM::BLUE]->GetMatrix(), sizeof(float4x4));
	basic_ps->SetTexture("_texture_sampler", object_[(unsigned int)TEAM::BLUE]->GetTexture(0));

	object_[(unsigned int)TEAM::BLUE]->Draw();
}