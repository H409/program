//*****************************************************************************
//
// spawn
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "spawn.h"
#include "math/math.h"

namespace action {
//=============================================================================
// constructor
//=============================================================================
Spawn::Spawn(TAction in_action_a,TAction in_action_b)
{
	actions_.push_back(in_action_a);
	actions_.push_back(in_action_b);
}

//=============================================================================
// update
//=============================================================================
void Spawn::Update_(const u32& in_delta_time)
{
	auto delta_time = in_delta_time;
	PARAM params;

	if(!IsEnd())
	{
		auto is_run = false;
		for(auto action : actions_)
		{
			if(!action->IsEnd())
			{
				action->Update(delta_time);
				auto param = action->GetParam();
				param = param - start_param_;
				params += param;
				is_run = true;
			}
		}

		if(is_run)
		{
			param_ = start_param_ + params;
		}
		else
		{
			is_end_ = true;
		}
	}
}

//=============================================================================
// set start param
//=============================================================================
void Spawn::SetStartParam_(const PARAM& in_param)
{
	for(auto action : actions_)
	{
		action->SetStartParam(in_param);
	}
}

} // namespace action

//---------------------------------- EOF --------------------------------------
