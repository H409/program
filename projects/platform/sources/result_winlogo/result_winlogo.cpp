//*****************************************************************************
//
// result_winlogo
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "result_winlogo.h"
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
ResultWinLogo::ResultWinLogo(void)
{
	//スコア背景の設定
	size_._x = GET_DEFAULT_DISPLAY_SIZE()._x / 5;
	size_._y = GET_DEFAULT_DISPLAY_SIZE()._y / 5;

	//スコア表示背景生成赤
	sprite_ = std::make_shared<mesh::Sprite>(size_);
	sprite_->SetAnchorPoint(float2(0.5f, 1.0f));
	object_ = std::make_shared<MeshObject>(sprite_);
	object_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/window_256x384_redwin.png"));//勝利UI
	object_->SetTexture(1, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/window_256x384_bluewin.png"));//引き分けUI
	object_->SetTexture(2, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/window_256x384_wake.png"));//引き分けUI
	object_->SetPosition(GET_DEFAULT_DISPLAY_SIZE()._x * 0.5f-size_._x/2.0f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.75f, 0.0f);
}

//=============================================================================
// destructor
//=============================================================================
ResultWinLogo::~ResultWinLogo(void)
{

}
//=============================================================================
// update
//=============================================================================
void ResultWinLogo::Update(void)
{

	if (state_ == STATE::NEUTRAL)
	{

	}
	else if (state_ == STATE::MOVE)
	{
	
	}
	else if (state_ == STATE::MOVED)
	{

	}
}
//=============================================================================
// draw
//=============================================================================
void ResultWinLogo::Draw(void)
{
	//シェーダーを取得
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");


	basic_vs->SetValue("_world_matrix", (f32*)&object_->GetMatrix(), sizeof(float4x4));	//シェーダーに値を設定
	if (win_team_ == TEAM::RED)
	{
		basic_ps->SetTexture("_texture_sampler", object_->GetTexture(0));
	}

	else if (win_team_ == TEAM::BLUE)
	{
		basic_ps->SetTexture("_texture_sampler", object_->GetTexture(1));
	}

	else if (win_team_ == TEAM::MAX)
	{
		basic_ps->SetTexture("_texture_sampler", object_->GetTexture(2));
	}
	object_->Draw();

}