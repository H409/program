//*****************************************************************************
//
// game_score
//
// Author		: Eyuu Yuminaga
//
// �Q�[�����ɕ\��������X�R�A�N���X
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

#define SCORE_DIGIT (3)		//�X�R�A�\���̌���

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

	//reset:���U���g�𔲂��鎞�ɌĂ�
	void Reset(void);

	//0:�ԁ@1:�� 
	void SetScore(int team, int num) { team_score_[team] = num; }

private:

	int team_score_[(unsigned int)TEAM::MAX];	//�e�`�[���̓��_

	float2 num_size_;
	float3 num_pos_[(unsigned int)TEAM::MAX][SCORE_DIGIT];
	TSprite num_sprite_[(unsigned int)TEAM::MAX][SCORE_DIGIT];		//���_���l�X�v���C�g
	TMeshObject num_object_[(unsigned int)TEAM::MAX][SCORE_DIGIT];	//���_���l�I�u�W�F�N�g
	unsigned int digit_num_[(unsigned int)TEAM::MAX][SCORE_DIGIT];	//���̔ԍ�
};

#endif

//---------------------------------- EOF --------------------------------------