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
	select_index_x_ = 0;
	select_index_y_ = 0;
	block_width_ = 0.5f;
	block_height_ = 0.5f;
	width_count_ = 60;
	height_count_ = 60;
	size_._x = width_count_ * block_width_;
	size_._y = height_count_ * block_height_;
	mesh_sprite_3d_ = std::make_shared<mesh::MeshSprite3D>(block_width_,block_height_,width_count_,height_count_);
	mesh_sprite_3d_->SetTexcoord(4,4);
	types_.resize(width_count_ * height_count_);
	for(auto& type : types_)
	{
		type = 1;
	}

	mesh_sprite_3d_->SetIndex(types_);
	mesh_sprite_3d_->Apply();

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
// update
//=============================================================================
void Field::Update(void)
{
	for(u32 i = 0;i < height_count_;++i)
	{
		for(u32 j = 0;j < width_count_;++j)
		{
			if(CheckTypeRightBottom(j,i,2))
			{
				SetType(j + 0,i + 0,3);
				SetType(j + 1,i + 0,3);
				SetType(j + 0,i + 1,3);
				SetType(j + 1,i + 1,3);
			}
		}
	}
}

void Field::Reset(void)
{
	for(auto& type : types_)
	{
		type = 1;
	}

	mesh_sprite_3d_->SetIndex(types_);
	mesh_sprite_3d_->Apply();
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

void Field::NotSelectBlock(void)
{
	mesh_sprite_3d_->SetColor(select_index_x_,select_index_y_,DEFAULT_COLOR);
}

float3 Field::GetBlockPosition(const float3& in_position)
{
	float3 position = float3(0.0f,0.0f,0.0f);
	float3 offset = float3(-block_width_ * width_count_ * 0.5f,0.0f,-block_height_ * height_count_ * 0.5f);

	auto x = (u32)((in_position._x - offset._x) / block_width_);
	auto y = (u32)((in_position._z - offset._z) / block_height_);

	position._x = x * block_width_ + block_width_ * 0.5f + offset._x;
	position._y = 0.0f;
	position._z = y * block_height_ + block_height_ * 0.5f + offset._z;

	return position;
}

u32 Field::GetBlockIndex(const float3& in_position)
{
	float3 offset = float3(-block_width_ * width_count_ * 0.5f,0.0f,-block_height_ * height_count_ * 0.5f);
	auto x = (u32)((in_position._x - offset._x) / block_width_);
	auto y = (u32)((in_position._z - offset._z) / block_height_);

	return y * width_count_ + x;
}

//=============================================================================
// get positions
//=============================================================================
std::vector<float3> Field::GetPositionsF(const u32& in_type)
{
	std::vector<float3> positions;
	float3 offset = float3(-block_width_ * width_count_ * 0.5f,0.0f,-block_height_ * height_count_ * 0.5f);

	for(u32 i = 0;i < height_count_;++i)
	{
		for(u32 j = 0;j < width_count_;++j)
		{
			u32 index = i * width_count_ + j;
			if(types_[index] == in_type)
			{
				float3 position = float3(offset._x + j * block_width_ + block_width_ * 0.5f,0.0f,offset._z + i * block_height_ + block_height_ * 0.5f);
				positions.push_back(position);
			}
		}
	}

	return positions;
}

//=============================================================================
// get positions
//=============================================================================
std::vector<float3> Field::GetPositionsT(const u32& in_type)
{
	std::vector<float3> positions;

	for(u32 i = 0;i < height_count_;++i)
	{
		for(u32 j = 0;j < width_count_;++j)
		{
			if(CheckTypeRightBottom(j,i,in_type))
			{
				float3 position = float3((j + 1) * block_width_,0.0f,(i + 1) * block_height_);
				positions.push_back(position);
				++j;
			}
		}
	}

	return positions;
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

	auto x = static_cast<u32>(position._x / block_width_);
	auto y = static_cast<u32>(position._z / block_height_);

	SetType(x,y,in_type);
}

void Field::SetType(const u32& in_x,const u32& in_y,const u32& in_type)
{
	u32 index = in_y * width_count_ + in_x;

	DEBUG_ASSERT(types_.size() > index);

	types_[index] = in_type;

	mesh_sprite_3d_->SetIndex(in_x,in_y,in_type);

	mesh_sprite_3d_->Apply();
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

u32 Field::CountType(u32 in_type)
{
	u32 count = 0;
	for(auto type : types_)
	{
		if(type == in_type)
		{
			count++;
		}
	}
	return count;
}

//=============================================================================
// check type
//=============================================================================
bool Field::CheckType(const u32& in_x,const u32& in_y,const u32& in_type)
{
	if(CheckTypeLeftTop(in_x,in_y,in_type))
	{
		return true;
	}

	if(CheckTypeLeftBottom(in_x,in_y,in_type))
	{
		return true;
	}

	if(CheckTypeRightTop(in_x,in_y,in_type))
	{
		return true;
	}

	if(CheckTypeRightBottom(in_x,in_y,in_type))
	{
		return true;
	}

	return false;
}

//=============================================================================
// check type left top
//=============================================================================
bool Field::CheckTypeLeftTop(const u32& in_x,const u32& in_y,const u32& in_type)
{
	if(in_x < 1)
	{
		return false;
	}

	if(in_y < 1)
	{
		return false;
	}

	if(in_x > width_count_)
	{
		return false;
	}

	if(in_y > height_count_)
	{
		return false;
	}

	auto index = in_y * width_count_ + in_x;

	if(types_[index] != in_type)
	{
		return false;
	}

	if(types_[index - 1] != in_type)
	{
		return false;
	}

	if(types_[index - width_count_] != in_type)
	{
		return false;
	}

	if(types_[index - width_count_ - 1] != in_type)
	{
		return false;
	}

	return true;
}

//=============================================================================
// check type left top
//=============================================================================
bool Field::CheckTypeLeftBottom(const u32& in_x,const u32& in_y,const u32& in_type)
{
	if(in_x < 1)
	{
		return false;
	}

	if(in_x > width_count_)
	{
		return false;
	}

	if(in_y >= height_count_)
	{
		return false;
	}

	auto index = in_y * width_count_ + in_x;

	if(types_[index] != in_type)
	{
		return false;
	}

	if(types_[index - 1] != in_type)
	{
		return false;
	}

	if(types_[index + width_count_] != in_type)
	{
		return false;
	}

	if(types_[index + width_count_ - 1] != in_type)
	{
		return false;
	}

	return true;
}

//=============================================================================
// check type right top
//=============================================================================
bool Field::CheckTypeRightTop(const u32& in_x,const u32& in_y,const u32& in_type)
{
	if(in_y < 1)
	{
		return false;
	}

	if(in_x >= width_count_)
	{
		return false;
	}

	if(in_y > height_count_)
	{
		return false;
	}

	auto index = in_y * width_count_ + in_x;

	if(types_[index] != in_type)
	{
		return false;
	}

	if(types_[index + 1] != in_type)
	{
		return false;
	}

	if(types_[index - width_count_] != in_type)
	{
		return false;
	}

	if(types_[index - width_count_ + 1] != in_type)
	{
		return false;
	}

	return true;
}

//=============================================================================
// check type right bottom
//=============================================================================
bool Field::CheckTypeRightBottom(const u32& in_x,const u32& in_y,const u32& in_type)
{
	if(in_x >= width_count_)
	{
		return false;
	}

	if(in_y >= height_count_)
	{
		return false;
	}

	auto index = in_y * width_count_ + in_x;

	if(types_[index] != in_type)
	{
		return false;
	}

	if(types_[index + 1] != in_type)
	{
		return false;
	}

	if(types_[index + width_count_] != in_type)
	{
		return false;
	}

	if(types_[index + width_count_ + 1] != in_type)
	{
		return false;
	}

	return true;
}

//---------------------------------- EOF --------------------------------------
