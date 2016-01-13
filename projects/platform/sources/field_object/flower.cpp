//*****************************************************************************
//
// flower
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "flower.h"
#include "mesh/sprite_3d.h"
#include "object/mesh_object.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "system/input_keyboard.h"
#include "system/input_manager.h"
#include "math/math.h"

//=============================================================================
// constructor
//=============================================================================
Flower::Flower(u32 in_number)
	:position_(0.0f,0.0f,0.0f)
	,is_show_(true)
	,type_(TYPE::SPROUT)
	,time_count_(0)
	,number_(0)
	,is_live_(false)
	,is_growth_(false)
	,tree_index_(-1)
{
	sprite_3d_ = std::make_shared<mesh::Sprite3D>(float2(0.5f,0.5f));
	mesh_object_ = std::make_shared<MeshObject>(sprite_3d_);
	sprite_3d_->SetAnchorPoint(float2(0.5f,0.5f));
	sprite_3d_->Apply();
	height_ = 0.25f;
	SetNumber(in_number);
}

//=============================================================================
// destructor
//=============================================================================
Flower::~Flower(void)
{
}

//=============================================================================
// update
//=============================================================================
void Flower::Update(void)
{
	time_count_++;

	if(type_ == TYPE::SPROUT)
	{
		if(time_count_ > 60 * 3)
		{
			time_count_ = 0;
			type_ = TYPE::FLOWER;
			SetTexture(number_);
		}
	}
}

//=============================================================================
// get object
//=============================================================================
Flower::TMeshObject Flower::GetObject(void) const
{
	return mesh_object_;
}

//=============================================================================
// set position
//=============================================================================
void Flower::SetPosition(const float3& in_position)
{
	position_ = in_position;
	auto position = float3(position_._x,position_._y + height_,position_._z);
	mesh_object_->SetPosition(position);
}

//=============================================================================
// get position
//=============================================================================
const float3& Flower::GetPosition(void)const
{
	return position_;
}

void Flower::Show(void)
{
	is_show_ = true;
	is_live_ = true;
	type_ = TYPE::SPROUT;
	time_count_ = 0;
	SetTexture(number_);
	is_growth_ = false;
}

void Flower::Hide(void)
{
	is_show_ = false;
}

void Flower::Death(void)
{
	is_show_ = false;
	is_live_ = false;
}

void Flower::SetNumber(u32 in_number)
{
	number_ = in_number;
	SetTexture(in_number);
}

void Flower::SetIsGrowth(bool in_is_growth)
{
	is_growth_ = in_is_growth;
}

void Flower::SetTreeIndex(u32 in_index)
{
	tree_index_ = in_index;
}

bool Flower::IsGrowthTree(void) const
{
	return is_growth_;
}

bool Flower::IsShow(void) const
{
	return is_show_;
}

bool Flower::IsLive(void) const
{
	return is_live_;
}

u32 Flower::GetNumber(void) const
{
	return number_;
}

u32 Flower::GetTreeIndex(void) const
{
	return tree_index_;
}

void Flower::SetTexture(u32 in_number)
{
	char work[256] = { 0 };

	if(type_ == TYPE::FLOWER)
	{
		auto team = in_number / 2;
		int number = rand() % 4 + team * 4;
		sprintf_s(work,"resources/texture/flower_00%d.png",number);
	}

	if(type_ == TYPE::SPROUT)
	{
		sprintf_s(work,"resources/texture/sprout.png");
	}
	mesh_object_->SetTexture(0,GET_GRAPHIC_DEVICE()->LoadTexture(work));
}

//---------------------------------- EOF --------------------------------------
