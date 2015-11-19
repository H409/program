//*****************************************************************************
//
// bullet
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

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
class Bullet// : public MeshObject
{
public:
	using TSprite3D = std::shared_ptr<mesh::Sprite3D>;
	using TMeshObject = std::shared_ptr<MeshObject>;

	enum class TYPE
	{
		NONE = -1,
		SEED,
		MAX,
	};

	// constructor
	Bullet(const float3& in_start_position,const float3& in_end_position,const TYPE in_type = TYPE::SEED);

	// destructor
	virtual ~Bullet(void);

	// update
	void Update(void);

	// remove
	void Remove(void);

	// is death
	bool IsDeath(void)const;

	// set tag
	void SetTag(const u32 in_tag);

	// get object
	TMeshObject GetObject(void)const;

	// get position
	const float3& GetPosition(void)const;

	// get type
	const TYPE& GetType(void)const;

	// get tag
	const u32& GetTag(void)const;
private:
	static const f32 GRAVITY;

	float3 position_;
	float3 start_position_;
	float3 end_position_;
	float3 move_;
	TSprite3D sprite_3d_;
	TMeshObject mesh_object_;
	TYPE type_;
	u32 tag_;
	bool is_death_;
};

#endif // _BULLET_H_

//---------------------------------- EOF --------------------------------------
