//*****************************************************************************
//
// wall
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "wall.h"
#include "mesh/sprite_3d.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "object/mesh_object.h"
//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
Wall::Wall(void)
{
	block_width_ = 0.5f;
	block_height_ = 0.5f;
	width_count_ = 60;
	height_count_ = 5;
	size_._x = width_count_ * block_width_;
	size_._y = height_count_ * block_height_;
	sprite_3d_ = std::make_shared<mesh::Sprite3D>(size_);

	mesh_object_ = std::make_shared<MeshObject>(sprite_3d_);
	mesh_object_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/field.png"));
	
}

//=============================================================================
// destructor
//=============================================================================
Wall::~Wall(void)
{
}

//=============================================================================
// update
//=============================================================================
void Wall::Update(void)
{

}
//=============================================================================
// get object
//=============================================================================
Wall::TMeshObject Wall::GetObject(void) const
{
	return mesh_object_;
}