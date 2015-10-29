//*****************************************************************************
//
// sequence
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "sequence.h"
#include "math/math.h"

namespace action {
//=============================================================================
// 
//=============================================================================
Sequence::Sequence(TAction in_action_a,TAction in_action_b)
	:is_next_(true)
{
	actions_.push_back(in_action_a);
	actions_.push_back(in_action_b);
}

//=============================================================================
// get reverse
//=============================================================================
Sequence::TAction Sequence::GetReverse(void) const
{
	return nullptr;
}

//=============================================================================
// update
//=============================================================================
void Sequence::Update_(const u32& in_delta_time)
{
	auto delta_time = in_delta_time;

	for(auto action : actions_)
	{
		if(!action->IsEnd())
		{
			if(is_next_)
			{
				action->SetStartPosition(position_);
				is_next_ = false;
			}
			delta_time = action->Update(delta_time);
			position_ = action->GetPosition();
			is_next_ = action->IsEnd();
			if(delta_time <= 0)
			{
				return;
			}
		}
	}

	is_end_ = true;
}

} // namespace action

//---------------------------------- EOF --------------------------------------
