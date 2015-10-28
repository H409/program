//*****************************************************************************
//
// follower observer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _FOLLOWER_OBSERVER_H_
#define _FOLLOWER_OBSERVER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "observer_3d.h"

//*****************************************************************************
// class declaration
//*****************************************************************************
class FollowerObserver : public Observer3D
{
public:
	// constructor
	FollowerObserver(const f32& in_radian,const f32& in_width,const f32& in_height);

	// 
	virtual ~FollowerObserver(void) = default;

	// 
	void SetPosition(const float3& in_position);

	// 
	void SetVector(const float3& in_vector);

protected:

private:


};
#endif // _FOLLOWER_OBSERVER_H_

//---------------------------------- EOF --------------------------------------
