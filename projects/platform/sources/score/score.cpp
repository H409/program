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
#include "score.h"
#include "mesh/sprite.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "object/mesh_object.h"
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


	//ÉXÉRÉAï\é¶îwåiê∂ê¨ê¬
	back_ground_sprite_[(unsigned int)TEAM::BLUE] = std::make_shared<mesh::Sprite>(size_);
	back_ground_sprite_[(unsigned int)TEAM::BLUE]->SetAnchorPoint(float2(0.5f, 1.0f));
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE] = std::make_shared<MeshObject>(back_ground_sprite_[(unsigned int)TEAM::BLUE]);
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/wall.png"));
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
	back_ground_mesh_object_[(unsigned int)TEAM::RED]->Draw();
	back_ground_mesh_object_[(unsigned int)TEAM::BLUE]->Draw();
}