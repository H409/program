//*****************************************************************************
//
// spawn
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SPAWN_H_
#define _SPAWN_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "action.h"

//*****************************************************************************
// class declaration
//*****************************************************************************
namespace action {
class Spawn : public Action
{
public:
	Spawn(TAction in_action_a,TAction in_action_b);
	virtual ~Spawn(void) = default;

private:
	void Update_(const u32& in_delta_time)override;
	void SetStartParam_(const PARAM& in_param)override;
	std::vector<TAction> actions_;

};

} // namespace action

#endif // _SPAWN_H_

//---------------------------------- EOF --------------------------------------
