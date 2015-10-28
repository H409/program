//*****************************************************************************
//
// observer 2d
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBSERVER_2D_H_
#define _OBSERVER_2D_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "observer.h"

//*****************************************************************************
// class declaration
//*****************************************************************************
class Observer2D : public Observer
{
public:
	// constructor
	Observer2D(const f32& in_width,const f32& in_height);

	// 
	virtual ~Observer2D(void) = default;

protected:

private:

};
#endif // _OBSERVER_H_

//---------------------------------- EOF --------------------------------------
