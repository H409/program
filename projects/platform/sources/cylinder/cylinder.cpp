//*****************************************************************************
//
// Cylinder
//
// Author		: Eyu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "cylinder.h"
#include "mesh/mesh_cylinder.h"
#include "object/mesh_object.h"
#include "system/win_system.h"
#include "dx9_device.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const float4 Cylinder::DEFAULT_COLOR = float4(1.0f, 1.0f, 1.0f, 1.0f);
const float4 Cylinder::SELECT_COLOR = float4(0.0f, 0.0f, 1.0f, 1.0f);

//=============================================================================
// constructor
//=============================================================================
Cylinder::Cylinder(void)
{
	select_index_x_ = 0;
	select_index_y_ = 0;
	block_width_ = (f32)4.5;
	block_height_ = (f32)7.5;
	width_count_ = (u32)36.0;
	height_count_ = (u32)1.0;
	size_._x = width_count_ * block_width_;
	size_._y = height_count_ * block_height_;
	mesh_sprite_dome_ = std::make_shared<mesh::MeshCylinder>(block_width_, block_height_, width_count_, height_count_);
	mesh_sprite_dome_->SetTexcoord(1, 1);
	types_.resize(width_count_ * height_count_);
	for (auto& type : types_)
	{
		type = 1;
	}

	mesh_sprite_dome_->Apply();

	mesh_object_ = std::make_shared<MeshObject>(mesh_sprite_dome_);
	mesh_object_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/cylinder.jpg"));
}

//=============================================================================
// destructor
//=============================================================================
Cylinder::~Cylinder(void)
{

}

//=============================================================================
// update
//=============================================================================
void Cylinder::Update(void)
{

}

//=============================================================================
// get object
//=============================================================================
Cylinder::TMeshObject Cylinder::GetObject(void) const
{
	return mesh_object_;
}
