//*****************************************************************************
//
// scene_base.h
//
// Author		: Masahiro Yamaguchi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_

//*****************************************************************************
// forward declaration
//*****************************************************************************
class SceneManager;
class SceneFactory;

//*****************************************************************************
// class definition
//*****************************************************************************
class SceneBase
{
public:
	//ctor
	SceneBase() {}

	//dtor
	virtual ~SceneBase() {}

	//������
	virtual bool Initialize(SceneManager* p_scene_manager) = 0;
	//�I��
	virtual void Finalize(void) = 0;
	//�X�V
	virtual void Update(void) = 0;
	//�`��
	virtual void Draw(void) = 0;

private:

};

#endif