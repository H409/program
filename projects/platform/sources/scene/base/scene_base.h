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

	//èâä˙âª
	virtual bool Initialize(SceneManager* p_scene_manager) = 0;
	//èIóπ
	virtual void Finalize(void) = 0;
	//çXêV
	virtual void Update(void) = 0;
	//ï`âÊ
	virtual void Draw(void) = 0;

private:

};

#endif