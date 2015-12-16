//*****************************************************************************
//
// game.h
//
// Author		: Masahiro Yamaguchi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "../base/scene_base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Bullet;
class Field;
class FieldIcon;
class Wall;
class Dome;
class Cylinder;
class Player;
class PlayerIcon;
class Observer2D;
class FollowerObserver;
class MeshObject;
class Flower;
class Score;
class FBXObject ;
class Timer;
class FBXTree ;

namespace utility {
namespace culling {
class FrustumCulling;
} // namespace utility
} // namespace culling

namespace graphic {
namespace directx9 {
namespace texture {
class DX9Texture;
} // namespace texture
} // namespace directx9
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
class Game : public SceneBase
{
public:
	// コンストラクタ
	Game();

	// デストラクタ
	virtual ~Game();

	// シーンの初期化。
	virtual bool Initialize(SceneManager* p_scene_manager) override;

	// シーンの終了処理。
	virtual void Finalize(void) override;

	// 更新処理を行う。
	virtual void Update(void) override;

	// 描画処理を行う。
	virtual void Draw(void) override;

	//リザルトシーンの更新を行う。
	void UpdateResult(void);

	//リザルトシーンの描画を行う。
	void DrawResult(void);
private:
	static const u32 PLAYER_MAX = 4;
	static const u32 WALL_MAX = 4;
	static const u32 FBX_OBJECT_MAX = 10 ;

	std::shared_ptr<Player> players_[PLAYER_MAX];
	std::shared_ptr<PlayerIcon> player_icons_[PLAYER_MAX];
	std::shared_ptr<FollowerObserver> observers_[PLAYER_MAX];
	std::shared_ptr<Field> field_;
	std::shared_ptr<FieldIcon> field_icons_[PLAYER_MAX];
	std::vector<std::shared_ptr<Bullet>> bullets_;
	std::shared_ptr<graphic::directx9::texture::DX9Texture> color_textures_[PLAYER_MAX];
	std::shared_ptr<graphic::directx9::texture::DX9Texture> normal_textures_[PLAYER_MAX];
	std::shared_ptr<graphic::directx9::texture::DX9Texture> position_textures_[PLAYER_MAX];
	std::shared_ptr<MeshObject> sprite_objects_[PLAYER_MAX];
	std::shared_ptr<Wall> wall_[WALL_MAX];
	std::shared_ptr<Dome> dome_;
	std::shared_ptr<Cylinder> cylinder_;
	std::shared_ptr<Observer2D> observer_2d_;
	std::vector<std::shared_ptr<Flower>> flowers_;
	std::unique_ptr<utility::culling::FrustumCulling> frustum_culling_;
	
	std::list<std::weak_ptr<Flower>> flower_list_;
	std::shared_ptr<FBXObject> fbx_object_[ FBX_OBJECT_MAX ];
	std::shared_ptr<FBXTree> fbx_tree_[ FBX_OBJECT_MAX ];

	std::unique_ptr<Timer> timer_;

	std::shared_ptr<MeshObject> sprite_3D_ ;


	//result関連
	bool result_flag_;								//リザルト画面表示をするかしないか
	std::shared_ptr<Score> score_;					//得点表示

#ifdef _DEBUG
	std::shared_ptr<MeshObject> debug_sprite_object_;
	std::shared_ptr<MeshObject> debug_object_;
	u32 debug_player_number_;
	bool debugRenderTarget_;
#endif

	u32 GetPoint(u32 player_number)const;


};

#endif