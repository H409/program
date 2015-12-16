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
	//ÉXÉRÉAîwåiÇÃê›íË
	size_._x = GET_DEFAULT_DISPLAY_SIZE()._x / 3;
	size_._y = GET_DEFAULT_DISPLAY_SIZE()._y / 3;

	//ÉXÉRÉAï\é¶îwåiê∂ê¨ê‘
	back_ground_sprite_[(unsigned int)TEAM::RED] = std::make_shared<mesh::Sprite>(size_);
	back_ground_sprite_[(unsigned int)TEAM::RED]->SetAnchorPoint(float2(0.5f, 1.0f));
	back_ground_mesh_object_[(unsigned int)TEAM::RED] = std::make_shared<MeshObject>(back_ground_sprite_[(unsigned int)TEAM::RED]);
	back_ground_mesh_object_[(unsigned int)TEAM::RED]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/wall.png"));
	back_ground_mesh_object_[(unsigned int)TEAM::RED]->SetPosition(GET_DEFAULT_DISPLAY_SIZE()._x * 0.1f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.3, 0.0f);

	//ÉXÉRÉAï\é¶îwåiê∂ê¨ê¬
	back_ground_sprite_[(unsigned int)TEAM::BLUE] = std::make_shared<mesh::Sprite>(size_);
	back_ground_sprite_[(unsigned int)TEAM::BLUE]->SetAnchorPoint(float2(0.5f, 1.0f));
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE] = std::make_shared<MeshObject>(back_ground_sprite_[(unsigned int)TEAM::BLUE]);
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/wall.png"));
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->SetPosition(GET_DEFAULT_DISPLAY_SIZE()._x * 0.6f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.3, 0.0f);
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

	//ÉXÉRÉAîwåiÇÃï`âÊ
	basic_vs->SetValue("_world_matrix", (f32*)&back_ground_mesh_object_[(unsigned int)TEAM::RED]->GetMatrix(), sizeof(float4x4));
	basic_ps->SetTexture("_texture_sampler", back_ground_mesh_object_[(unsigned int)TEAM::RED]->GetTexture(0));
	back_ground_mesh_object_[(unsigned int)TEAM::RED]->Draw();

	basic_vs->SetValue("_world_matrix", (f32*)&back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->GetMatrix(), sizeof(float4x4));
	basic_ps->SetTexture("_texture_sampler", back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->GetTexture(0));
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->Draw();

	//ÉXÉRÉAêîéöÇÃï`âÊ
}