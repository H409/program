//*****************************************************************************
//
// rotate by
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "rotate_by.h"
#include "math/math.h"

namespace action {
//=============================================================================
// constructor
//=============================================================================
RotateBy::RotateBy(const u32& in_duration,const float3& in_rotation)
	:Action(in_duration)
	,rotation_(in_rotation)
{
}

//=============================================================================
// get reverse
//=============================================================================
RotateBy::TAction RotateBy::GetReverse(void) const
{
	return nullptr;
}

//=============================================================================
// update
//=============================================================================
void RotateBy::Update_(const u32& in_delta_time)
{
	auto rate = static_cast<f32>(time_count_) / static_cast<f32>(duration_);
	param_._rotation = start_param_._rotation + rotation_ * rate;
	//param_._rotation._y = utility::math::Wrap(param_._rotation._y,utility::math::ToRadian(-180.0f),utility::math::ToRadian(180.0f));
}
} // namespace action

//---------------------------------- EOF --------------------------------------
