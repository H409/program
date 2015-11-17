//*****************************************************************************
//
// field icon
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _FIELD_ICON_H_
#define _FIELD_ICON_H_

//*****************************************************************************
// include
//*****************************************************************************
//#include "../mesh_object.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace mesh {
class Sprite3D;
} // namespace mesh
class MeshObject;

//*****************************************************************************
// class declaration
//*****************************************************************************
class FieldIcon// : public MeshObject
{
public:
	using TSprite3D = std::shared_ptr<mesh::Sprite3D>;
	using TMeshObject = std::shared_ptr<MeshObject>;

	// constructor
	FieldIcon(void);

	// destructor
	virtual ~FieldIcon(void);

	// update
	void Update(void);

	// get object
	TMeshObject GetObject(void)const;

	// set basic position
	void SetBasicPosition(const float3& in_position);

	// set front vector
	void SetFrontVector(const float3& in_front_vector);

	// get position
	const float3& GetPosition(void)const;

private:
	float3 position_;
	float3 basic_position_;
	f32 range_;
	f32 speed_;
	TSprite3D sprite_3d_;
	TMeshObject mesh_object_;
	float3 front_vector_;

	float3 GetVector_(void)const;
	bool IsOverRange_(void)const;
};

#endif // _FIELD_ICON_H_

//---------------------------------- EOF --------------------------------------
