//*****************************************************************************
//
// result_score
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_


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

#define SCORE_DIGIT (3)		//スコア表示の桁数

//*****************************************************************************
// class declaration
//*****************************************************************************
class Score
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
	Score(void);

	//destructor
	virtual ~Score(void);

	// update
	void Update(void);

	//draw
	void Draw(void);

	//reset:リザルトを抜ける時に呼ぶ
	void Reset(void);

	//GetSprite3D
	TSprite GetSprite(int i) { return back_ground_sprite_[i]; }

	//GetObject
	TMeshObject GetObject(int i) { return back_ground_mesh_object_[i]; }

	//SetState
	void SetState(STATE in_state) { state_ = in_state; }

	//GetState
	STATE GetState(void) { return state_; }

	//0:赤 1:青 2:引き分け
	void SetWinTeam(int i) { win_team_ = (TEAM)i; }

	//0:赤　1:青 
	void SetScore(int team, int num) { score[team] = num; }

private:

	int score[(unsigned int)TEAM::MAX];	//得点

	float2 back_ground_size_;
	float3 back_ground_pos_[(unsigned int)TEAM::MAX];
	TSprite back_ground_sprite_[(unsigned int)TEAM::MAX];			//得点背景スプライト
	TMeshObject back_ground_mesh_object_[(unsigned int)TEAM::MAX];	//得点背景オブジェクト

	float2 num_size_;
	float3 num_pos_[(unsigned int)TEAM::MAX][SCORE_DIGIT];
	TSprite num_sprite_[(unsigned int)TEAM::MAX][SCORE_DIGIT];		//得点数値スプライト
	TMeshObject num_object_[(unsigned int)TEAM::MAX][SCORE_DIGIT];	//得点数値オブジェクト
	unsigned int digit_num_[(unsigned int)TEAM::MAX][SCORE_DIGIT];	//桁の番号


	float2 moved_pos_win;					//移動後のポジション
	float2 moved_pos_lose_red;
	float2 moved_pos_lose_blue;
	int moving_easingtime;							//線形補間で要する時間
	int easingcount;								//線形補間カウント
	STATE state_;									//ステータス
	TEAM win_team_;									//勝ったチーム
};

#endif

//---------------------------------- EOF --------------------------------------