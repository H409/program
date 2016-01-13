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
// struct definition
//*****************************************************************************
typedef struct _PARTICUL
{
	std::shared_ptr<MeshObject> particul_;
	float particul_angle_;
	int start_cnt_;
	bool start_flag_;
}PARTICUL;

//*****************************************************************************
// class definition
//*****************************************************************************
class Title : public SceneBase
{
public:

	//マクロ定義
	static const int PARTICUL_MAX = 60;

	// コンストラクタ
	Title();

	// デストラクタ
	virtual ~Title();

	// シーンの初期化。
	virtual bool Initialize(SceneManager* p_scene_manager) override;

	// シーンの終了処理。
	virtual void Finalize(void) override;

	// 更新処理を行う。
	virtual void Update(void) override;

	// 描画処理を行う。
	virtual void Draw(void) override;
private:

	std::shared_ptr<Observer2D> observer_2d_;
	std::shared_ptr<MeshObject> background_;
	std::shared_ptr<MeshObject> logo_;
	std::shared_ptr<MeshObject> button_;
	std::shared_ptr<MeshObject> button_interface_;
	PARTICUL particul_[PARTICUL_MAX];

	//とりあえずゴリ押し
	int  draw_cnt_;
	bool use_flag_;
	
	int particul_cnt_;
};

#endif