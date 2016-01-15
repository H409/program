//*****************************************************************************
//
// game.cpp
//
// Author		: Masahiro Yamaguchi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "game.h"
#include "../title/title.h"
#include "system/win_system.h"
#include "system/input_keyboard.h"
#include "shader/dx9_vertex_shader.h"
#include "shader/dx9_pixel_shader.h"
#include "texture/dx9_texture.h"
#include "mesh/sprite.h"
#include "observer/observer_2d.h"
#include "observer/observer_3d.h"
#include "observer/result_observer.h"
#include "observer/follower_observer.h"
#include "mesh/sprite_3d.h"
#include "object/mesh_object.h"
#include "object/object.h"
#include "field/field.h"
#include "field_icon/field_icon.h"
#include "player/player.h"
#include "bullet/bullet.h"
#include "math/math.h"
#include "x_model/x_model.h"
#include "develop_tool/develop_tool.h"
#include "system/input_manager.h"
#include "player_icon/player_icon.h"
#include "field_object/flower.h"
#include "wall/wall.h"
#include "dome/dome.h"
#include "cylinder/cylinder.h"
#include "culling/frustum_culling.h"
#include "fbx_object/fbx_object.h"
#include "timer/timer.h"
#include "system/xi_pad.h"
#include "fbx_tree/fbx_tree.h"
#include "score/result_score.h"
#include "result_team_icon/result_team_icon.h"
#include "sound/sound.h"
#include "../base/scene_manager.h"
#include "game_timer/game_timer.h"
#include "weapon_icon/weapon_icon.h"
#include "result_winlogo/result_winlogo.h"
#include "effect/smoke.h"
#include "field_object/tree_creater.h"

//=============================================================================
// constructor
//=============================================================================
Game::Game()
{
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto window = GET_WINDOW();

	timer_ = std::make_unique<Timer>();

	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
		observers_[i] = std::make_shared<FollowerObserver>(utility::math::ToRadian(60.0f), window->GetWidth(), window->GetHeight());
		observers_[i]->SetTargetPosition(float3(0.0f, 0.0f, 0.0f));
		observers_[i]->SetTargetVector(float3(0.0f, 0.0f, 1.0f));
		observers_[i]->SetLength(2.0f);
		observers_[i]->SetHeight(1.5f);
		observers_[i]->SetState(FollowerObserver::STATE::NONE);
		observers_[i]->SetID(i);
		observers_[i]->Update();
	}

	observer_2d_ = std::make_shared<Observer2D>(window->GetWidth(), window->GetHeight());
	//result_observer = std::make_shared<Observer3D>(D3DX_PI/3,window->GetWidth(), window->GetHeight());
	result_observer = std::make_shared<ResultObserver>(D3DX_PI / 3, window->GetWidth(), window->GetHeight());

	frustum_culling_ = std::make_unique<utility::culling::FrustumCulling>(utility::math::ToRadian(70.0f), (f32)window->GetWidth() / window->GetHeight(), 0.1f, 100.0f);

	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
		color_textures_[i] = graphic_device->CreateTexture(window->GetWidth(), window->GetHeight(), D3DFMT_A8R8G8B8);
		normal_textures_[i] = graphic_device->CreateTexture(window->GetWidth(), window->GetHeight(), D3DFMT_A16B16G16R16F);
		position_textures_[i] = graphic_device->CreateTexture(window->GetWidth(), window->GetHeight(), D3DFMT_A16B16G16R16F);
	}

	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
		field_icons_[i] = std::make_shared<FieldIcon>();
		field_icons_[i]->SetNumber(i);
	}

	float2 positions[]
	{
		float2(0.0f,  0.0f),
		float2(0.0f,window->GetHeight() * 0.5f),
		float2(window->GetWidth() * 0.5f,  0.0f),
		float2(window->GetWidth() * 0.5f,window->GetHeight() * 0.5f),
	};
	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
		auto sprite = std::make_shared<mesh::Sprite>(float2(window->GetWidth() * 0.5f, window->GetHeight() * 0.5f));
		sprite_objects_[i] = std::make_shared<MeshObject>(sprite);
		sprite->SetAnchorPoint(float2(0.0f, 0.0f));
		sprite_objects_[i]->SetPosition(positions[i]._x - 0.5f, positions[i]._y - 0.5f, 0.0f);
	}

	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
		player_icons_[i] = std::make_shared<PlayerIcon>(i);
	}
	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
		players_[i] = std::make_shared<Player>(graphic_device->GetDevice() , i );
	}

	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
		players_[i]->Init(float3(0.0f, 0.0f, 0.0f));
		players_[i]->SetID(i);
	}

	field_ = std::make_shared<Field>();
	field_->Load("resources/map/map.txt");
	auto field_size = field_->GetSize();
	for (u32 i = 0; i < WALL_MAX; ++i)
	{
		wall_[i] = std::make_shared<Wall>(float2(field_size._x, 1.0f));
		wall_[i]->Update();
	}

	wall_[0]->GetObject()->SetPosition(0.0f, 0.0f, field_size._y * 0.5f);
	wall_[0]->GetObject()->SetRotation(0.0f, 0.0f, 0.0f);
	wall_[1]->GetObject()->SetPosition(field_size._x * 0.5f, 0.0f, 0.0f);
	wall_[1]->GetObject()->SetRotation(0.0f, D3DX_PI / 2, 0.0f);
	wall_[2]->GetObject()->SetPosition(0.0f, 0.0f, -field_size._y * 0.5f);
	wall_[2]->GetObject()->SetRotation(0.0f, D3DX_PI, 0.0f);
	wall_[3]->GetObject()->SetPosition(-field_size._x * 0.5f, 0.0f, 0.0f);
	wall_[3]->GetObject()->SetRotation(0.0f, D3DX_PI / -2, 0.0f);

	dome_ = std::make_shared<Dome>();
	dome_->GetObjectA()->SetPosition(0.0f, -6.0f, 0.0f);

	cylinder_ = std::make_shared<Cylinder>();
	cylinder_->GetObjectA()->SetPosition(0.0f, -5.0f, 0.0f);

	game_timer_ = std::make_shared<GameTimer>();

	weapon_icon_ = std::make_shared<WeaponIcon>();

	flowers_.resize(field_->GetBlockCount());

	for (auto& flower : flowers_)
	{
		flower = std::make_shared<Flower>(0);
	}

	score_ = std::make_shared<Score>();
	result_team_icon = std::make_shared<ResultTeamIcon>();
	result_winlogo_ = std::make_shared<ResultWinLogo>();

	fbx_object_[0] = std::make_shared<FBXObject>(graphic_device->GetDevice());
	fbx_object_[0]->Load("resources/model/iwa_obj_1.kim");
	fbx_object_[0]->SetPosition(-10, 0, 0);

	fbx_tree_[0] = std::make_shared<FBXTree>(graphic_device->GetDevice(), 0);
	fbx_tree_[1] = std::make_shared<FBXTree>(graphic_device->GetDevice(), 2);

	fbx_tree_[0]->SetPosition(-10, 0, 5);
	fbx_tree_[1]->SetPosition(-10, 0, -5);

	is_win_team_ = WIN_TEAM::NONE;
	is_result_ = false;
	result_state = RESULT_STATE::NONE;

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		auto sprite_3d = std::make_shared<mesh::Sprite3D>(float2(0.4f, 0.35f));
		sprite_3D_[i] = std::make_shared<MeshObject>(sprite_3d);
		sprite_3D_[i]->SetPosition(-9.5f, 0.01f, 2.0f);
		sprite_3D_[i]->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/shadow.png"));
		sprite_3D_[i]->SetRotationX(utility::math::ToRadian(90.0f));
	}

#ifdef _DEBUG
	debugRenderTarget_ = false;
	debug_player_number_ = 0;
	auto sprite = std::make_shared<mesh::Sprite>(float2(window->GetWidth() * 0.25f, window->GetHeight() * 0.25f));
	debug_sprite_object_ = std::make_shared<MeshObject>(sprite);
	debug_sprite_object_->SetPosition(-0.5f, -0.5f, 0.0f);
	sprite = std::make_shared<mesh::Sprite>(float2(window->GetWidth(), window->GetHeight()));
	debug_object_ = std::make_shared<MeshObject>(sprite);
	debug_object_->SetPosition(-0.5f, -0.5f, 0.0f);
#endif
}

//=============================================================================
// destructor
//=============================================================================
Game::~Game()
{

}

//=============================================================================
// initialize
//=============================================================================
bool Game::Initialize(SceneManager* p_scene_manager)
{
	float3 positions[] =
	{
		float3(-10.0f,0.0f,-10.0f),
		float3(10.0f,0.0f,-10.0f),
		float3(-10.0f,0.0f, 10.0f),
		float3(10.0f,0.0f, 10.0f),
	};

	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
		players_[i]->Init(positions[i]);

		observers_[i]->SetTargetVector(float3(0.0f,0.0f,1.0f));
		observers_[i]->SetLength(2.0f);
		observers_[i]->SetHeight(1.5f);
		observers_[i]->SetTargetPosition(positions[i]);
		observers_[i]->SetState(FollowerObserver::STATE::FOLLWER);
		observers_[i]->SetTimer(1);
		observers_[i]->SetRotation(float3());
		observers_[i]->Update();
	}

	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
		player_icons_[i]->SetPosition(players_[i]->GetPosition());
	}

	for (auto flower : flowers_)
	{
		flower->Death();
	}

	flower_list_.clear();

	timer_->Reset();
	game_timer_->Reset();

	result_team_icon->Reset();
	score_->Reset();

	is_result_ = false;
	result_state = RESULT_STATE::NONE;

	//BGM
	Sound::Instance().PlaySound(SOUND_LABEL_BGM002);

	return true;
}

//=============================================================================
// finalize
//=============================================================================
void Game::Finalize()
{
	Sound::Instance().StopSound();
}

//=============================================================================
// update
//=============================================================================
void Game::Update()
{
	//timer_->Update();

	if (timer_->GetTimeLeft() == 0)
	{
		// 終了
		is_result_ = true;
		if (GetPoint(0) + GetPoint(1) > GetPoint(2) + GetPoint(3))
		{
			is_win_team_ = WIN_TEAM::RED;
		}
		else if (GetPoint(0) + GetPoint(1) < GetPoint(2) + GetPoint(3))
		{
			is_win_team_ = WIN_TEAM::BLUE;
		}
		else if (GetPoint(0) + GetPoint(1) == GetPoint(2) + GetPoint(3))
		{
			is_win_team_ = WIN_TEAM::DRAW;
		}
		result_state = RESULT_STATE::TWOTEAM;
		score_->SetScore(0, GetPoint(0)+GetPoint(1));
		score_->SetScore(1, GetPoint(2)+GetPoint(3));
	}

	for (int i = 0; i < PLAYER_SUM; i++)
	{
		if (GET_INPUT_XPAD(i)->GetTrigger(XIPad::KEY::X))
		{
			//効果音再生
			Sound::Instance().PlaySeSound(SOUND_LABEL_SE_YES, 0);

			is_result_ = true;

			if (GetPoint(0) + GetPoint(1) > GetPoint(2) + GetPoint(3))
			{
				is_win_team_ = WIN_TEAM::RED;
			}
			else if (GetPoint(0) + GetPoint(1) < GetPoint(2) + GetPoint(3))
			{
				is_win_team_ = WIN_TEAM::BLUE;
			}
			else if (GetPoint(0) + GetPoint(1) == GetPoint(2) + GetPoint(3))
			{
				is_win_team_ = WIN_TEAM::DRAW;
			}


			result_state = RESULT_STATE::TWOTEAM;
			score_->SetScore(0, GetPoint(0) + GetPoint(1));
			score_->SetScore(1, GetPoint(2) + GetPoint(3));
		}
	}

#ifdef _DEBUG
	if (debugRenderTarget_)
	{
		players_[debug_player_number_]->SetCameraVector(observers_[debug_player_number_]->GetFrontVector());
		players_[debug_player_number_]->Update();
	}
#endif

	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
#ifdef _DEBUG
		if (!debugRenderTarget_)
		{
			players_[i]->SetCameraVector(observers_[i]->GetFrontVector());
			players_[i]->Update();
		}
#else
		players_[i]->SetCameraVector(observers_[i]->GetFrontVector());
		players_[i]->Update();
#endif
		player_icons_[i]->SetPosition(players_[i]->GetPosition());
		player_icons_[i]->Update();
		auto front_vector = observers_[i]->GetFrontVector();
		field_icons_[i]->SetFrontVector(front_vector);
		field_icons_[i]->SetBasicPosition(players_[i]->GetPosition());
		field_icons_[i]->Update();

#ifdef _DEBUG
		static bool _bullet_debug = false;

		if (GET_INPUT_KEYBOARD()->GetPress(DIK_B))
		{
			_bullet_debug = true;
		}
		if (GET_INPUT_KEYBOARD()->GetRelease(DIK_B))
		{
			_bullet_debug = false;
		}

#endif // _DEBUG

		// 掘り返し
		if (players_[i]->GetWepon() == Player::WEAPON::HOE &&
			players_[i]->GetAnime() == Player::ANIME::ACTION)
		{
			auto position = field_icons_[i]->GetPosition();
			//if(field_->GetType(position) == (u32)Field::TYPE::SOIL)
			if (players_[i]->GetKimPointer()->GetSingleAnimationEnd() == true)
			{
				auto index = field_->GetBlockIndex(position);
				//field_->SetType(index,(u32)Field::TYPE::SOIL);
				flowers_[index]->Death();
				if(field_->GetType(index) == Field::TYPE::TREE_FLOWER)
				{
					field_->SetType(index,Field::TYPE::TREE);
				}
			}
		}

		if (players_[i]->GetAction() == true)
		{
			// 種まき
			if (players_[i]->GetWepon() == Player::WEAPON::GUN)
			{
				auto start_position = players_[i]->GetPosition();
				start_position._y += 0.7f;
				auto end_position = field_->GetBlockPosition(field_icons_[i]->GetPosition());

				auto is_create = true;

				for (auto bullet : bullets_)
				{
					if (bullet->IsDeath())
					{
						bullet->SetType(Bullet::TYPE::SEED);
						bullet->Reset(start_position, end_position);
						bullet->SetTag(i);
						is_create = false;
						break;
					}
				}

				if (is_create)
				{
					auto bullet = std::make_shared<Bullet>(start_position, end_position);
					bullet->SetTag(i);
					bullets_.push_back(bullet);
				}
			}

			// 妨害
			if (players_[i]->GetWepon() == Player::WEAPON::LAUNCHER)
			{
				auto start_position = players_[i]->GetPosition();
				start_position._y += 0.7f;
				auto end_position = field_icons_[i]->GetPosition();

				auto is_create = true;

				auto smoke = std::make_shared<Smoke>();
				smoke->Start(60,start_position);
				effect_list_.push_back(smoke);

				for(auto bullet : bullets_)
				{
					if (bullet->IsDeath())
					{
						bullet->SetType(Bullet::TYPE::BOMB);
						bullet->Reset(start_position, end_position);
						bullet->SetTag(i);
						is_create = false;
						break;
					}
				}

				if (is_create)
				{
					auto bullet = std::make_shared<Bullet>(start_position, end_position, Bullet::TYPE::BOMB);
					//bullet->SetType(Bullet::TYPE::BOMB);
					bullet->SetTag(i);
					bullets_.push_back(bullet);
				}
			}
		}

		//--  エイム判定  --//
		if (Player::STATE::AIM == players_[i]->GetState())
		{
			observers_[i]->SetState(FollowerObserver::STATE::AIM);

			if (players_[i]->GetWepon() == Player::WEAPON::GUN)
			{
				field_icons_[i]->SetRange(5.0f);
				field_icons_[i]->SetMin(1.0f);
				field_icons_[i]->SetSpeed(0.1f);
				field_icons_[i]->Show(true);
			}

			if (players_[i]->GetWepon() == Player::WEAPON::HOE)
			{
				field_icons_[i]->SetRange(1.0f);
				field_icons_[i]->SetMin(1.0f);
				field_icons_[i]->SetSpeed(0.05f);
				field_icons_[i]->Show(true);
			}

			if (players_[i]->GetWepon() == Player::WEAPON::LAUNCHER)
			{
				field_icons_[i]->SetRange(5.0f);
				field_icons_[i]->SetMin(1.0f);
				field_icons_[i]->SetSpeed(0.1f);
				field_icons_[i]->Show(true, true);
			}
		}
		else
		{
			field_icons_[i]->Show(false);
			observers_[i]->SetState(FollowerObserver::STATE::FOLLWER);
		}

		observers_[i]->SetFieldIconPosition(field_icons_[i]->GetPosition());
		observers_[i]->SetTargetPosition(players_[i]->GetPosition());
		observers_[i]->SetTargetVector(float3(sinf(players_[i]->GetRotation()._y), 0, cosf(players_[i]->GetRotation()._y)));
		observers_[i]->Update();

	}

	game_timer_->Update();
	for (int i = 0; i < 4; i++)
	{
		weapon_icon_->SetWeaponUsing(i, (int)players_[i]->GetWepon());
	}
	weapon_icon_->Update();

	field_->Update();

	effect_list_.erase(remove_if(effect_list_.begin(),effect_list_.end(),[](std::weak_ptr<Effect> effect)->bool {return effect._Get()->IsDeath();}),effect_list_.end());

	for(auto bullet : bullets_)
	{
		bullet->Update();
	}

	// 当たり判定
	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
#ifdef _DEBUG
		if (GET_INPUT_KEYBOARD()->GetPress(DIK_COMMA) || GET_INPUT_MOUSE()->GetPress(InputMouse::MOUSE_KEY::MIDDLE))
		{
			continue;
		}
#endif
		auto player = players_[i];
		auto player_old_position = player->GetOldPosition();
		auto player_move = player->GetMove();
		auto player_position = player->GetPosition();
		auto player_block_position = field_->GetBlockPosition(player_old_position);

		player_position._x = utility::math::Clamp(player_position._x, -14.5f, 14.5f);
		player_position._z = utility::math::Clamp(player_position._z, -14.5f, 14.5f);
		player->SetPosition(player_position);

		auto type = field_->GetType(player_position);

		//if(type == (u32)Field::TYPE::BUILDING)
		//{
		//player->SetPosition(player->GetOldPosition());
		//player->SetMove(float3(0.0f,0.0f,0.0f));
		//}

		player_position = float3(player_old_position._x + player_move._x, 0.0f, player_old_position._z);
		if (field_->IsObstacle(type))
		{
			auto x = field_->GetBlockPosition(player_position)._x - player_block_position._x;
			player->SetPositionX(player->GetOldPosition()._x);
			//player->SetPositionX(player_block_position._x + x);
			//player->SetMove(float3(0.0f,player->GetMove()._y,player->GetMove()._z));
			//player->SetMove(float3(0.0f,0.0f,0.0f));
		}

		player_position = float3(player_old_position._x, 0.0f, player_old_position._z + player_move._z);

		if (field_->IsObstacle(type))
		{
			auto z = field_->GetBlockPosition(player_position)._z - player_block_position._z;
			player->SetPositionZ(player->GetOldPosition()._z);
			//player->SetPositionZ(player_block_position._z + z);
			//player->SetMove(float3(player->GetMove()._x,player->GetMove()._y,0.0f));
		}
	}

	for (auto flower : flower_list_)
	{
		flower._Get()->Update();
	}

	flower_list_.erase(remove_if(flower_list_.begin(),flower_list_.end(),[](std::weak_ptr<Flower> flower)->bool {return !flower._Get()->IsShow();}),flower_list_.end());

	UpdateFieldObject();

	for(auto tree_creater : tree_creater_map_)
	{
		tree_creater.second->Update();
	}

	for(auto tree_creater_it : tree_creater_map_)
	{
		auto tree_creater = tree_creater_it.second;
		if(!tree_creater->IsDeath())
		{
			if(tree_creater->IsCreate())
			{
				auto tree = std::make_shared<FBXTree>(GET_DIRECTX9_DEVICE(),tree_creater->GetNumber());
				tree->SetPosition(tree_creater->GetPosition());
				tree_list_.push_back(tree);
				tree_creater->Death();

				auto index = tree_creater_it.first;

				flowers_[index]->Hide();
				flowers_[index + 1]->Hide();
				flowers_[index + field_->GetBlockWidthCount()]->Hide();
				flowers_[index + field_->GetBlockWidthCount() + 1]->Hide();
			}
		}
	}

	for(auto& tree : tree_list_)
	{
		tree->Update();
	}

	for(auto effect : effect_list_)
	{
		effect._Get()->Update();
	}

	fbx_object_[ 0 ]->Update();

	fbx_tree_[0]->Update();
	fbx_tree_[1]->Update();

	// 
	for (auto bullet : bullets_)
	{
		if (!bullet->IsDeath())
		{
			auto position = bullet->GetPosition();
			if (field_->IsObstacle(field_->GetType(position)))
			{
				bullet->Remove();
			}
			else
			{
				if (position._y <= 0.0f)
				{
					if (bullet->GetType() == Bullet::TYPE::SEED)
					{
						auto index = field_->GetBlockIndex(position);
						auto field_type = field_->GetType(index);
						if(field_type == Field::TYPE::SOIL || field_type == Field::TYPE::TREE)
						{
							auto index = field_->GetBlockIndex(position);
							auto flower_position = field_->GetBlockPosition(position);
							if(!flowers_[index]->IsLive())
							{
								flowers_[index]->SetNumber(bullet->GetTag());
								flowers_[index]->Show();
								flowers_[index]->SetPosition(flower_position);


								if(field_type == Field::TYPE::TREE)
								{
									flowers_[index]->SetIsGrowth(true);
									//field_->SetType(index,Field::TYPE::TREE_FLOWER);
								}
								flower_list_.push_back(flowers_[index]);
							}
						}
					}

					if (bullet->GetType() == Bullet::TYPE::BOMB)
					{
						position._y = 0.0f;
						for (u32 i = 0; i < PLAYER_MAX; ++i)
						{
							if (bullet->GetTag() / 2 != i / 2)
							{
								auto& player = players_[i];
								auto player_position = player->GetPosition();
								if (utility::math::Distance(position, player_position) < 0.5f + 1.0f)
								{
									DEBUG_TRACE("hit");
								}
							}
						}
					}

					bullet->Remove();
				}
			}
		}
	}

#ifndef _RELEASE
	for (auto i = 0; i < PLAYER_MAX; ++i)
	{
		DEVELOP_DISPLAY("player %d : %d\n", i, GetPoint(i));
	}
#endif
	if (is_result_)
	{
		UpdateResult();
	}
}

//=============================================================================
// draw
//=============================================================================
void Game::Draw()
{
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto gb_vs = graphic_device->LoadVertexShader("resources/shader/graphics_buffer.vsc");
	auto gb_ps = graphic_device->LoadPixelShader("resources/shader/graphics_buffer.psc");
	auto d_vs = graphic_device->LoadVertexShader("resources/shader/deferred.vsc");
	auto d_ps = graphic_device->LoadPixelShader("resources/shader/deferred.psc");
	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");
	auto gb_vs_fbx = graphic_device->LoadVertexShader("resources/shader/graphics_buffer_fbx.vsc");
	auto default_texture = graphic_device->GetRenderTarget(0);


#ifdef _DEBUG

	int debug_object_draw_num = 0;

	int min = 0;
	int max = PLAYER_MAX;

	static bool _d = false;
	if (GET_INPUT_KEYBOARD()->GetTrigger(DIK_9))
	{
		_d = !_d;
	}

	if (_d == true)
	{
		max = 1;
		if (debugRenderTarget_)
		{
			min = debug_player_number_;
			max = debug_player_number_ + 1;
		}
	}

	if (GET_INPUT_KEYBOARD()->GetPress(DIK_M))
	{
		GET_DIRECTX9_DEVICE()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	for (u32 i = min; i < max; ++i)
#else
	for (u32 i = 0; i < PLAYER_MAX; ++i)
#endif // _DEBUG
	{
		graphic_device->SetRenderTarget(0, color_textures_[i]);
		graphic_device->SetRenderTarget(1, normal_textures_[i]);
		graphic_device->SetRenderTarget(2, position_textures_[i]);

		graphic_device->Clear(float4(1.0f, 0.0f, 0.0f, 0.0f), 1.0f);

		graphic_device->SetVertexShader(gb_vs);
		graphic_device->SetPixelShader(gb_ps);

		// observer
		gb_vs->SetValue("_view_matrix", (f32*)&observers_[i]->GetViewMatrix(), 16);
		gb_vs->SetValue("_projection_matrix", (f32*)&observers_[i]->GetProjectionMatrix(), 16);


		auto view_matrix = observers_[i]->GetViewMatrix();
		auto i_view_matrix = utility::math::InverseB(view_matrix);

		auto object = field_->GetObject();
		auto world_matrix = object->GetMatrix();

		frustum_culling_->SetViewMatrix(view_matrix);

		gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
		gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

		//if(frustum_culling_->IsCulling(object->GetPosition(),2.0f))
		{
			object->Draw();
		}

		for (u32 j = 0; j < PLAYER_MAX; ++j)
		{
			if (field_icons_[j]->IsShow())
			{
				if (i != j)
				{
					if (!field_icons_[j]->IsShowAll())
					{
						continue;
					}
				}
				object = field_icons_[j]->GetObject();

				world_matrix = object->GetMatrix();

				// object
				gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
				gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

				if (frustum_culling_->IsCulling(object->GetPosition(), 0.5f))
				{
#ifdef _DEBUG
					debug_object_draw_num++;
#endif // _DEBUG
					object->Draw();
				}
			}
		}

		for (auto bullet : bullets_)
		{
			if (!bullet->IsDeath())
			{
				object = bullet->GetObject();
				world_matrix = object->GetMatrix();
				world_matrix = utility::math::Multiply(i_view_matrix, world_matrix);

				gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
				gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

				if (frustum_culling_->IsCulling(object->GetPosition(), 0.5f))
				{
#ifdef _DEBUG
					debug_object_draw_num++;
#endif // _DEBUG
					object->Draw();
				}
			}
		}

		for (auto flower : flower_list_)
		{
			//if(flower->IsShow())
			//{
			object = flower._Get()->GetObject();
			world_matrix = object->GetMatrix();
			world_matrix = utility::math::Multiply(i_view_matrix, world_matrix);

			gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
			gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

			if (frustum_culling_->IsCulling(object->GetPosition(), 0.5f))
			{
#ifdef _DEBUG
				debug_object_draw_num++;
#endif // _DEBUG
				object->Draw();
			}
			//}
		}

		for(auto effect : effect_list_)
		{
			//if(flower->IsShow())
			//{
			object = effect._Get()->GetObject();
			world_matrix = object->GetMatrix();
			world_matrix = utility::math::Multiply(i_view_matrix,world_matrix);

			gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,16);
			gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

			if(frustum_culling_->IsCulling(object->GetPosition(),0.5f))
			{
#ifdef _DEBUG
				debug_object_draw_num++;
#endif // _DEBUG
				object->Draw();
			}
			//}
		}

		//draw wall
		for (u32 j = 0; j < WALL_MAX; ++j)
		{
			object = wall_[j]->GetObject();

			world_matrix = object->GetMatrix();

			gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
			gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

			//if(frustum_culling_->IsCulling(object->GetPosition(),2.0f))
			{
				object->Draw();
			}
		}

		//draw dome
		object = dome_->GetObject();
		world_matrix = object->GetMatrix();
		gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
		gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

		//if(frustum_culling_->IsCulling(object->GetPosition(),2.0f))
		{
			object->Draw();
		}

		//draw cylinder
		object = cylinder_->GetObject();
		world_matrix = object->GetMatrix();
		gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
		gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

		//if(frustum_culling_->IsCulling(object->GetPosition(),2.0f))
		{
			object->Draw();
		}

		for (u32 j = 0; j < PLAYER_MAX; ++j)
		{
			if (i != j)
			{
				object = player_icons_[j]->GetObject();
				world_matrix = object->GetMatrix();
				world_matrix = utility::math::Multiply(i_view_matrix, world_matrix);
				gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
				gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());
				if (frustum_culling_->IsCulling(players_[j]->GetPosition(), 0.5f))
				{
#ifdef _DEBUG
					debug_object_draw_num++;
#endif // _DEBUG
					object->Draw();
				}
			}
		}

		for (int j = 0; j < PLAYER_MAX; j++)
		{
			gb_vs->SetValue("_world_matrix", (f32*)&sprite_3D_[j]->GetMatrix(), 16);
			gb_ps->SetTexture("_texture_sampler", sprite_3D_[j]->GetTexture(0)->GetTexture());
			sprite_3D_[j]->SetPosition(players_[j]->GetPosition()._x, 0.01f, players_[j]->GetPosition()._z);
			sprite_3D_[j]->Draw();
		}


		//--  動かないFBX  --//
		fbx_object_[0]->GetKimPointer()->SetView((D3DXMATRIX*)&observers_[i]->GetViewMatrix());
		fbx_object_[0]->GetKimPointer()->SetProjection((D3DXMATRIX*)&observers_[i]->GetProjectionMatrix());
		fbx_object_[0]->Draw();

		graphic_device->SetVertexShader(gb_vs_fbx);

		fbx_tree_[0]->GetKimPointer()->SetView((D3DXMATRIX*)&observers_[i]->GetViewMatrix());
		fbx_tree_[0]->GetKimPointer()->SetProjection((D3DXMATRIX*)&observers_[i]->GetProjectionMatrix());
		fbx_tree_[0]->Draw();

		fbx_tree_[1]->GetKimPointer()->SetView((D3DXMATRIX*)&observers_[i]->GetViewMatrix());
		fbx_tree_[1]->GetKimPointer()->SetProjection((D3DXMATRIX*)&observers_[i]->GetProjectionMatrix());
		fbx_tree_[1]->Draw();

		for(auto tree : tree_list_)
		{
			tree->GetKimPointer()->SetView((D3DXMATRIX*)&observers_[i]->GetViewMatrix());
			tree->GetKimPointer()->SetProjection((D3DXMATRIX*)&observers_[i]->GetProjectionMatrix());
			tree->Draw();
		}

		for(u32 j = 0;j < PLAYER_MAX;++j)
		{
			players_[j]->GetKimPointer()->SetView((D3DXMATRIX*)&observers_[i]->GetViewMatrix());
			players_[j]->GetKimPointer()->SetProjection((D3DXMATRIX*)&observers_[i]->GetProjectionMatrix());

			if (frustum_culling_->IsCulling(players_[j]->GetPosition(), 1.0f))
			{
#ifdef _DEBUG
				debug_object_draw_num++;
#endif // _DEBUG
				players_[j]->Draw();
			}
		}
	}

#ifdef _DEBUG
	DEVELOP_DISPLAY("object_draw : %d\n", debug_object_draw_num);
	GET_DIRECTX9_DEVICE()->SetRenderState(D3DRS_FILLMODE, D3DFILL_FORCE_DWORD);
#endif
	graphic_device->SetRenderTarget(0, default_texture);
	graphic_device->SetRenderTarget(1, nullptr);
	graphic_device->SetRenderTarget(2, nullptr);
	graphic_device->SetRenderTarget(3, nullptr);

	graphic_device->Clear(float4(1.0f, 0.0f, 0.0f, 0.0f), 1.0f);

	graphic_device->SetVertexShader(d_vs);
	graphic_device->SetPixelShader(d_ps);

	d_vs->SetValue("_view_matrix", (f32*)&observer_2d_->GetViewMatrix(), 16);
	d_vs->SetValue("_projection_matrix", (f32*)&observer_2d_->GetProjectionMatrix(), 16);
	d_ps->SetValue("_light_vector", (f32*)&float3(0.0f, -1.0f, 0.0f), 3);
	d_ps->SetValue("_light_deffuse", (f32*)&float3(1.0f, 1.0f, 1.0f), 3);

	for (u32 i = 0; i < PLAYER_MAX; ++i)
	{
		d_vs->SetValue("_world_matrix", (f32*)&sprite_objects_[i]->GetMatrix(), 16);
		d_ps->SetTexture("_color_sampler", color_textures_[i]->GetTexture());
		d_ps->SetTexture("_normal_sampler", normal_textures_[i]->GetTexture());
		d_ps->SetTexture("_position_sampler", position_textures_[i]->GetTexture());
		sprite_objects_[i]->Draw();
	}



#ifdef _DEBUG 
	static int _debugRenderTargetIndex = 0;

	LPDIRECT3DTEXTURE9 tex[3];
	tex[0] = color_textures_[debug_player_number_]->GetTexture();
	tex[1] = normal_textures_[debug_player_number_]->GetTexture();
	tex[2] = position_textures_[debug_player_number_]->GetTexture();

	if (GET_INPUT_KEYBOARD()->GetTrigger(DIK_0) == true)
	{
		debugRenderTarget_ = !debugRenderTarget_;
	}

	if (debugRenderTarget_ == true)
	{
		DEVELOP_DISPLAY("操作プレイヤー : %d\n", debug_player_number_ + 1);
		if (GET_INPUT_KEYBOARD()->GetTrigger(DIK_LEFT) == true)
		{
			_debugRenderTargetIndex--;

			if (_debugRenderTargetIndex == -1)
			{
				_debugRenderTargetIndex = 0;
			}
		}
		if (GET_INPUT_KEYBOARD()->GetTrigger(DIK_RIGHT) == true)
		{
			_debugRenderTargetIndex++;

			if (_debugRenderTargetIndex == 3)
			{
				_debugRenderTargetIndex = 2;
			}
		}

		if (GET_INPUT_KEYBOARD()->GetTrigger(DIK_1))
		{
			debug_player_number_ = 0;
		}

		if (GET_INPUT_KEYBOARD()->GetTrigger(DIK_2))
		{
			debug_player_number_ = 1;
		}

		if (GET_INPUT_KEYBOARD()->GetTrigger(DIK_3))
		{
			debug_player_number_ = 2;
		}

		if (GET_INPUT_KEYBOARD()->GetTrigger(DIK_4))
		{
			debug_player_number_ = 3;
		}

		graphic_device->SetVertexShader(d_vs);
		graphic_device->SetPixelShader(d_ps);

		d_vs->SetValue("_view_matrix", (f32*)&observer_2d_->GetViewMatrix(), sizeof(float4x4));
		d_vs->SetValue("_projection_matrix", (f32*)&observer_2d_->GetProjectionMatrix(), sizeof(float4x4));
		d_vs->SetValue("_world_matrix", (f32*)&debug_object_->GetMatrix(), sizeof(float4x4));

		d_ps->SetValue("_light_vector", (f32*)&float3(0.0f, 0.0f, -1.0f), sizeof(float3));
		d_ps->SetValue("_light_deffuse", (f32*)&float3(1.0f, 1.0f, 1.0f), sizeof(float3));
		d_ps->SetTexture("_color_sampler", color_textures_[debug_player_number_]->GetTexture());
		d_ps->SetTexture("_normal_sampler", normal_textures_[debug_player_number_]->GetTexture());
		d_ps->SetTexture("_position_sampler", position_textures_[debug_player_number_]->GetTexture());

		debug_object_->Draw();

		graphic_device->SetVertexShader(basic_vs);
		graphic_device->SetPixelShader(basic_ps);

		basic_vs->SetValue("_view_matrix", (f32*)&observer_2d_->GetViewMatrix(), sizeof(float4x4));
		basic_vs->SetValue("_projection_matrix", (f32*)&observer_2d_->GetProjectionMatrix(), sizeof(float4x4));
		basic_vs->SetValue("_world_matrix", (f32*)&debug_sprite_object_->GetMatrix(), sizeof(float4x4));

		basic_ps->SetTexture("_texture_sampler", tex[_debugRenderTargetIndex]);

		debug_sprite_object_->Draw();
	}
#endif


	//draw game_timer_
	basic_vs->SetValue("_view_matrix", (f32*)&observer_2d_->GetViewMatrix(), sizeof(float4x4));
	basic_vs->SetValue("_projection_matrix", (f32*)&observer_2d_->GetProjectionMatrix(), sizeof(float4x4));
	game_timer_->Draw();


	//draw weapon_icon
	weapon_icon_->Draw();

	//Draw Result
	if (is_result_)
	{
		DrawResult();
	}

}

void Game::UpdateResult(void)
{
	if (result_state == RESULT_STATE::TWOTEAM)
	{
		for (int i = 0; i < 4; i++)
		{
			if (GET_INPUT_XPAD(i)->GetTrigger(XIPad::KEY::A) || GET_INPUT_XPAD(i)->GetTrigger(XIPad::KEY::B))
			{
				result_team_icon->SetState(ResultTeamIcon::STATE::MOVE);
				result_team_icon->SetWinTeam((unsigned int)is_win_team_);

				score_->SetState(Score::STATE::MOVE);
				score_->SetWinTeam((unsigned int)is_win_team_);

				result_state = RESULT_STATE::TEAMMOVE;
			}
		}
	}
	else if (result_state == RESULT_STATE::TEAMMOVE)
	{
		if (result_team_icon->GetState() == ResultTeamIcon::STATE::MOVED)
		{
			result_state = RESULT_STATE::WINLOGO;
			result_winlogo_->SetWinTeam((unsigned int)is_win_team_);
		}
	}
	else if (result_state == RESULT_STATE::WINLOGO)
	{
		for (int i = 0; i < 4; i++)
		{
			if (GET_INPUT_XPAD(i)->GetTrigger(XIPad::KEY::A) || GET_INPUT_XPAD(i)->GetTrigger(XIPad::KEY::B))
			{
				result_state = RESULT_STATE::BACKGROUND;
			}
		}
	}
	//リザルト状態がバックグラウンドの表示のみの場合
	else if (result_state == RESULT_STATE::BACKGROUND)
	{
		for (int i = 0; i < 4; i++)
		{
			if (GET_INPUT_XPAD(i)->GetTrigger(XIPad::KEY::A) || GET_INPUT_XPAD(i)->GetTrigger(XIPad::KEY::B))
			{
				SceneManager::Instance().set_p_next_scene(SceneManager::Instance().get_game());
				SceneManager::Instance().set_scene_change_flag(true);
				
			}
		}
	}
	result_team_icon->Update();
	score_->Update();
	result_observer->Update();
}

void Game::DrawResult(void)
{
	//クリアー
	//graphic_device->Clear(float4(1.0f, 0.0f, 0.0f, 0.0f), 1.0f);
	//フィールド描画

	//2Dポリゴン描画
	auto graphic_device = GET_GRAPHIC_DEVICE();
	graphic_device->Clear(float4(0.0f, 0.0f, 0.0f, 0.0f), 1.0f);
	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");
	auto gb_vs = graphic_device->LoadVertexShader("resources/shader/graphics_buffer.vsc");
	auto gb_ps = graphic_device->LoadPixelShader("resources/shader/graphics_buffer.psc");

	basic_vs->SetValue("_view_matrix", (f32*)&observer_2d_->GetViewMatrix(), sizeof(float4x4));
	basic_vs->SetValue("_projection_matrix", (f32*)&observer_2d_->GetProjectionMatrix(), sizeof(float4x4));

	if (result_state != RESULT_STATE::BACKGROUND)
	{
		//チーム アイコン
		result_team_icon->Draw();
		//スコア
		score_->Draw();
		if (result_state == RESULT_STATE::WINLOGO)
		{
			result_winlogo_->Draw();
		}
	}

	//プレイヤー描画

	//背景としてフィールド描画
	graphic_device->SetVertexShader(gb_vs);
	graphic_device->SetPixelShader(gb_ps);

	// observer
	gb_vs->SetValue("_view_matrix", (f32*)&result_observer->GetViewMatrix(), 16);
	gb_vs->SetValue("_projection_matrix", (f32*)&result_observer->GetProjectionMatrix(), 16);


	auto view_matrix = result_observer->GetViewMatrix();
	auto i_view_matrix = utility::math::InverseB(view_matrix);

	//フィールド
	auto object = field_->GetObject();
	auto world_matrix = object->GetMatrix();

	frustum_culling_->SetViewMatrix(view_matrix);

	gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
	gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

	object->Draw();

	//フラワーリスト
	for (auto flower : flower_list_)
	{
		object = flower._Get()->GetObject();
		world_matrix = object->GetMatrix();
		world_matrix = utility::math::Multiply(i_view_matrix, world_matrix);

		gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
		gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

		if (frustum_culling_->IsCulling(object->GetPosition(), 0.5f))
		{
			object->Draw();
		}
	}

	//draw wall
	for (u32 j = 0; j < WALL_MAX; ++j)
	{
		object = wall_[j]->GetObject();

		world_matrix = object->GetMatrix();

		gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
		gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

		//if(frustum_culling_->IsCulling(object->GetPosition(),2.0f))
		{
			object->Draw();
		}
	}

	//draw dome
	object = dome_->GetObject();
	world_matrix = object->GetMatrix();
	gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
	gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

	//if(frustum_culling_->IsCulling(object->GetPosition(),2.0f))
	{
		object->Draw();
	}
}

u32 Game::GetPoint(u32 player_number) const
{
	u32 count = 0;

	for (auto flower : flower_list_)
	{
		if (flower._Get()->GetNumber() == player_number)
		{
			count++;
		}
	}
	return count;
}

void Game::UpdateFieldObject(void)
{
	auto width = field_->GetBlockWidthCount();
	auto height = field_->GetBlockHeightCount();
	for(u32 i = 0;i < height;++i)
	{
		for(u32 j = 0;j < width;++j)
		{
			auto key = i * width + j;
			if(!(tree_creater_map_.find(key) == tree_creater_map_.end()))
			{
				continue;
			}
			if(CheckGrowTree(j,i,0))
			{
				flowers_[i * width + j]->SetTreeIndex(key);
				flowers_[i * width + j]->SetGrow();
				flowers_[i * width + j + 1]->SetTreeIndex(key);
				flowers_[i * width + j + 1]->SetGrow();
				flowers_[(i + 1) * width + j]->SetTreeIndex(key);
				flowers_[(i + 1) * width + j]->SetGrow();
				flowers_[(i + 1) * width + j + 1]->SetTreeIndex(key);
				flowers_[(i + 1) * width + j + 1]->SetGrow();
				auto tree_creater = std::make_shared<TreeCreater>();
				//tree_creater->SetPosition(float3(0.0f,0.0f,0.0f));
				tree_creater->SetPosition(float3((j + 1) * 0.5f - width * 0.25f,0.0f,-((i + 1) * 0.5f) + height * 0.25f));
				tree_creater->SetNumber(0);
				tree_creater_map_.insert(std::make_pair(key,tree_creater));
			}
			if(CheckGrowTree(j,i,2))
			{

			}
		}
	}
}

bool Game::CheckGrowTree(u32 in_x,u32 in_y,u32 in_type)
{
	auto width = field_->GetBlockWidthCount();

	if(!(flowers_[in_y * width + in_x]->IsTreeCreate()))
	{
		return false;
	}

	if(!(flowers_[in_y * width + in_x]->GetNumber() == in_type || flowers_[in_y * width + in_x]->GetNumber() == in_type + 1))
	{
		return false;
	}

	if(!flowers_[in_y * width + in_x + 1]->IsTreeCreate())
	{
		return false;
	}

	if(!(flowers_[in_y * width + in_x + 1]->GetNumber() == in_type || flowers_[in_y * width + in_x + 1]->GetNumber() == in_type + 1))
	{
		return false;
	}

	if(!flowers_[(in_y + 1) * width + in_x]->IsTreeCreate())
	{
		return false;
	}

	if(!(flowers_[(in_y + 1) * width + in_x]->GetNumber() == in_type || flowers_[(in_y + 1) * width + in_x]->GetNumber() == in_type + 1))
	{
		return false;
	}

	if(!flowers_[(in_y + 1) * width + in_x + 1]->IsTreeCreate())
	{
		return false;
	}

	if(!(flowers_[(in_y + 1) * width + in_x + 1]->GetNumber() == in_type || flowers_[(in_y + 1) * width + in_x + 1]->GetNumber() == in_type + 1))
	{
		return false;
	}

	return true;
}
