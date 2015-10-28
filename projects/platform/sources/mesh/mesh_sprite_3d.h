//*****************************************************************************
//
// mesh sprite 3D
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MESH_SPRITE_3D_H_
#define _MESH_SPRITE_3D_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "mesh.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace mesh {
class MeshSprite3D : public Mesh
{
public:
	// constructor
	MeshSprite3D(const u32& in_width_count,const u32& in_height_count);
	MeshSprite3D(const f32& in_block_width,const f32& in_block_height,const u32& in_width_count,const u32& in_height_count);

	// destructor
	virtual ~MeshSprite3D(void);

	// set parameter
	void SetParameter(void);

	// set index
	void SetIndex(u32 x,u32 y,u32 index);

	// accessor
	void __index(const s32& index) { index_ = index; }
	void __division_width(const u32& division_width) { division_width_ = division_width; }
	void __division_height(const u32& division_height) { division_height_ = division_height; }
	bool __is_flip(void)const { return is_flip_; }
	void __is_flip(bool is_flip) { is_flip_ = is_flip; }
	void __width(f32 width) { width_ = width; }
	void __height(f32 height) { height_ = height; }
private:
	struct VERTEX
	{
		float3 _position;
		float2 _texcoord;
	};
	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const D3DCOLOR DEFAULT_COLOR;
	static const D3DXVECTOR2 DEFAULT_POSITION;

	D3DCOLOR color_;
	s32 index_;
	bool is_flip_;

	f32 width_;
	f32 height_;
	u32 width_count_;
	u32 height_count_;
	u32 division_width_;
	u32 division_height_;
	u32 index_count_;
	u32* indexs_;
};

} // namespace mesh
#endif	// _MESH_SPRITE_3D_H_

//---------------------------------- EOF --------------------------------------
