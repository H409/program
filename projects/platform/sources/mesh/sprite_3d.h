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
	explicit Sprite3D(const float2& in_size);

	// destructor
	virtual ~Sprite3D(void);

	// set size
	void SetSize(const float2& in_size);
	void SetSize(const f32& in_width,const f32& in_height);

	// set anchor point
	void SetAnchorPoint(const float2& in_anchor_point);

	// set texcoord
	void SetTexcoord(const float4& in_texcoord);
	void SetTexcoord(const f32& in_left,const f32& in_right,const f32& in_top,const f32& in_bottom);
	void SetTexcoord(const u32& in_index);
	void SetTexcoord(const u32& in_index,const u32& in_division_width,const u32& in_division_height);

protected:

private:
	struct VERTEX
	{
		float3 _position;
		float2 _texcoord;
		float3 _normal;
	};

	static const float2 DEFAULT_SIZE;
	static const float4 DEFAULT_COLOR;
	static const float2 DEFAULT_ANCHOR_POINT;

	float2 anchor_point_;
	float2 size_;
	u32 index_;
	u32 division_width_;
	u32 division_height_;

	float4 texcoord_;

	void UpdateVertexBuffer_(void)override;
};

} // namespace mesh

#endif // _SPRITE_H_

//---------------------------------- EOF --------------------------------------
