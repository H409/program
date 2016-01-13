//*****************************************************************************
//
// tree creater
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#include "tree_creater.h"

TreeCreater::TreeCreater(void)
	:frame_count_(0)
	,position_(0.0f,0.0f,0.0f)
	,is_create_(false)
	,number_(0)
{

}

TreeCreater::~TreeCreater(void)
{
}

void TreeCreater::Update(void)
{
	frame_count_++;

	if(frame_count_ > 180)
	{
		is_create_ = true;
	}
}

void TreeCreater::SetNumber(u32 in_number)
{
	number_ = in_number;
}

void TreeCreater::SetPosition(const float3& in_position)
{
	position_ = in_position;
}

u32 TreeCreater::GetNumber(void) const
{
	return number_;
}

const float3& TreeCreater::GetPosition(void) const
{
	return position_;
}

bool TreeCreater::IsCreate(void) const
{
	return is_create_;
}

//---------------------------------- EOF --------------------------------------
