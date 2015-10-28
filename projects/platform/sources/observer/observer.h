//*****************************************************************************
//
// observer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBSERVER_H_
#define _OBSERVER_H_

//*****************************************************************************
// class declaration
//*****************************************************************************
class Observer
{
public:
	// 
	virtual ~Observer(void) = default;

	// get view matrix
	const float4x4& GetViewMatrix(void)const;

	// get projection matrix
	const float4x4& GetProjectionMatrix(void)const;

protected:
	Observer(void) = default;
	float4x4 view_matrix_;
	float4x4 projection_matrix_;

};
#endif // _OBSERVER_H_

//---------------------------------- EOF --------------------------------------
