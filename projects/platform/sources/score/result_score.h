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

	// constructor
	Score(void);

	//destructor
	virtual ~Score(void);

	// update
	void Update(void);

	//draw
	void Draw(void);

	//GetSprite3D
	TSprite GetSprite(int i) { return back_ground_sprite_[i]; }

	//GetObject
	TMeshObject GetObject(int i) { return back_ground_mesh_object_[i]; }

private:
	float2 back_ground_size_;
	float3 back_ground_pos_[(unsigned int)TEAM::MAX];
	TSprite back_ground_sprite_[(unsigned int)TEAM::MAX];			//���_�w�i�X�v���C�g
	TMeshObject back_ground_mesh_object_[(unsigned int)TEAM::MAX];	//���_�w�i�I�u�W�F�N�g

	float2 num_size_;
	float3 num_pos_[(unsigned int)TEAM::MAX][SCORE_DIGIT];
	TSprite num_sprite_[(unsigned int)TEAM::MAX][SCORE_DIGIT];		//���_���l�X�v���C�g
	TMeshObject num_object_[(unsigned int)TEAM::MAX][SCORE_DIGIT];	//���_���l�I�u�W�F�N�g
};

#endif

//---------------------------------- EOF --------------------------------------