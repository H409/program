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
	// �R���X�g���N�^
	Game();

	// �f�X�g���N�^
	virtual ~Game();

	// �V�[���̏������B
	virtual bool Initialize(SceneManager* p_scene_manager) override;

	// �V�[���̏I�������B
	virtual void Finalize(void) override;

	// �X�V�������s���B
	virtual void Update(void) override;

	// �`�揈�����s���B
	virtual void Draw(void) override;

	//���U���g�V�[���̍X�V���s���B
	void UpdateResult(void);

	//���U���g�V�[���̕`����s���B
	void DrawResult(void);

	enum class WIN_TEAM
	{
		RED = 0,
		BLUE,
		DRAW,
		NONE,
	};

	//���U���g�\���̏�ԑJ��
	enum class RESULT_STATE
	{
		TWOTEAM = 0,	//���`�[���̃`�[�����S�ƃX�R�A��\��
		TEAMMOVE,		//�����`�[���̃`�[�����S�ƃX�R�A����������ǂ��o���悤�Ɉړ�
		WINLOGO,		//�����`�[���̃`�[�����S�ƃX�R�A�A����UI��\������
		BACKGROUND,		//2D�̕\�������ׂĔr�����ăo�b�N�O���E���h�݂̂̕\���ɕύX
		NONE,			//���U���g��ʂ�\�����Ă��Ȃ�
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

	//result�֘A
	bool is_result_;									//���U���g��ʕ\�������邩���Ȃ���
	WIN_TEAM is_win_team_;								//�������`�[��
	RESULT_STATE result_state;							//���U���g�̏��
	std::shared_ptr<Score> score_;						//���_�\��
	std::shared_ptr<ResultTeamIcon> result_team_icon;	//�`�[���̃A�C�R��
	std::shared_ptr<ResultObserver> result_observer;	//���U���g�ɂăt�B�[���h���f���ׂ̃J����

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