//*****************************************************************************
//
// rotate by
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _ROTATE_BY_H_
#define _ROTATE_BY_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "action.h"

//*****************************************************************************
// class declaration
//*****************************************************************************
namespace action {
class RotateBy : public Action
{
public:
	RotateBy(const u32& in_duration,const float3& in_rotation);
	virtual ~RotateBy(void) = default;

	// get reverse
	TAction GetReverse(void)const override;

private:
	void Update_(const u32& in_delta_time)override;
	float3 rotation_;
};

} // namespace action

#endif // _ROTATE_BY_H_

//---------------------------------- EOF --------------------------------------
