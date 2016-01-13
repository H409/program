//*****************************************************************************
//
// weapon_icon
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _WEAPON_ICON_H_
#define _WEAPON_ICON_H_


//*****************************************************************************
// include
//*****************************************************************************


//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace mesh {
	class Sprite;
}	//namespace mesh
class MeshObject;

#define PLAYER_SUM (4)
#define WEAPON_SUM (3)


//*****************************************************************************
// class declaration
//*****************************************************************************
class WeaponIcon
{
public:
	using TSprite = std::shared_ptr<mesh::Sprite>;
	using TMeshObject = std::shared_ptr<MeshObject>;

	enum class TEAM
	{
		RED = 0,
		BLUE,
		MAX
	};

	// constructor
	WeaponIcon(void);

	//destructor
	virtual ~WeaponIcon(void);

	// update
	void Update(void);

	//draw
	void Draw(void);

	void SetWeaponUsing(int id, int weapon) { weapon_using[id] = weapon; }

	////GetSprite3D
	//TSprite GetSprite(int i) { return back_ground_sprite_; }

	////GetObject
	//TMeshObject GetObject(int i) { return back_ground_mesh_object_; }

private:
	float2 icon_size_;
	float2 icon_size_big;
	float3 icon_pos_[WEAPON_SUM][PLAYER_SUM];
	TSprite icon_sprite_[WEAPON_SUM][PLAYER_SUM];		//武器アイコンスプライト
	TMeshObject icon_object_[WEAPON_SUM][PLAYER_SUM];	//武器アイコンオブジェクト
	int weapon_using[PLAYER_SUM];

											/*void Reset(void);
											u32 GetTimeLeft(void)const;*/
};

#endif

//---------------------------------- EOF --------------------------------------