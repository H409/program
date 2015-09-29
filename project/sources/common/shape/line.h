//*****************************************************************************
//
// line
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _LINE_H_
#define _LINE_H_

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

class Line : public Shape
{
public:
	// constructor
	Line(void);
	Line(const float3& in_position,const float3& in_start,const float3& in_end);

	// destructor
	virtual ~Line(void);

	// is collide
	bool IsCollide(const Shape* in_shape)const override;
	bool IsCollide(const Line* in_line)const override;
	bool IsCollide(const Sphere* in_sphere)const override;

	// accessor
	const float3& __start(void)const { return start_; }
	void __start(const float3& in_start) { start_ = in_start; }
	const float3& __end(void)const { return end_; }
	void __end(const float3& in_end) { end_ = in_end; }

private:
	float3 start_;
	float3 end_;
};

} // namespace shape
} // namespace common

#endif // _LINE_H_

//---------------------------------- EOF --------------------------------------
