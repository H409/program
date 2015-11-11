//*****************************************************************************
//
// field
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "field.h"
#include "mesh/mesh_sprite_3d.h"
#include "object/mesh_object.h"
#include "system/win_system.h"
#include "dx9_device.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
Field::Field(void)
{
	mesh_sprite_3d_ = std::make_shared<mesh::MeshSprite3D>(30,30);
	mesh_object_ = std::make_shared<MeshObject>(mesh_sprite_3d_);
	mesh_object_->SetTexture(0,GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/test.png"));
}

//=============================================================================
// destructor
//=============================================================================
Field::~Field(void)
{
}

//=============================================================================
// get object
//=============================================================================
Field::TMeshObject Field::GetObject(void) const
{
	return mesh_object_;
}

//=============================================================================
// is in range
//=============================================================================
bool Field::IsInRange(const float3& in_position)const
{
	float3 position = in_position;

	if(-size_._x * 0.5f > position._x)
	{
		return false;
	}

	if(size_._x * 0.5f < position._x)
	{
		return false;
	}

	if(-size_._y * 0.5f > position._z)
	{
		return false;
	}

	if(size_._y * 0.5f < position._z)
	{
		return false;
	}

	return true;
}

//=============================================================================
// get type
//=============================================================================
u32 Field::GetType(const float3& in_position)const
{
	if(!IsInRange(in_position))
	{
		return -1;
	}

	float3 position = float3(in_position._x + size_._x * 0.5f,in_position._y,in_position._z - size_._y * 0.5f);

	auto x_index = static_cast<u32>(position._x / block_width_);
	auto y_index = static_cast<u32>(position._z / block_height_);

	u32 index = y_index * width_count_ + x_index;

	DEBUG_ASSERT(types_.size() > index);

	return types_[index];
}

//---------------------------------- EOF --------------------------------------
