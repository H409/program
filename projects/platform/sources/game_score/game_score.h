//*****************************************************************************
//
// game_score
//
// Author		: Eyuu Yuminaga
//
// ゲーム中に表示させるスコアクラス
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GAME_SCORE_H_
#define _GAME_SCORE_H_


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
class GameScore
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
	GameScore(void);

	//destructor
	virtual ~GameScore(void);

	// update
	void Update(void);

	//draw
	void Draw(void);

	//reset:リザルトを抜ける時に呼ぶ
	void Reset(void);

	//0:赤　1:青 
	void SetScore(int team, int num) { team_score_[team] = num; }

private:

	int team_score_[(unsigned int)TEAM::MAX];	//各チームの得点

	float2 num_size_;
	float3 num_pos_[(unsigned int)TEAM::MAX][SCORE_DIGIT];
	TSprite num_sprite_[(unsigned int)TEAM::MAX][SCORE_DIGIT];		//得点数値スプライト
	TMeshObject num_object_[(unsigned int)TEAM::MAX][SCORE_DIGIT];	//得点数値オブジェクト
	unsigned int digit_num_[(unsigned int)TEAM::MAX][SCORE_DIGIT];	//桁の番号
};

#endif

//---------------------------------- EOF --------------------------------------