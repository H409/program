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
class Field// : public MeshObject
{
public:
	using TMeshSprite3D = std::shared_ptr<mesh::MeshSprite3D>;
	using TMeshObject = std::shared_ptr<MeshObject>;

	// constructor
	Field(void);

	// destructor
	virtual ~Field(void);

	// get object
	TMeshObject GetObject(void)const;

	// is in range
	bool IsInRange(const float3& in_position)const;

	// get type
	u32 GetType(const float3& in_position)const;

private:
	f32 block_width_;
	f32 block_height_;
	u32 width_count_;
	u32 height_count_;
	float2 size_;
	std::vector<u32> types_;

	TMeshSprite3D mesh_sprite_3d_;
	TMeshObject mesh_object_;
};

#endif // _FIELD_H_

//---------------------------------- EOF --------------------------------------
