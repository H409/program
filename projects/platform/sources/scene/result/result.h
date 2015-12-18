//*****************************************************************************
//
// result.h
//
// Author		: Masahiro Yamaguchi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "../base/scene_base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Player;
class Field;
class Score;

//*****************************************************************************
// class definition
//*****************************************************************************
class Result : public SceneBase
{
public:
	// �R���X�g���N�^
	Result();

	// �f�X�g���N�^
	virtual ~Result();

	// �V�[���̏������B
	virtual bool Initialize(SceneManager* p_scene_manager) override;

	// �V�[���̏I�������B
	virtual void Finalize(void) override;

	// �X�V�������s���B
	virtual void Update(void) override;

	// �`�揈�����s���B
	virtual void Draw(void) override;
private:
	std::shared_ptr<Score> score_;					//���_�\��
	//�V�[���J�ڗp�J�E���g�_�E��
	//�J����

};

#endif