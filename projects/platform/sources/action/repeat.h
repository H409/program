//*****************************************************************************
//
// repeat
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _REPEAT_H_
#define _REPEAT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "action.h"

//*****************************************************************************
// class declaration
//*****************************************************************************
namespace action {
class Repeat : public Action
{
public:
	Repeat(const u32& in_repeat_count,TAction in_action);
	virtual ~Repeat(void) = default;

private:
	void Update_(const u32& in_delta_time)override;
	void SetStartParam_(const PARAM& in_param)override;
	TAction action_;
	u32 repeat_count_;
	u32 count_;

};

} // namespace action

#endif // _REPEAT_H_

//---------------------------------- EOF --------------------------------------
