//*****************************************************************************
//
// move to
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "move_to.h"
#include "math/math.h"

namespace action {
//=============================================================================
// constructor
//=============================================================================
MoveTo::MoveTo(const u32& in_duration,const float3& in_goal_position)
	:Action(in_duration)
	,goal_position_(in_goal_position)
{
}

//=============================================================================
// get reverse
//=============================================================================
MoveTo::TAction MoveTo::GetReverse(void) const
{
	return nullptr;
}

//=============================================================================
// update
//=============================================================================
void MoveTo::Update_(const u32& in_delta_time)
{
	auto vector = goal_position_ - start_param_._position;
	auto rate = static_cast<f32>(time_count_) / static_cast<f32>(duration_);
	param_._position = start_param_._position + vector * rate;

}
} // namespace action

//---------------------------------- EOF --------------------------------------
