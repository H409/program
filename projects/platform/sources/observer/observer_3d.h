//*****************************************************************************
//
// observer 3D
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBSERVER_3D_H_
#define _OBSERVER_3D_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "observer.h"

//*****************************************************************************
// class declaration
//*****************************************************************************
class Observer3D : public Observer
{
public:
	// constructor
	Observer3D(const f32& in_radian,const f32& in_width,const f32& in_height);

	// 
	virtual ~Observer3D(void) = default;

	float3 GetEye( void ){ return eye_ ; }
	float3 GetLookAt( void ){ return look_at_ ; }
	float3 GetUp( void ){ return up_ ; }

protected:
	float3 eye_;
	float3 look_at_;
	float3 up_;

private:

};
#endif // _OBSERVER_3D_H_

//---------------------------------- EOF --------------------------------------
