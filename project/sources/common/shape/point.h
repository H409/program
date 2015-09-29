//*****************************************************************************
//
// point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _POINT_H_
#define _POINT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "shape.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace common
{
namespace shape
{

class Point : public Shape
{
public:
	// constructor
	Point(void);

	// destructor
	virtual ~Point(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// is collide
	bool IsCollide(const Shape* in_shape)const override;
	bool IsCollide(const Point* in_point)const override;

protected:

private:

};

} // namespace shape
} // namespace common

#endif // _POINT_H_

//---------------------------------- EOF --------------------------------------
