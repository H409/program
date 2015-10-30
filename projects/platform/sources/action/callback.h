//*****************************************************************************
//
// callback
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _CALLBACK_H_
#define _CALLBACK_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "action.h"

//*****************************************************************************
// class declaration
//*****************************************************************************
namespace action {
class Callback : public Action
{
public:
	using TCallback = std::function<void(void)>;
	explicit Callback(const TCallback& in_callback);
	virtual ~Callback(void) = default;

private:
	void Update_(const u32& in_delta_time)override;
	TCallback callback_;
};

} // namespace action

#endif // _CALLBACK_H_

//---------------------------------- EOF --------------------------------------
