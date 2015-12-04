//*****************************************************************************
//
// field
//
// Author		: Eyu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DOME_H_
#define _DOME_H_

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace mesh {
class MeshDome;
} // namespace mesh
class MeshObject;

//*****************************************************************************
// class declaration
//*****************************************************************************
class Dome
{
public:
	using TMeshDome = std::shared_ptr<mesh::MeshDome>;
	using TMeshObject = std::shared_ptr<MeshObject>;

	// constructor
	Dome(void);

	// destructor
	virtual ~Dome(void);

	// update
	void Update(void);

	// reset
	void Reset(void);

	// get object
	TMeshObject GetObject(void)const;

	// is in range
	bool IsInRange(const float3& in_position)const;

	u32 GetBlockIndex(const float3& in_position);

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
	TMeshDome mesh_sprite_dome_;
	TMeshObject mesh_object_;
};

#endif