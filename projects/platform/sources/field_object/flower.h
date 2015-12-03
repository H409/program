//*****************************************************************************
//
// flower
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _FLOWER_H_
#define _FLOWER_H_

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
class Flower// : public MeshObject
{
public:
	using TSprite3D = std::shared_ptr<mesh::Sprite3D>;
	using TMeshObject = std::shared_ptr<MeshObject>;

	// constructor
	Flower(u32 in_number);

	// destructor
	virtual ~Flower(void);

	// update
	void Update(void);

	// get object
	TMeshObject GetObject(void)const;

	// set position
	void SetPosition(const float3& in_position);

	// get position
	const float3& GetPosition(void)const;

	// 
	void Show(bool in_is_show);

	void SetNumber(u32 in_number);

	bool IsShow(void)const;

private:
	float3 position_;
	TSprite3D sprite_3d_;
	TMeshObject mesh_object_;
	bool is_show_;
	float height_;

	void SetTexture(u32 in_number);
};

#endif // _FLOWER_H_

//---------------------------------- EOF --------------------------------------
