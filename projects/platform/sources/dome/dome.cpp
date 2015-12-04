//*****************************************************************************
//
// Dome
//
// Author		: Eyu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dome.h"
#include "dome/mesh_dome.h"
#include "object/mesh_object.h"
#include "system/win_system.h"
#include "dx9_device.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const float4 Dome::DEFAULT_COLOR = float4(1.0f, 1.0f, 1.0f, 1.0f);
const float4 Dome::SELECT_COLOR = float4(0.0f, 0.0f, 1.0f, 1.0f);

//=============================================================================
// constructor
//=============================================================================
Dome::Dome(void)
{
	select_index_x_ = 0;
	select_index_y_ = 0;
	block_width_ = 10.0f;
	block_height_ = 45.0f;
	width_count_ = 36.0f;
	height_count_ = 4.0f;
	size_._x = width_count_ * block_width_;
	size_._y = height_count_ * block_height_;
	mesh_sprite_dome_ = std::make_shared<mesh::MeshDome>(block_width_, block_height_, width_count_, height_count_);
	mesh_sprite_dome_->SetTexcoord(8, 1);
	types_.resize(width_count_ * height_count_);
	for (auto& type : types_)
	{
		type = 1;
	}

	mesh_sprite_dome_->Apply();

	mesh_object_ = std::make_shared<MeshObject>(mesh_sprite_dome_);
	mesh_object_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/sky000.jpg"));
}

//=============================================================================
// destructor
//=============================================================================
Dome::~Dome(void)
{

}

//=============================================================================
// update
//=============================================================================
void Dome::Update(void)
{

}

//=============================================================================
// get object
//=============================================================================
Dome::TMeshObject Dome::GetObject(void) const
{
	return mesh_object_;
}
