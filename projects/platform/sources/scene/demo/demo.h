//*****************************************************************************
//
// demo.h
//
// Author		: Masahiro Yamaguchi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DEMO_H_
#define _DEMO_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "../base/scene_base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************


//*****************************************************************************
// class definition
//*****************************************************************************
class Demo : public SceneBase
{
public:
	// コンストラクタ
	Demo();

	// デストラクタ
	virtual ~Demo();

	// シーンの初期化。
	virtual bool Initialize(SceneManager* p_scene_manager) override;

	// シーンの終了処理。
	virtual void Finalize(void) override;

	// 更新処理を行う。
	virtual void Update(void) override;

	// 描画処理を行う。
	virtual void Draw(void) override;
private:

};

#endif