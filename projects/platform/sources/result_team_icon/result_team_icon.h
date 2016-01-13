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

	enum class STATE
	{
		NEUTRAL = 0,
		MOVE,
		MOVED,
	};

	// constructor
	ResultTeamIcon(void);

	//destructor
	virtual ~ResultTeamIcon(void);

	// update
	void Update(void);

	//draw
	void Draw(void);

	//Reset
	void Reset(void);

	//GetSprite3D
	TSprite GetSprite(int i) { return sprite_[i]; }

	//SetState
	void SetState(STATE in_state) { state_ = in_state; }

	//GetState
	STATE GetState(void) { return state_; }

	//0:�ԁ@1:�� 2:��������
	void SetWinTeam(int i) { win_team_ = (TEAM)i; }

private:
	float2 size_;
	TSprite sprite_[(unsigned int)TEAM::MAX];		//�A�C�R���\���X�v���C�g
	TMeshObject object_[(unsigned int)TEAM::MAX];	//�A�C�R���\���I�u�W�F�N�g
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