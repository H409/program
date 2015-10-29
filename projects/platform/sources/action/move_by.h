//*****************************************************************************
//
// move by
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MOVE_BY_H_
#define _MOVE_BY_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "action.h"

//*****************************************************************************
// class declaration
//*****************************************************************************
namespace action {
class MoveBy : public Action
{
public:
	MoveBy(const u32& in_duration,const float3& in_move);
	MoveBy(const u32& in_duration,const float3& in_vector,const f32& in_length);
	virtual ~MoveBy(void) = default;

	// get reverse
	TAction GetReverse(void)const override;

private:
	void Update_(const u32& in_delta_time)override;
	float3 move_;
};

} // namespace action

#endif // _MOVE_BY_H_

//---------------------------------- EOF --------------------------------------
