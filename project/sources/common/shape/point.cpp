//*****************************************************************************
//
// point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "point.h"

namespace common
{
namespace shape
{

//=============================================================================
// constructor
//=============================================================================
Point::Point(void)
	:Shape(TYPE_POINT)
{
}

//=============================================================================
// destructor
//=============================================================================
Point::~Point(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Point::Initialize(void)
{
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Point::Uninitialize(void)
{
}

//=============================================================================
// is collide
//=============================================================================
bool Point::IsCollide(const Shape* in_shape)const
{
	return in_shape->IsCollide(this);
}

//=============================================================================
// is collide
//=============================================================================
bool Point::IsCollide(const Point* in_point)const
{
	return false;
}

} // namespace shape
} // namespace common

//---------------------------------- EOF --------------------------------------
