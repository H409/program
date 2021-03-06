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

	//初期化
	virtual bool Initialize(SceneManager* p_scene_manager) = 0;
	//終了
	virtual void Finalize(void) = 0;
	//更新
	virtual void Update(void) = 0;
	//描画
	virtual void Draw(void) = 0;

private:

};

#endif