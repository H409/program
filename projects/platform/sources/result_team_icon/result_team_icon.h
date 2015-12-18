//*****************************************************************************
//
// result_team_icon
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _RESULT_TEAM_ICON_H_
#define _RESULT_TEAM_ICON_H_


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

//*****************************************************************************
// class declaration
//*****************************************************************************
class ResultTeamIcon
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
	ResultTeamIcon(void);

	//destructor
	virtual ~ResultTeamIcon(void);

	// update
	void Update(void);

	//draw
	void Draw(void);

	//GetSprite3D
	TSprite GetSprite(int i) { return sprite_[i]; }

private:
	float2 size_;
	TSprite sprite_[(unsigned int)TEAM::MAX];		//アイコン表示スプライト
	TMeshObject object_[(unsigned int)TEAM::MAX];	//アイコン表示オブジェクト
};

#endif

//---------------------------------- EOF --------------------------------------