//*****************************************************************************
//
// sprite 3D
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SPRITE_3D_H_
#define _SPRITE_3D_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "mesh.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace mesh {
class Sprite3D : public Mesh
{
public:
	// constructor
	Sprite3D(void);
	Sprite3D(const float2& in_size);

	// destructor
	virtual ~Sprite3D(void);

	// set anchor point
	void SetAnchorPoint(const float2& in_anchor_point);

	// set color
	void SetColor(const float4& in_color);

	// accsessor
	void __size(const float2& in_size) { size_ = in_size; }
	void __color(const float4& in_color) { color_ = in_color; }
	void __index(const u32& in_index) { index_ = in_index; }
	void __division_width(const u32& in_division_width) { division_width_ = in_division_width; }
	void __division_height(const u32& in_division_height) { division_height_ = in_division_height; }

protected:

private:
	static const float2 DEFAULT_SIZE;
	static const float4 DEFAULT_COLOR;
	static const float2 DEFAULT_ANCHOR_POINT;

	float2 anchor_point_;
	float2 size_;
	float4 color_;
	u32 index_;
	u32 division_width_;
	u32 division_height_;
};

} // namespace mesh

#endif // _SPRITE_H_

//---------------------------------- EOF --------------------------------------
