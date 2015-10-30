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

private:
	void Update_(const u32& in_delta_time)override;
	void Reset_(void)override;
	std::vector<TAction> actions_;
	bool is_next_;
};

} // namespace action

#endif // _SEQUENCE_H_

//---------------------------------- EOF --------------------------------------
