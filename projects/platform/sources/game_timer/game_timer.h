//*****************************************************************************
//
// game_timer
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GAME_TIMER_H_
#define _GAME_TIMER_H_


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

#define TIMER_DIGIT (3)		//スコア表示の桁数

//*****************************************************************************
// class declaration
//*****************************************************************************
class GameTimer
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
	GameTimer(void);

	//destructor
	virtual ~GameTimer(void);

	// update
	void Update(void);

	//draw
	void Draw(void);

	//GetSprite3D
	TSprite GetSprite(int i) { return back_ground_sprite_; }

	//GetObject
	TMeshObject GetObject(int i) { return back_ground_mesh_object_; }

private:
	float2 back_ground_size_;
	float3 back_ground_pos_;
	TSprite back_ground_sprite_;			//時間背景スプライト
	TMeshObject back_ground_mesh_object_;	//時間背景オブジェクト

	float2 num_size_;
	float3 num_pos_[TIMER_DIGIT];
	TSprite num_sprite_[TIMER_DIGIT];		//時間数値スプライト
	TMeshObject num_object_[TIMER_DIGIT];	//時間数値オブジェクト
};

#endif

//---------------------------------- EOF --------------------------------------