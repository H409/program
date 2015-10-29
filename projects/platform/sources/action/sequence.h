//*****************************************************************************
//
// sequence
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "action.h"

//*****************************************************************************
// class declaration
//*****************************************************************************
namespace action {
class Sequence : public Action
{
public:
	Sequence(TAction in_action_a,TAction in_action_b);
	virtual ~Sequence(void) = default;

	// get reverse
	TAction GetReverse(void)const override;

private:
	void Update_(const u32& in_delta_time)override;
	std::vector<TAction> actions_;
	bool is_next_;
};

} // namespace action

#endif // _MOVE_TO_H_

//---------------------------------- EOF --------------------------------------
