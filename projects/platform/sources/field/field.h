//*****************************************************************************
//
// field
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _FIELD_H_
#define _FIELD_H_

//*****************************************************************************
// include
//*****************************************************************************
//#include "../mesh_object.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace mesh {
class MeshSprite3D;
} // namespace mesh
class MeshObject;

//*****************************************************************************
// class declaration
//*****************************************************************************
class Field
{
public:
	using TMeshSprite3D = std::shared_ptr<mesh::MeshSprite3D>;
	using TMeshObject = std::shared_ptr<MeshObject>;

	// constructor
	Field(void);

	// destructor
	virtual ~Field(void);

	// update
	void Update(void);

	// reset
	void Reset(void);

	// get object
	TMeshObject GetObject(void)const;

	// is in range
	bool IsInRange(const float3& in_position)const;

	// select block
	void SelectBlock(const float3& in_position);

	//
	void NotSelectBlock(void);

	// get block position
	float3 GetBlockPosition(const float3& in_position);

	u32 GetBlockIndex(const float3& in_position);

	// get positions
	std::vector<float3> GetPositionsF(const u32& in_type);
	std::vector<float3> GetPositionsT(const u32& in_type);

	// set type
	void SetType(const float3& in_position,const u32& in_type);
	void SetType(const u32& in_x,const u32& in_y,const u32& in_type);

	// get type
	u32 GetType(const float3& in_position)const;

	// check type
	bool CheckType(const u32& in_x,const u32& in_y,const u32& in_type);
	bool CheckTypeLeftTop(const u32& in_x,const u32& in_y,const u32& in_type);
	bool CheckTypeLeftBottom(const u32& in_x,const u32& in_y,const u32& in_type);
	bool CheckTypeRightTop(const u32& in_x,const u32& in_y,const u32& in_type);
	bool CheckTypeRightBottom(const u32& in_x,const u32& in_y,const u32& in_type);

private:
	static const float4 DEFAULT_COLOR;
	static const float4 SELECT_COLOR;

	f32 block_width_;
	f32 block_height_;
	u32 width_count_;
	u32 height_count_;
	float2 size_;
	std::vector<u32> types_;
	u32 select_index_x_;
	u32 select_index_y_;
	TMeshSprite3D mesh_sprite_3d_;
	TMeshObject mesh_object_;
};

#endif // _FIELD_H_

//---------------------------------- EOF --------------------------------------
