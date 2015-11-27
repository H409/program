//*****************************************************************************
//
// player icon
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _PLAYER_ICON_H_
#define _PLAYER_ICON_H_

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
class PlayerIcon// : public MeshObject
{
public:
	using TSprite3D = std::shared_ptr<mesh::Sprite3D>;
	using TMeshObject = std::shared_ptr<MeshObject>;

	// constructor
	PlayerIcon(u32 in_number);

	// destructor
	virtual ~PlayerIcon(void);

	// update
	void Update(void);

	// get object
	TMeshObject GetObject(void)const;

	// set position
	void SetPosition(const float3& in_position);

private:
	float3 position_;
	f32 height_;
	u32 number_;
	TSprite3D sprite_3d_;
	TMeshObject mesh_object_;
};

#endif // _PLAYER_ICON_H_

//---------------------------------- EOF --------------------------------------
