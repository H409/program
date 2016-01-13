//*****************************************************************************
//
// result_winlogo
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _RESULT_WINLOGO_H_
#define _RESULT_WINLOGO_H_


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
class ResultWinLogo
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

	enum class STATE
	{
		NEUTRAL = 0,
		MOVE,
		MOVED,
	};

	// constructor
	ResultWinLogo(void);

	//destructor
	virtual ~ResultWinLogo(void);

	// update
	void Update(void);

	//draw
	void Draw(void);

	//GetSprite3D
	TSprite GetSprite(void) { return sprite_; }

	//SetState
	void SetState(STATE in_state) { state_ = in_state; }

	//GetState
	STATE GetState(void) { return state_; }

	//0:赤　1:青 2:引き分け
	void SetWinTeam(int i) { win_team_ = (TEAM)i; }

private:
	float2 size_;
	TSprite sprite_;		//アイコン表示スプライト
	TMeshObject object_;	//アイコン表示オブジェクト
	float2 moved_pos_win;	//移動後のポジション
	STATE state_;			//ステータス
	TEAM win_team_;			//勝ったチーム

};

#endif

//---------------------------------- EOF --------------------------------------