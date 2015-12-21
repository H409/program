//*****************************************************************************
//
// effect
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#include "effect.h"
#include "object/mesh_object.h"

Effect::Effect(void)
{
}

Effect::~Effect(void)
{
}

void Effect::Update(void)
{
	if(frame_count_ < frame_)
	{
		frame_count_++;
		Update_();
	}
}

Effect::TMeshObject Effect::GetObject(void) const
{
	return mesh_object_;
}

bool Effect::IsDeath(void) const
{
	return frame_ <= frame_count_;
}

void Effect::Start(u32 in_frame,const float3& in_start_position)
{
	frame_count_ = 0;

	frame_ = in_frame;

	start_position_ = in_start_position;

	mesh_object_->SetPosition(in_start_position);
}

//---------------------------------- EOF --------------------------------------
