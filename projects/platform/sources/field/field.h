//*****************************************************************************
//
// field
//
// Author		: 
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
#define MESH 1

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace mesh {
#if MESH
class MeshSprite3D;
#else
class Sprite3D;
#endif
} // namespace mesh
class MeshObject;

//*****************************************************************************
// class declaration
//*****************************************************************************
class Field
{
public:
#if MESH
	using TMeshSprite3D = std::shared_ptr<mesh::MeshSprite3D>;
#else
	using TSprite3D = std::shared_ptr<mesh::Sprite3D>;
#endif
	using TMeshObject = std::shared_ptr<MeshObject>;

	enum class TYPE
	{
		NONE = -1,
		GRAVEL,
		GREEN_SPACE,
		STONE_PAVEMENT,
		SOIL,
		TREE,
		SHRINE,
		LANTERN,
		SHRINE_2,
		ROCK_2x2,
		ROCK_4x4,
		TREE_FLOWER,
		MAX,
	};
	// constructor
	Field(void);

	// destructor
	virtual ~Field(void);

	// update
	void Update(void);

	// reset
	void Reset(void);

	// load
	void Load(const std::string& in_path);

	// get object
	TMeshObject GetObject(void)const;

	// is in range
	bool IsInRange(const float3& in_position)const;

	// select block
	void SelectBlock(const float3& in_position);

	//
	void NotSelectBlock(void);

	const float2& GetSize(void) const;

	// get block position
	float3 GetBlockPosition(const float3& in_position);

	u32 GetBlockIndex(const float3& in_position);

	u32 GetBlockCount(void)const;

	u32 GetBlockCount(TYPE in_type);

	std::vector<u32> GetIndexs(TYPE in_type);

	// get positions
	std::vector<float3> GetPositionsF(const u32& in_type);
	std::vector<float3> GetPositionsT(const u32& in_type);

	// set type
	void SetType(const float3& in_position,TYPE in_type);
	void SetType(const u32& in_x,const u32& in_y,TYPE in_type);
	void SetType(u32 in_index,TYPE in_type);

	// get type
	TYPE GetType(const float3& in_position)const;
	TYPE GetType(u32 in_index)const;

	// 
	u32 CountType(u32 in_type);

	// check type
	bool CheckType(const u32& in_x,const u32& in_y,const u32& in_type);
	bool CheckTypeLeftTop(const u32& in_x,const u32& in_y,const u32& in_type);
	bool CheckTypeLeftBottom(const u32& in_x,const u32& in_y,const u32& in_type);
	bool CheckTypeRightTop(const u32& in_x,const u32& in_y,const u32& in_type);
	bool CheckTypeRightBottom(const u32& in_x,const u32& in_y,const u32& in_type);

	bool IsObstacle(TYPE in_type);

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
#if MESH
	TMeshSprite3D mesh_sprite_3d_;
#else
	TSprite3D sprite_3d_;
#endif
	TMeshObject mesh_object_;
};

#endif // _FIELD_H_

//---------------------------------- EOF --------------------------------------
