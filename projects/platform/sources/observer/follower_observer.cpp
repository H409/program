//*****************************************************************************
//
// follower observer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "follower_observer.h"
#include "math/math.h"

//=============================================================================
// constructor
//=============================================================================
FollowerObserver::FollowerObserver(const f32& in_radian,const f32& in_width,const f32& in_height)
	:Observer3D(in_radian,in_width,in_height)
{
	rotation_ = float3();
}

//=============================================================================
// update
//=============================================================================
void FollowerObserver::Update(void)
{
	look_at_ = target_position_;
	eye_ = look_at_ - target_vector_ * length_;
	eye_ = look_at_ + length_;
	
	eye_._y = height_;

	view_matrix_ = utility::math::LookAtLH(eye_,look_at_,up_);

	//rotation_ 
}

//=============================================================================
// 
//=============================================================================
void FollowerObserver::SetTargetPosition(const float3 & in_position)
{
	target_position_ = in_position;
}

//=============================================================================
// set vector
//=============================================================================
void FollowerObserver::SetTargetVector(const float3 & in_vector)
{
	target_vector_ = utility::math::Normalize(float3(in_vector._x,0.0f,in_vector._z));;
}

//=============================================================================
// set length
//=============================================================================
void FollowerObserver::SetLength(const f32 & in_length)
{
	length_ = in_length;
}

//=============================================================================
// set height
//=============================================================================
void FollowerObserver::SetHeight(const f32& in_height)
{
	height_ = in_height;
}

//---------------------------------- EOF --------------------------------------
