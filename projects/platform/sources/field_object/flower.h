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

	enum class TYPE
	{
		SPROUT,
		FLOWER,
	};
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

	void Show(void);

	void Hide(void);

	void Death(void);

	void SetNumber(u32 in_number);

	void SetIsGrowth(bool in_is_growth);

	void SetTreeIndex(u32 in_index);

	bool IsGrowthTree(void)const;

	bool IsShow(void)const;

	bool IsLive(void)const;

	u32 GetNumber(void)const;

	u32 GetTreeIndex(void)const;

	bool IsTreeCreate(void)const;

	bool IsGrowing(void)const;

	void SetGrow(void);
private:
	float3 position_;
	TSprite3D sprite_3d_;
	TMeshObject mesh_object_;
	bool is_show_;
	float height_;
	bool is_live_;
	u32 number_;
	u32 time_count_;
	TYPE type_;
	bool is_growth_;
	u32 tree_index_;
	bool is_growing_;

	void SetTexture(u32 in_number);
};

#endif // _FLOWER_H_

//---------------------------------- EOF --------------------------------------
