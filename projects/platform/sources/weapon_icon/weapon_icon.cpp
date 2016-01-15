//*****************************************************************************
//
// weapon_icon
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "weapon_icon.h"
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
WeaponIcon::WeaponIcon(void)
{
	////タイマー背景の設定
	//icon_size_._x = GET_DEFAULT_DISPLAY_SIZE()._x / 6.0f;
	//icon_size_._y = GET_DEFAULT_DISPLAY_SIZE()._y / 6.0f;
	//back_ground_pos_._x = GET_DEFAULT_DISPLAY_SIZE()._x * 0.5f - (back_ground_size_._x / 2);
	//back_ground_pos_._y = GET_DEFAULT_DISPLAY_SIZE()._y * 0.5f - (back_ground_size_._y / 2);

	//武器アイコン表示の設定
	icon_size_._x = GET_DEFAULT_DISPLAY_SIZE()._x / 18.0f;
	icon_size_._y = icon_size_._x;
	icon_size_big._x = GET_DEFAULT_DISPLAY_SIZE()._x / 17.0f;
	icon_size_big._y = icon_size_big._x;
	for (int i = 0; i < WEAPON_SUM; i++)
	{
		/*icon_pos_[i]._x = (GET_DEFAULT_DISPLAY_SIZE()._x / 2 - icon_size_big._x * WEAPON_SUM) + icon_size_big._x * i;*/
		icon_pos_[i][0]._x = 10.0f + icon_size_big._x * i;
		icon_pos_[i][0]._y = (GET_DEFAULT_DISPLAY_SIZE()._y) / 2 - icon_size_big._y;
		icon_pos_[i][1]._x = 10.0f + icon_size_big._x * i;
		icon_pos_[i][1]._y = (GET_DEFAULT_DISPLAY_SIZE()._y) -10.0f - icon_size_big._y;

		icon_pos_[i][2]._x = (GET_DEFAULT_DISPLAY_SIZE()._x - icon_size_big._x * 3) + icon_size_big._x * i;
		icon_pos_[i][2]._y = (GET_DEFAULT_DISPLAY_SIZE()._y) / 2 - icon_size_big._y;
		icon_pos_[i][3]._x = (GET_DEFAULT_DISPLAY_SIZE()._x - icon_size_big._x * 3) + icon_size_big._x * i;
		icon_pos_[i][3]._y = (GET_DEFAULT_DISPLAY_SIZE()._y) - 10.0f - icon_size_big._y;
	}


	//タイマー数字表示の生成
	for (int i = 0; i < WEAPON_SUM; i++)
	{
		icon_sprite_[i][0] = std::make_shared<mesh::Sprite>(icon_size_);
		icon_sprite_[i][0]->SetAnchorPoint(float2(0.5f, 0.5f));
		icon_object_[i][0] = std::make_shared<MeshObject>(icon_sprite_[i][0]);
		icon_object_[i][0]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/zero.png"));
		icon_object_[i][0]->SetPosition(icon_pos_[i][0]);

		icon_sprite_[i][1] = std::make_shared<mesh::Sprite>(icon_size_);
		icon_sprite_[i][1]->SetAnchorPoint(float2(0.5f, 0.5f));
		icon_object_[i][1] = std::make_shared<MeshObject>(icon_sprite_[i][1]);
		icon_object_[i][1]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/zero.png"));
		icon_object_[i][1]->SetPosition(icon_pos_[i][1]);

		icon_sprite_[i][2] = std::make_shared<mesh::Sprite>(icon_size_);
		icon_sprite_[i][2]->SetAnchorPoint(float2(0.5f, 0.5f));
		icon_object_[i][2] = std::make_shared<MeshObject>(icon_sprite_[i][2]);
		icon_object_[i][2]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/zero.png"));
		icon_object_[i][2]->SetPosition(icon_pos_[i][2]);

		icon_sprite_[i][3] = std::make_shared<mesh::Sprite>(icon_size_);
		icon_sprite_[i][3]->SetAnchorPoint(float2(0.5f, 0.5f));
		icon_object_[i][3] = std::make_shared<MeshObject>(icon_sprite_[i][3]);
		icon_object_[i][3]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/zero.png"));
		icon_object_[i][3]->SetPosition(icon_pos_[i][3]);
	}

	for (int i = 0; i < PLAYER_SUM; i++)
	{
		icon_object_[0][i]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/Weapon icon_Bazooka_01.png"));
		icon_object_[0][i]->SetTexture(1, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/Weapon icon_Bazooka_02.png"));
		icon_object_[1][i]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/Weapon icon_Shotgun_01.png"));
		icon_object_[1][i]->SetTexture(1, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/Weapon icon_Shotgun_02.png"));
		icon_object_[2][i]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/Weapon icon_Hoe_01.png"));
		icon_object_[2][i]->SetTexture(1, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/Weapon icon_Hoe_02.png"));
	}

}

//=============================================================================
// destructor
//=============================================================================
WeaponIcon::~WeaponIcon(void)
{

}
//=============================================================================
// update
//=============================================================================
void WeaponIcon::Update(void)
{


}
//=============================================================================
// draw
//=============================================================================
void WeaponIcon::Draw(void)
{
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");

	//スコア数字の描画
	for (int j = 0; j < PLAYER_SUM; j++)
	{
		for (int i = 0; i < WEAPON_SUM; i++)
		{
			basic_vs->SetValue("_world_matrix", (f32*)&icon_object_[i][j]->GetMatrix(), sizeof(float4x4));
			if (weapon_using[j] == i)
			{
				basic_ps->SetTexture("_texture_sampler", icon_object_[i][j]->GetTexture(0));
			}
			else {
				basic_ps->SetTexture("_texture_sampler", icon_object_[i][j]->GetTexture(1));
			}
			icon_object_[i][j]->Draw();
		}
	}
}