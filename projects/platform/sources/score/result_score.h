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

#define SCORE_DIGIT (3)		//�X�R�A�\���̌���

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

	//reset:���U���g�𔲂��鎞�ɌĂ�
	void Reset(void);

	//GetSprite3D
	TSprite GetSprite(int i) { return back_ground_sprite_[i]; }

	//GetObject
	TMeshObject GetObject(int i) { return back_ground_mesh_object_[i]; }

	//SetState
	void SetState(STATE in_state) { state_ = in_state; }

	//GetState
	STATE GetState(void) { return state_; }

	//0:�� 1:�� 2:��������
	void SetWinTeam(int i) { win_team_ = (TEAM)i; }

	//0:�ԁ@1:�� 
	void SetScore(int team, int num) { score[team] = num; }

private:

	int score[(unsigned int)TEAM::MAX];	//���_

	float2 back_ground_size_;
	float3 back_ground_pos_[(unsigned int)TEAM::MAX];
	TSprite back_ground_sprite_[(unsigned int)TEAM::MAX];			//���_�w�i�X�v���C�g
	TMeshObject back_ground_mesh_object_[(unsigned int)TEAM::MAX];	//���_�w�i�I�u�W�F�N�g

	float2 num_size_;
	float3 num_pos_[(unsigned int)TEAM::MAX][SCORE_DIGIT];
	TSprite num_sprite_[(unsigned int)TEAM::MAX][SCORE_DIGIT];		//���_���l�X�v���C�g
	TMeshObject num_object_[(unsigned int)TEAM::MAX][SCORE_DIGIT];	//���_���l�I�u�W�F�N�g
	unsigned int digit_num_[(unsigned int)TEAM::MAX][SCORE_DIGIT];	//���̔ԍ�


	float2 moved_pos_win;					//�ړ���̃|�W�V����
	float2 moved_pos_lose_red;
	float2 moved_pos_lose_blue;
	int moving_easingtime;							//���`��Ԃŗv���鎞��
	int easingcount;								//���`��ԃJ�E���g
	STATE state_;									//�X�e�[�^�X
	TEAM win_team_;									//�������`�[��
};

#endif

//---------------------------------- EOF --------------------------------------