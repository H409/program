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

	// update
	void Update(void);

	// set position
	void SetPosition(const float3& in_position);

	// set vector
	void SetVector(const float3& in_vector);

	// set length
	void SetLength(const f32& in_length);

	// set height
	void SetHeight(const f32& in_height);

private:
	float3 position_;
	float3 vector_;
	f32 length_;
	f32 height_;
	float3 preview_position_;

};
#endif // _FOLLOWER_OBSERVER_H_

//---------------------------------- EOF --------------------------------------