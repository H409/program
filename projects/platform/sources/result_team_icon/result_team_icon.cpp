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
	//�X�R�A�w�i�̐ݒ�
	size_._x = GET_DEFAULT_DISPLAY_SIZE()._x / 6;
	size_._y = GET_DEFAULT_DISPLAY_SIZE()._y / 6;

	//�X�R�A�\���w�i������
	sprite_[(unsigned int)TEAM::RED] = std::make_shared<mesh::Sprite>(size_);
	sprite_[(unsigned int)TEAM::RED]->SetAnchorPoint(float2(0.5f, 1.0f));
	object_[(unsigned int)TEAM::RED] = std::make_shared<MeshObject>(sprite_[(unsigned int)TEAM::RED]);
	object_[(unsigned int)TEAM::RED]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/window_256x384_redteam.png"));
	object_[(unsigned int)TEAM::RED]->SetPosition(GET_DEFAULT_DISPLAY_SIZE()._x * 0.15f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.1, 0.0f);


	//�X�R�A�\���w�i������
	sprite_[(unsigned int)TEAM::BLUE] = std::make_shared<mesh::Sprite>(size_);
	sprite_[(unsigned int)TEAM::BLUE]->SetAnchorPoint(float2(0.5f, 1.0f));
	object_[(unsigned int)TEAM::BLUE] = std::make_shared<MeshObject>(sprite_[(unsigned int)TEAM::BLUE]);
	object_[(unsigned int)TEAM::BLUE]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/window_256x384_blueteam.png"));
	object_[(unsigned int)TEAM::BLUE]->SetPosition(GET_DEFAULT_DISPLAY_SIZE()._x * 0.7f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.1, 0.0f);
	state_ = STATE::NEUTRAL;
	easingcount = 0;

	//
	moved_pos_win = float2(GET_DEFAULT_DISPLAY_SIZE()._x / 2.0f -size_._x/2.0f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.1f);
	moved_pos_lose_red = float2(0.0f - 500.0f, GET_DEFAULT_DISPLAY_SIZE()._y*0.1f);
	moved_pos_lose_blue = float2(GET_DEFAULT_DISPLAY_SIZE()._x + 500.0f, GET_DEFAULT_DISPLAY_SIZE()._y*0.1f);
	ResultTeamIcon::moving_easingtime = 60;
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
	if (state_ == STATE::NEUTRAL)
	{

	}
	else if (state_ == STATE::MOVE)
	{
		easingcount++;
		float2 red_neutralpos = float2(GET_DEFAULT_DISPLAY_SIZE()._x * 0.15f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.1);
		float2 blue_neutralpos = float2(GET_DEFAULT_DISPLAY_SIZE()._x * 0.7f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.1);

		//�Ԃ������ɐ��E����
		if (win_team_ == TEAM::RED)
		{
			float2 red_easinglong = moved_pos_win - red_neutralpos;
			float2 blue_easinglong = moved_pos_lose_blue - blue_neutralpos;

			float2 pos = red_neutralpos + (red_easinglong)*((float)easingcount / (float)moving_easingtime);

			object_[(unsigned int)TEAM::RED]->SetPosition(red_neutralpos + (red_easinglong)*((float)easingcount / (float)moving_easingtime));
			object_[(unsigned int)TEAM::BLUE]->SetPosition(blue_neutralpos + (blue_easinglong)*((float)easingcount / (float)moving_easingtime));
		}
		//�������ɐԂ�������
		else if (win_team_ == TEAM::BLUE)
		{
			float2 red_easinglong = moved_pos_lose_red - red_neutralpos;
			float2 blue_easinglong = moved_pos_win - blue_neutralpos;

			object_[(unsigned int)TEAM::RED]->SetPosition(red_neutralpos + (red_easinglong)*((float)easingcount / (float)moving_easingtime));
			object_[(unsigned int)TEAM::BLUE]->SetPosition(blue_neutralpos + (blue_easinglong)*((float)easingcount / (float)moving_easingtime));
		}
		//��������
		else {

		}

		//���`��Ԃ̃J�E���g���K��l�ɒB������
		if (easingcount == moving_easingtime)
		{
			state_ = STATE::MOVED;
			easingcount = 0;
		}
	}
	else if (state_ == STATE::MOVED)
	{

	}
}
//=============================================================================
// draw
//=============================================================================
void ResultTeamIcon::Draw(void)
{
	//�V�F�[�_�[���擾
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");

	
	basic_vs->SetValue("_world_matrix", (f32*)&object_[(unsigned int)TEAM::RED]->GetMatrix(), sizeof(float4x4));	//�V�F�[�_�[�ɒl��ݒ�
	basic_ps->SetTexture("_texture_sampler", object_[(unsigned int)TEAM::RED]->GetTexture(0));

	object_[(unsigned int)TEAM::RED]->Draw();

	basic_vs->SetValue("_world_matrix", (f32*)&object_[(unsigned int)TEAM::BLUE]->GetMatrix(), sizeof(float4x4));
	basic_ps->SetTexture("_texture_sampler", object_[(unsigned int)TEAM::BLUE]->GetTexture(0));

	object_[(unsigned int)TEAM::BLUE]->Draw();
}

//=============================================================================
// reset
//=============================================================================
void ResultTeamIcon::Reset(void)
{
	object_[(unsigned int)TEAM::RED]->SetPosition(GET_DEFAULT_DISPLAY_SIZE()._x * 0.15f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.1, 0.0f);
	object_[(unsigned int)TEAM::BLUE]->SetPosition(GET_DEFAULT_DISPLAY_SIZE()._x * 0.7f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.1, 0.0f);
}