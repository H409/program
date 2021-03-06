//*****************************************************************************
//
// shape
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "shape.h"

namespace common
{
namespace shape
{

//=============================================================================
// constructor
//=============================================================================
Shape::Shape(const TYPE& in_type)
	:type_(in_type)
	,position_(0.0f,0.0f,0.0f)
{
}

//=============================================================================
// constructor
//=============================================================================
Shape::Shape(const TYPE& in_type,const float3& in_position)
	:type_(in_type)
	,position_(in_position)
{
}

//=============================================================================
// destructor
//=============================================================================
Shape::~Shape(void)
{
}

} // namespace shape
} // namespace common

//---------------------------------- EOF --------------------------------------
