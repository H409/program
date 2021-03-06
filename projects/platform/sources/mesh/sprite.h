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
#include "mesh.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace mesh {
class Sprite : public Mesh
{
public:
	// constructor
	Sprite(void);
	explicit Sprite(const float2& in_size);
	Sprite(const f32& in_width,const f32& in_height);

	// destructor
	virtual ~Sprite(void);

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

private:
	struct VERTEX
	{
		float3 _position;
		float2 _texcoord;
		D3DCOLOR _color;
	};

	static const float2 DEFAULT_SIZE;
	static const float4 DEFAULT_COLOR;
	static const float2 DEFAULT_ANCHOR_POINT;
	static const D3DVERTEXELEMENT9 VERTEXELEMENTS[];

	float2 anchor_point_;
	float2 size_;
	u32 index_;
	u32 division_width_;
	u32 division_height_;
	float4 texcoord_;

	const D3DVERTEXELEMENT9* GetVertexElements_(void)const override;
	// update vertex buffer
	void UpdateVertexBuffer_(void)override;
};

} // namespace mesh

#endif // _SPRITE_H_

//---------------------------------- EOF --------------------------------------
