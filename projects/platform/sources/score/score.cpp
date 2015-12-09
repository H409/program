//*****************************************************************************
//
// score
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
	block_width_ = 0.5f;
	block_height_ = 0.5f;
	width_count_ = 60;
	height_count_ = 2;
	size_._x = width_count_ * block_width_;
	size_._y = height_count_ * block_height_;
	sprite_ = std::make_shared<mesh::Sprite>(size_);
	sprite_->SetAnchorPoint(float2(0.5f, 1.0f));
	mesh_object_ = std::make_shared<MeshObject>(sprite_);
	mesh_object_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/wall.png"));

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
	sprite_->SetAnchorPoint(float2(0.5f, 1.0f));
}
//=============================================================================
// get object
//=============================================================================
Score::TMeshObject Score::GetObject(void) const
{
	return mesh_object_;
}