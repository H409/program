//*****************************************************************************
//
// mesh wall
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MESH_WALL_H_
#define _MESH_WALL_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "mesh.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace mesh {
class MeshWall :public Mesh
{
public:
	// constructor
	MeshWall(const u32& in_width_count, const u32& in_height_count);
	MeshWall(const f32& in_block_width, const f32& in_block_height, const u32& in_width_count, const u32& in_height_count);
	//destructor
	virtual ~MeshWall(void);

	// set index
	void SetIndex(u32 in_x, u32 in_y, u32 in_index);
	//void SetIndex(const std::vector<u32>& in_indexs);

	//// set color
	//void SetColor(u32 in_x, u32 in_y, const float4& in_color);

	//// set texcoord
	//void SetTexcoord(u32 in_division_width, u32 in_division_height);

private:
	struct VERTEX
	{
		float3 _position;
		float2 _texcoord;
		float3 _normal;
		D3DCOLOR _color;
	};

	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const D3DCOLOR DEFAULT_COLOR;
	static const D3DXVECTOR2 DEFAULT_POSITION;

	s32 index_;

	float2 size_;
	float2 block_size_;
	u32 width_count_;
	u32 height_count_;
	u32 division_width_;
	u32 division_height_;
	u32 index_count_;
	u32* indexs_;
	float2 anchor_point_;

	void AttachRenderState_(void)override;
	void DetachRenderState_(void)override;
	void UpdateVertexBuffer_(void)override;

};
} // namespace mesh

#endif//_MESH_WALL_H_

//---------------------------------- EOF --------------------------------------
