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

//*****************************************************************************
// class definition
//*****************************************************************************
class Result : public SceneBase
{
public:
	// コンストラクタ
	Result();

	// デストラクタ
	virtual ~Result();

	// シーンの初期化。
	virtual bool Initialize(SceneManager* p_scene_manager) override;

	// シーンの終了処理。
	virtual void Finalize(void) override;

	// 更新処理を行う。
	virtual void Update(void) override;

	// 描画処理を行う。
	virtual void Draw(void) override;
private:
	static const u32 PLAYER_MAX = 4;

	std::shared_ptr<Player> players_[PLAYER_MAX];	//プレイヤー
	std::shared_ptr<Field> field_;					//フィールド
	//得点表示
	//シーン遷移用カウントダウン
	//カメラ

};

#endif