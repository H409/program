//*****************************************************************************
//
// sphere
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SPHERE_H_
#define _SPHERE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "shape.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace common
{
namespace shape
{

class Sphere : public Shape
{
public:
	// constructor
	Sphere(void);
	Sphere(const float3& in_position,f32 in_radius);

	// destructor
	virtual ~Sphere(void);

	// is collide
	bool IsCollide(const Shape* in_shape)const override;
	bool IsCollide(const Line* in_line)const override;
	bool IsCollide(const Sphere* in_sphere)const override;

	// accessor
	f32 __radius(void)const { return radius_; }
	void __radius(f32 in_radius) { radius_ = in_radius; }

private:
	f32 radius_;
};

} // namespace shape
} // namespace common

#endif // _SPHERE_H_

//---------------------------------- EOF --------------------------------------
