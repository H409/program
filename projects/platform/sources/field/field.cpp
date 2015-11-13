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
const float4 Field::DEFAULT_COLOR = float4(1.0f,1.0f,1.0f,1.0f);
const float4 Field::SELECT_COLOR = float4(0.0f,0.0f,1.0f,1.0f);

//=============================================================================
// constructor
//=============================================================================
Field::Field(void)
{
	size_._x = 30.0f * 1.0f;
	size_._y = 30.0f * 1.0f;
	select_index_x_ = 0;
	select_index_y_ = 0;
	block_width_ = 1.0f;
	block_height_ = 1.0f;
	width_count_ = 30;
	height_count_ = 30;
	mesh_sprite_3d_ = std::make_shared<mesh::MeshSprite3D>(block_width_,block_height_,width_count_,height_count_);
	types_.resize(width_count_ * height_count_);
	mesh_object_ = std::make_shared<MeshObject>(mesh_sprite_3d_);
	mesh_object_->SetTexture(0,GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/field.png"));
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
// select block
//=============================================================================
void Field::SelectBlock(const float3& in_position)
{
	if(!IsInRange(in_position))
	{
		return;
	}

	mesh_sprite_3d_->SetColor(select_index_x_,select_index_y_,DEFAULT_COLOR);

	float3 position = float3(in_position._x + size_._x * 0.5f,in_position._y,-(in_position._z - size_._y * 0.5f));

	select_index_x_ = static_cast<u32>(position._x / block_width_);
	select_index_y_ = static_cast<u32>(position._z / block_height_);

	mesh_sprite_3d_->SetColor(select_index_x_,select_index_y_,SELECT_COLOR);
}

//=============================================================================
// set type
//=============================================================================
void Field::SetType(const float3& in_position,const u32& in_type)
{
	if(!IsInRange(in_position))
	{
		return;
	}

	float3 position = float3(in_position._x + size_._x * 0.5f,in_position._y,-(in_position._z - size_._y * 0.5f));

	auto x_index = static_cast<u32>(position._x / block_width_);
	auto y_index = static_cast<u32>(position._z / block_height_);

	u32 index = y_index * width_count_ + x_index;

	DEBUG_ASSERT(types_.size() > index);

	types_[index] = in_type;

	mesh_sprite_3d_->SetIndex(x_index,y_index,in_type);
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

	float3 position = float3(in_position._x + size_._x * 0.5f,in_position._y,-(in_position._z - size_._y * 0.5f));

	auto x_index = static_cast<u32>(position._x / block_width_);
	auto y_index = static_cast<u32>(position._z / block_height_);

	u32 index = y_index * width_count_ + x_index;

	DEBUG_ASSERT(types_.size() > index);

	return types_[index];
}

//---------------------------------- EOF --------------------------------------
