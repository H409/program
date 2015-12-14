//*****************************************************************************
//
// wall
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _WALL_H_
#define _WALL_H_


//*****************************************************************************
// include
//*****************************************************************************


//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace mesh {
	class Sprite3D;
}	//namespace mesh
class MeshObject;

//*****************************************************************************
// class declaration
//*****************************************************************************
class Wall
{
public:
	using TSprite3D = std::shared_ptr<mesh::Sprite3D>;
	using TMeshObject = std::shared_ptr<MeshObject>;

	// constructor
	Wall(void) {};
	Wall(float2 size);

	//destructor
	virtual ~Wall(void);

	// update
	void Update(void);

	//GetSprite3D
	TSprite3D GetSprite3D(void) { return sprite_3d_; }

	// get object
	TMeshObject GetObject(void)const;

private:

	f32 block_width_;
	f32 block_height_;
	u32 width_count_;
	u32 height_count_;
	float2 size_;
	TSprite3D sprite_3d_;
	TMeshObject mesh_object_;
};

#endif

//---------------------------------- EOF --------------------------------------