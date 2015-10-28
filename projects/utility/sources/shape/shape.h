//*****************************************************************************
//
// shape
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SHAPE_H_
#define _SHAPE_H_

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace common
{
namespace shape
{
class Line;
class Sphere;
} // namespace shape
} // namespace common

//*****************************************************************************
// class definition
//*****************************************************************************
namespace common
{
namespace shape
{

class Shape
{
public:
	enum TYPE
	{
		TYPE_POINT = 0,
		TYPE_LINE,
		TYPE_SPHERE,
		TYPE_TRIANGLE,
		TYPE_RECTANGLE,
		TYPE_MAX,
	};

	// constructor
	explicit Shape(const TYPE& in_type);
	Shape(const TYPE& in_type,const float3& in_position);

	// destructor
	virtual ~Shape(void);

	// is collide
	virtual bool IsCollide(const Shape* in_shape)const = 0;
	virtual bool IsCollide(const Line* in_line)const = 0;
	virtual bool IsCollide(const Sphere* in_sphere)const = 0;

	// accessor
	const TYPE& __type(void)const { return type_; }
	const float3& __position(void)const { return position_; }
	void __position(const float3& in_position) { position_ = in_position; }

protected:
	float3 position_;

private:
	TYPE type_;
};

} // namespace shape
} // namespace common

#endif // _SHAPE_H_

//---------------------------------- EOF --------------------------------------
