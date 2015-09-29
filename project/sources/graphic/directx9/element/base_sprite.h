//*****************************************************************************
//
// base sprite
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_SPRITE_H_
#define _BASE_SPRITE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base_element.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace element
{
class BaseSprite : public BaseElement
{
public:
	// destructor
	virtual ~BaseSprite(void);

	// accsessor
	void __point(const float2& in_point) { point_ = in_point; }
	void __size(const float2& in_size) { size_ = in_size; }
	void __color(const float4& in_color) { color_ = in_color; }
	void __index(const u32& in_index) { index_ = in_index; }
	void __division_width(const u32& in_division_width) { division_width_ = in_division_width; }
	void __division_height(const u32& in_division_height) { division_height_ = in_division_height; }

protected:
	// constructor
	BaseSprite(void);

private:
	float2 point_;
	float2 size_;
	float4 color_;
	u32 index_;
	u32 division_width_;
	u32 division_height_;

};

} // namespace element
} // namespace base
} // napaspace graphic

#endif // _BASE_SPRITE_H_

//---------------------------------- EOF --------------------------------------
