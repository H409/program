//*****************************************************************************
//
// title.h
//
// Author		: Masahiro Yamaguchi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "../base/scene_base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Observer2D;
class MeshObject;

//*****************************************************************************
// class definition
//*****************************************************************************
class Title : public SceneBase
{
public:

	// �R���X�g���N�^
	Title();

	// �f�X�g���N�^
	virtual ~Title();

	// �V�[���̏������B
	virtual bool Initialize(SceneManager* p_scene_manager) override;

	// �V�[���̏I�������B
	virtual void Finalize(void) override;

	// �X�V�������s���B
	virtual void Update(void) override;

	// �`�揈�����s���B
	virtual void Draw(void) override;
private:

	std::shared_ptr<Observer2D> observer_2d_;
	std::shared_ptr<MeshObject> background_;
	std::shared_ptr<MeshObject> logo_;
	std::shared_ptr<MeshObject> button_;
};

#endif