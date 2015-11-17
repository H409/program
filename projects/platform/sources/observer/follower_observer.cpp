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
	,target_length_(1.0f)
{
	rotation_ = float3();
}

//=============================================================================
// update
//=============================================================================
void FollowerObserver::Update(void)
{
	look_at_ = target_position_ + target_vector_ * target_length_;
	auto look_at = float3(look_at_._x,0.0f,look_at_._z);
	auto eye = float3(eye_._x,0.0f,eye_._z);
	auto vector = look_at_ - eye;

	auto length = utility::math::Length(vector);

	vector = utility::math::Normalize(vector);
	eye_ = look_at_ - vector * length_;
	eye_._y += height_;

	view_matrix_ = utility::math::LookAtLH(eye_,look_at_,up_);

	MouseMove_();
}

void FollowerObserver::MouseMove_( void )
{
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
// set target length
//=============================================================================
void FollowerObserver::SetTargetLength(const f32 & in_length)
{
	target_length_ = in_length;
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
