//*****************************************************************************
//
// result observer
//
// Author		: Eyu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _RESULT_OBSERVER_H_
#define _RESULT_OBSERVER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "observer_3d.h"

//*****************************************************************************
// class declaration
//*****************************************************************************
class ResultObserver : public Observer3D
{
public:
	enum STATE
	{
		NONE = -1,
		FOLLWER,
		AIM,
		MAX
	};

	// constructor
	ResultObserver(const f32& in_radian, const f32& in_width, const f32& in_height);

	// 
	virtual ~ResultObserver(void) = default;

	// update
	void Update(void);

	// set position
	void SetTargetPosition(const float3& in_position);

	// set vector
	void SetTargetVector(const float3& in_vector);

	// set target length
	void SetTargetLength(const f32& in_length);

	// set length
	void SetLength(const f32& in_length);

	// set height
	void SetHeight(const f32& in_height);

	//
	float3 GetPosition(void) { return target_position_; }

	float3 GetVector(void) { return target_vector_; }

	float3 GetFrontVector(void)const { auto vector = look_at_ - eye_; return vector; }

	f32 GetLength(void) { return length_; }

	f32 GetHeight(void) { return height_; }

	void SetState(STATE state) { state_ = state; }

	STATE GetState(void)const;

	void SetID(int id) { ID_ = id; };
	int GetID(void) { return ID_; }

	void SetFieldIconPosition(const float3& pos) { feild_icon_ = pos; }

private:
	int ID_;
	float3 target_position_;
	float3 target_vector_;
	f32 target_length_;
	f32 length_;
	f32 height_;
	float3 rotation_;

	float3 feild_icon_;

	STATE state_;

	void TargetLookRotation_(void);
	void MouseMove_(void);
};
#endif // _FOLLOWER_OBSERVER_H_

//---------------------------------- EOF --------------------------------------
