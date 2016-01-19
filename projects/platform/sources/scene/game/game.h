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
class Observer3D;
class ResultObserver;
class FollowerObserver;
class MeshObject;
class Flower;
class Score;
class FBXObject;
class Timer;
class FBXTree;
class ResultTeamIcon;
class GameTimer;
class WeaponIcon;
class ResultWinLogo;
class Effect;
class TreeCreater;

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

	enum class WIN_TEAM
	{
		RED = 0,
		BLUE,
		DRAW,
		NONE,
	};

	//リザルト表示の状態遷移
	enum class RESULT_STATE
	{
		TWOTEAM = 0,	//両チームのチームロゴとスコアを表示
		TEAMMOVE,		//勝ちチームのチームロゴとスコアが負け側を追い出すように移動
		WINLOGO,		//勝ちチームのチームロゴとスコア、勝利UIを表示する
		BACKGROUND,		//2Dの表示をすべて排除してバックグラウンドのみの表示に変更
		NONE,			//リザルト画面を表示していない
	};

private:
	static const u32 PLAYER_MAX = 4;
	u32 player_num ;
	static const u32 WALL_MAX = 4;
	static const u32 FBX_OBJECT_MAX = 10;

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
	std::shared_ptr<ResultWinLogo>result_winlogo_;
	std::shared_ptr<GameTimer> game_timer_;
	std::shared_ptr<WeaponIcon>weapon_icon_;
	std::shared_ptr<Cylinder> cylinder_;
	std::shared_ptr<Observer2D> observer_2d_;
	std::vector<std::shared_ptr<Flower>> flowers_;
	std::unique_ptr<utility::culling::FrustumCulling> frustum_culling_;

	std::list<std::weak_ptr<Flower>> flower_list_;

	std::unique_ptr<Timer> timer_;

	std::shared_ptr<FBXObject> field_object_ ;

	std::shared_ptr<MeshObject> sprite_3D_[ 4 ] ;
	std::list<std::shared_ptr<FBXTree>> tree_list_;

	//result関連
	bool is_result_;									//リザルト画面表示をするかしないか
	WIN_TEAM is_win_team_;								//勝ったチーム
	RESULT_STATE result_state;							//リザルトの状態
	std::shared_ptr<Score> score_;						//得点表示
	std::shared_ptr<ResultTeamIcon> result_team_icon;	//チームのアイコン
	std::shared_ptr<ResultObserver> result_observer;	//リザルトにてフィールドを映す為のカメラ

	//std::list<std::shared_ptr<>> effect_list_;
	std::list<std::shared_ptr<Effect>> effect_list_;

#ifdef _DEBUG
	std::shared_ptr<MeshObject> debug_sprite_object_;
	std::shared_ptr<MeshObject> debug_object_;
	u32 debug_player_number_;
	bool debugRenderTarget_;
#endif

	u32 GetPoint(u32 player_number)const;
	void UpdateFieldObject(void);
	bool CheckGrowTree(u32 in_x,u32 in_y,u32 in_type);
	std::unordered_map<u32,std::shared_ptr<TreeCreater>> tree_creater_map_;
};

#endif