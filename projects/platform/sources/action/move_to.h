//*****************************************************************************
//
// move to
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MOVE_TO_H_
#define _MOVE_TO_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "action.h"

//*****************************************************************************
// class declaration
//*****************************************************************************
namespace action {
class MoveTo : public Action
{
public:
	MoveTo(const u32& in_duration,const float3& in_goal_position);
	virtual ~MoveTo(void) = default;

	// get reverse
	TAction GetReverse(void)const override;

private:
	void Update_(const u32& in_delta_time)override;
	float3 goal_position_;
};

} // namespace action

#endif // _MOVE_TO_H_

//---------------------------------- EOF --------------------------------------
