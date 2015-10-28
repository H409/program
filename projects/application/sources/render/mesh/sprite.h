//*****************************************************************************
//
// sprite
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base_mesh_creater.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic {
namespace vertex {
class VertexBuffer;
} // namespace vertex
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace render {
namespace mesh {
class Sprite : public BaseMeshCreater
{
public:
	// constructor
	Sprite(void);
	Sprite(const float2& in_size);
	Sprite(const float2& in_size,const float4& in_color);
	Sprite(const TFormat& in_format);

	// destructor
	virtual ~Sprite(void);

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
} // napaspace render

#endif // _SPRITE_H_

//---------------------------------- EOF --------------------------------------
