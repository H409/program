//*****************************************************************************
//
// scene_manager.h
//
// Author		: Masahiro Yamaguchi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

//*****************************************************************************
// forward declaration
//*****************************************************************************
class SceneBase;
class SceneFactory;
class Title;
class Demo;
class Tutorial;
class Game;
class Result;

//*****************************************************************************
// class definition
//*****************************************************************************
class SceneManager
{
public:

	//スマートポインタ用
	using TBase = std::shared_ptr<SceneBase>;
	using TTitle = std::shared_ptr<Title>;
	using TTutorial = std::shared_ptr<Tutorial>;
	using TDemo = std::shared_ptr<Demo>;
	using TGame = std::shared_ptr<Game>;
	using TResult = std::shared_ptr<Result>;

	

	//インスタンス
	static SceneManager& Instance(void)
	{
		static SceneManager instance;
		return instance;
	}

	// シーンの更新をする。
	void Update(void);

	// シーンの描画をする。
	void Draw(void);


	// アクセサ
	TBase p_next_scene(void) const
	{
		return p_next_scene_;
	}

	// ミューテータ
	void set_p_current_scene(TBase p_current_scene)
	{
		p_current_scene_ = p_current_scene;
	}
	void set_p_next_scene(TBase p_next_scene)
	{
		p_next_scene_ = p_next_scene;
	}

	TTitle get_title(void)const
	{
		return p_title_;
	}
	TTutorial get_tutorial(void)const
	{
		return p_tutorial_;
	}
	TDemo get_demo(void)const
	{
		return p_demo_;
	}
	TGame get_game(void)const
	{
		return p_game_;
	}
	TResult get_result(void)const
	{
		return p_result_;
	}

	//シーン切替
	bool get_scene_change_flag(void)
	{
		return scene_change_flag_;
	}
	void set_scene_change_flag(const bool flag)
	{
		scene_change_flag_ = flag;
	}

	// dtor
	~SceneManager();

protected:

	

private:

	// ctor
	SceneManager();

	//各シーンのポインタ
	TTitle p_title_;
	TDemo p_demo_;
	TTutorial p_tutorial_;
	TGame p_game_;
	TResult p_result_;

	TBase p_current_scene_;
	TBase p_next_scene_;

	//シーン切り替えフラグ
	bool scene_change_flag_;
};

#endif