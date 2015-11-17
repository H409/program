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
	void SetTargetPosition(const float3& in_position);

	// set vector
	void SetTargetVector(const float3& in_vector);

	//
	void SetTargetPreviewPosition( const float3& in_preview_position );

	// set length
	void SetLength(const f32& in_length);

	// set height
	void SetHeight(const f32& in_height);

	//
	float3 GetPosition( void ){ return target_position_ ; }
	float3 GetVector( void ){ return target_vector_ ; }
	float3 GetFrontVector(void)const { auto vector = look_at_ - eye_; return vector; }
	f32 GetLength( void ){ return length_ ; }
	f32 GetHeight( void ){ return height_ ; }
	float3 GetPreviewPosition( void ){ return target_preview_position_ ; }

private:
	float3 target_position_;
	float3 target_vector_;
	float3 target_preview_position_;
	f32 length_;
	f32 height_;
	float3 rotation_ ;

	void MouseMove_( void );
};
#endif // _FOLLOWER_OBSERVER_H_

//---------------------------------- EOF --------------------------------------
