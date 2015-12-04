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
#include "system/win_system.h"
#include "system/input_keyboard.h"
#include "shader/dx9_vertex_shader.h"
#include "shader/dx9_pixel_shader.h"
#include "texture/dx9_texture.h"
#include "mesh/sprite.h"
#include "observer/observer_2d.h"
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

//=============================================================================
// constructor
//=============================================================================
Game::Game()
{
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto window = GET_WINDOW();

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		observers_[i] = std::make_shared<FollowerObserver>(utility::math::ToRadian(60.0f),window->GetWidth(),window->GetHeight());
		observers_[i]->SetTargetPosition(float3(0.0f,0.0f,0.0f));
		observers_[i]->SetTargetVector(float3(0.0f,0.0f,1.0f));
		observers_[i]->SetLength(2.0f);
		observers_[i]->SetHeight(1.5f);
		observers_[i]->SetState(FollowerObserver::STATE::FOLLWER);
		observers_[i]->Update();
	}

	observer_2d_ = std::make_shared<Observer2D>(window->GetWidth(),window->GetHeight());

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		color_textures_[i] = graphic_device->CreateTexture(window->GetWidth(),window->GetHeight(),D3DFMT_A8R8G8B8);
		normal_textures_[i] = graphic_device->CreateTexture(window->GetWidth(),window->GetHeight(),D3DFMT_A16B16G16R16F);
		position_textures_[i] = graphic_device->CreateTexture(window->GetWidth(),window->GetHeight(),D3DFMT_A16B16G16R16F);
	}

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		field_icons_[i] = std::make_shared<FieldIcon>();
	}

	float2 positions[]
	{
		float2(  0.0f,  0.0f),
		float2(window->GetWidth() * 0.5f,  0.0f),
		float2(  0.0f,window->GetHeight() * 0.5f),
		float2(window->GetWidth() * 0.5f,window->GetHeight() * 0.5f),
	};
	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		auto sprite = std::make_shared<mesh::Sprite>(float2(window->GetWidth() * 0.5f,window->GetHeight() * 0.5f));
		sprite_objects_[i] = std::make_shared<MeshObject>(sprite);
		sprite->SetAnchorPoint(float2(0.0f,0.0f));
		sprite_objects_[i]->SetPosition(positions[i]._x  - 0.5f,positions[i]._y - 0.5f,0.0f);
	}

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		player_icons_[i] = std::make_shared<PlayerIcon>(i);
	}
	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		players_[i] = std::make_shared<Player>(graphic_device->GetDevice());
	}

	field_ = std::make_shared<Field>();

	for (u32 i = 0; i < WALL_MAX; ++i)
	{
		wall_[i] = std::make_shared<Wall>();
		wall_[i]->Update();
	}

	wall_[0]->GetObject()->SetPosition(0.0f, 0.0f, 15.0f);
	wall_[0]->GetObject()->SetRotation(0.0f, 0.0f, 0.0f);
	wall_[1]->GetObject()->SetPosition(15.0f, 0.0f, 0.0f);
	wall_[1]->GetObject()->SetRotation(0.0f, D3DX_PI/2, 0.0f);
	wall_[2]->GetObject()->SetPosition(0.0f, 0.0f, -15.0f);
	wall_[2]->GetObject()->SetRotation(0.0f, D3DX_PI, 0.0f);
	wall_[3]->GetObject()->SetPosition(-15.0f, 0.0f, 0.0f);
	wall_[3]->GetObject()->SetRotation(0.0f, D3DX_PI/-2, 0.0f);
	
	dome_ = std::make_shared<Dome>();
	dome_->GetObjectA()->SetPosition(0.0f,-6.0f, 0.0f);

	cylinder_ = std::make_shared<Cylinder>();
	cylinder_->GetObjectA()->SetPosition(0.0f,0.0f,0.0f);

#ifdef _DEBUG
	debugRenderTarget_ = false;
	debug_player_number_ = 0;
	auto sprite = std::make_shared<mesh::Sprite>(float2(window->GetWidth() * 0.25f,window->GetHeight() * 0.25f));
	debug_sprite_object_ = std::make_shared<MeshObject>(sprite);
	debug_sprite_object_->SetPosition(-0.5f,-0.5f,0.0f);
	sprite = std::make_shared<mesh::Sprite>(float2(window->GetWidth(),window->GetHeight()));
	debug_object_ = std::make_shared<MeshObject>(sprite);
	debug_object_->SetPosition(-0.5f,-0.5f,0.0f);
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
		float3( 10.0f,0.0f,-10.0f),
		float3(-10.0f,0.0f, 10.0f),
		float3( 10.0f,0.0f, 10.0f),
	};

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		players_[i]->Init(positions[i]);
	}
	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		player_icons_[i]->SetPosition(players_[i]->GetPosition());
	}
	return true;
}
//=============================================================================
// finalize
//=============================================================================
void Game::Finalize()
{

}

//=============================================================================
// update
//=============================================================================
void Game::Update()
{
#ifndef _RELEASE
	if(GET_INPUT_KEYBOARD()->GetTrigger(DIK_R))
	{
		field_->Reset();
	}
#endif

#ifdef _DEBUG
	if(debugRenderTarget_)
	{
		players_[debug_player_number_]->SetCameraVector(observers_[debug_player_number_]->GetFrontVector());
		players_[debug_player_number_]->Update();
	}
#endif

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
#ifdef _DEBUG
		if(!debugRenderTarget_)
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

		if( players_[ i ]->GetKimPointer()->GetWepon() == Kim::WEAPON::GUN &&
			//GET_INPUT_KEYBOARD()->GetTrigger( DIK_SPACE ) &&
			players_[ i ]->GetAction() == true )
	//		GET_INPUT_KEYBOARD()->GetTrigger( DIK_SPACE )
		//if(  )
		{
			// Ží‚Ü‚«
			if(field_icons_[i]->IsShow())
			{
				auto start_position = players_[i]->GetPosition();
				start_position._y += 0.7f;
				auto end_position = field_->GetBlockPosition(field_icons_[i]->GetPosition());

				auto is_create = true;

				for(auto bullet : bullets_)
				{
					if(bullet->IsDeath())
					{
						bullet->Reset(start_position,end_position);
						bullet->SetTag(i);
						is_create = false;
						break;
					}
				}

				if(is_create)
				{
					auto bullet = std::make_shared<Bullet>(start_position,end_position);
					bullet->SetTag(i);
					bullets_.push_back(bullet);
				}
			}
			// Œ@‚è•Ô‚µ
			else
			{
				auto position = players_[i]->GetPosition();
				if(field_->GetType(position) == 3)
				{
					field_->SetType(position,1);
				}
			}
		}

		//--  ƒGƒCƒ€”»’è  --//
		if( Player::STATE::AIM == players_[ i ]->GetState() )
		{
			observers_[i]->SetState( FollowerObserver::STATE::AIM );
			field_icons_[i]->Show(true);
		}
		else
		{
			field_icons_[i]->Show(false);
			observers_[i]->SetState( FollowerObserver::STATE::FOLLWER );
		}

		observers_[i]->SetFieldIconPosition( field_icons_[i]->GetPosition() );
		observers_[i]->SetTargetPosition(players_[i]->GetPosition());
		observers_[i]->SetTargetVector(float3(sinf(players_[i]->GetRotation()._y),0,cosf(players_[i]->GetRotation()._y)));
		observers_[i]->Update();

	}

	field_->Update();

	for(auto bullet : bullets_)
	{
		bullet->Update();
	}

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		auto player = players_[i];
		auto player_old_position = player->GetOldPosition();
		auto player_move = player->GetMove();
		auto player_position = player->GetPosition();

		if(field_->GetType(player_position) == 3)
		{
			player->SetPosition(player->GetOldPosition());
			player->SetMove(float3(0.0f,0.0f,0.0f));
		}

		player_position = float3(player_old_position._x + player_move._x,0.0f,player_old_position._z);
		if(field_->GetType(player_position) == 3)
		{
			player->SetPosition(player->GetOldPosition());
			player->SetMove(float3(0.0f,0.0f,0.0f));
		}

		player_position = float3(player_old_position._x,0.0f,player_old_position._z + player_move._z);

		if(field_->GetType(player_position) == 3)
		{
			player->SetPosition(player->GetOldPosition());
			player->SetMove(float3(0.0f,0.0f,0.0f));
		}
	}

	for(auto flower : flowers_)
	{
		flower->Update();
	}

	// 
	for(auto bullet : bullets_)
	{
		if(!bullet->IsDeath())
		{
			auto position = bullet->GetPosition();
			if(field_->GetType(position) == 3)
			{
				bullet->Remove();
			}
			else
			{
				if(position._y <= 0.0f)
				{
					if(field_->GetType(position) == 1)
					{
						field_->SetType(position,2);
						auto is_create = true;
						auto flower_position = field_->GetBlockPosition(position);
						for(auto flower : flowers_)
						{
							if(!flower->IsShow())
							{
								flower->SetPosition(flower_position);
								flower->SetNumber(bullet->GetTag());
								is_create = false;
								break;
							}
						}

						if(is_create)
						{
							auto flower = std::make_shared<Flower>(bullet->GetTag());
							flower->SetPosition(flower_position);
							flowers_.push_back(flower);
						}
					}
					bullet->Remove();
				}
			}
		}
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
	//auto gb_ps_fbx = graphic_device->LoadVertexShader("resources/shader/graphics_buffer_fbx.psc");
	auto default_texture = graphic_device->GetRenderTarget(0);

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		graphic_device->SetRenderTarget(0,color_textures_[i]);
		graphic_device->SetRenderTarget(1,normal_textures_[i]);
		graphic_device->SetRenderTarget(2,position_textures_[i]);

		graphic_device->Clear(float4(1.0f,0.0f,0.0f,0.0f),1.0f);

		if(field_icons_[i]->IsShow())
		{
			field_->SelectBlock(field_icons_[i]->GetPosition());
		}
		else
		{
			field_->NotSelectBlock();
		}

		graphic_device->SetVertexShader(gb_vs);
		graphic_device->SetPixelShader(gb_ps);

		// observer
		gb_vs->SetValue("_view_matrix",(f32*)&observers_[i]->GetViewMatrix(),16);
		gb_vs->SetValue("_projection_matrix",(f32*)&observers_[i]->GetProjectionMatrix(),16);


		auto view_matrix = observers_[i]->GetViewMatrix();
		auto i_view_matrix = utility::math::InverseB(view_matrix);

		auto object = field_->GetObject();
		auto world_matrix = object->GetMatrix();

		gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,16);
		gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

		object->Draw();

		if(field_icons_[i]->IsShow())
		{
			object = field_icons_[i]->GetObject();

			world_matrix = object->GetMatrix();

			// object
			gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,16);
			gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

			object->Draw();
		}

		for(auto bullet : bullets_)
		{
			if(!bullet->IsDeath())
			{
				object = bullet->GetObject();
				world_matrix = object->GetMatrix();
				world_matrix = utility::math::Multiply(i_view_matrix,world_matrix);

				gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,16);
				gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

				object->Draw();
			}
		}

		for(auto flower : flowers_)
		{
			if(flower->IsShow())
			{
				object = flower->GetObject();
				world_matrix = object->GetMatrix();
				world_matrix = utility::math::Multiply(i_view_matrix,world_matrix);

				gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,16);
				gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

				object->Draw();
			}
		}

		for(u32 j = 0;j < PLAYER_MAX;++j)
		{
			if(i != j)
			{
				object = player_icons_[j]->GetObject();
				world_matrix = object->GetMatrix();
				world_matrix = utility::math::Multiply(i_view_matrix,world_matrix);
				gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,16);
				gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());
				object->Draw();
			}
		}

		//draw wall
		for(u32 j = 0; j < WALL_MAX; ++j)
		{
			object = wall_[j]->GetObject();

			world_matrix = object->GetMatrix();

			gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,16);
			gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

			object->Draw();
		}

		//draw dome
		object = dome_->GetObjectA();
		world_matrix = object->GetMatrix();
		gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
		gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

		object->Draw();

		//draw cylinder
		object = cylinder_->GetObjectA();
		world_matrix = object->GetMatrix();
		gb_vs->SetValue("_world_matrix", (f32*)&world_matrix, 16);
		gb_ps->SetTexture("_texture_sampler", object->GetTexture(0)->GetTexture());

		object->Draw();

		graphic_device->SetVertexShader(gb_vs_fbx);

		for(u32 j = 0;j < PLAYER_MAX;++j)
		{
			players_[j]->GetKimPointer()->SetView((D3DXMATRIX*)&observers_[i]->GetViewMatrix());
			players_[j]->GetKimPointer()->SetProjection((D3DXMATRIX*)&observers_[i]->GetProjectionMatrix());
			players_[j]->Draw();
		}
	}

	graphic_device->SetRenderTarget(0,default_texture);
	graphic_device->SetRenderTarget(1,nullptr);
	graphic_device->SetRenderTarget(2,nullptr);
	graphic_device->SetRenderTarget(3,nullptr);

	graphic_device->Clear(float4(1.0f,0.0f,0.0f,0.0f),1.0f);

	graphic_device->SetVertexShader(d_vs);
	graphic_device->SetPixelShader(d_ps);

	d_vs->SetValue("_view_matrix",(f32*)&observer_2d_->GetViewMatrix(),16);
	d_vs->SetValue("_projection_matrix",(f32*)&observer_2d_->GetProjectionMatrix(),16);
	d_ps->SetValue("_light_vector",(f32*)&float3(0.0f,-1.0f,0.0f),3);
	d_ps->SetValue("_light_deffuse",(f32*)&float3(1.0f,1.0f,1.0f),3);

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		d_vs->SetValue("_world_matrix",(f32*)&sprite_objects_[i]->GetMatrix(),16);
		d_ps->SetTexture("_color_sampler",color_textures_[i]->GetTexture());
		d_ps->SetTexture("_normal_sampler",normal_textures_[i]->GetTexture());
		d_ps->SetTexture("_position_sampler",position_textures_[i]->GetTexture());
		sprite_objects_[i]->Draw();
	}

#ifdef _DEBUG 
	static int _debugRenderTargetIndex = 0;

	LPDIRECT3DTEXTURE9 tex[3];
	tex[0] = color_textures_[debug_player_number_]->GetTexture();
	tex[1] = normal_textures_[debug_player_number_]->GetTexture();
	tex[2] = position_textures_[debug_player_number_]->GetTexture();

	if(GET_INPUT_KEYBOARD()->GetTrigger(DIK_0) == true)
	{
		debugRenderTarget_ = !debugRenderTarget_;
	}

	if(debugRenderTarget_ == true)
	{
		if(GET_INPUT_KEYBOARD()->GetTrigger(DIK_LEFT) == true)
		{
			_debugRenderTargetIndex--;

			if(_debugRenderTargetIndex == -1)
			{
				_debugRenderTargetIndex = 0;
			}
		}
		if(GET_INPUT_KEYBOARD()->GetTrigger(DIK_RIGHT) == true)
		{
			_debugRenderTargetIndex++;

			if(_debugRenderTargetIndex == 3)
			{
				_debugRenderTargetIndex = 2;
			}
		}

		if(GET_INPUT_KEYBOARD()->GetTrigger(DIK_1))
		{
			debug_player_number_ = 0;
		}

		if(GET_INPUT_KEYBOARD()->GetTrigger(DIK_2))
		{
			debug_player_number_ = 1;
		}

		if(GET_INPUT_KEYBOARD()->GetTrigger(DIK_3))
		{
			debug_player_number_ = 2;
		}

		if(GET_INPUT_KEYBOARD()->GetTrigger(DIK_4))
		{
			debug_player_number_ = 3;
		}

		graphic_device->SetVertexShader(d_vs);
		graphic_device->SetPixelShader(d_ps);

		d_vs->SetValue("_view_matrix",(f32*)&observer_2d_->GetViewMatrix(),sizeof(float4x4));
		d_vs->SetValue("_projection_matrix",(f32*)&observer_2d_->GetProjectionMatrix(),sizeof(float4x4));
		d_vs->SetValue("_world_matrix",(f32*)&debug_object_->GetMatrix(),sizeof(float4x4));

		d_ps->SetValue("_light_vector",(f32*)&float3(0.0f,-1.0f,0.0f),sizeof(float3));
		d_ps->SetValue("_light_deffuse",(f32*)&float3(1.0f,1.0f,1.0f),sizeof(float3));
		d_ps->SetTexture("_color_sampler",color_textures_[debug_player_number_]->GetTexture());
		d_ps->SetTexture("_normal_sampler",normal_textures_[debug_player_number_]->GetTexture());
		d_ps->SetTexture("_position_sampler",position_textures_[debug_player_number_]->GetTexture());

		debug_object_->Draw();

		graphic_device->SetVertexShader(basic_vs);
		graphic_device->SetPixelShader(basic_ps);

		basic_vs->SetValue("_view_matrix",(f32*)&observer_2d_->GetViewMatrix(),sizeof(float4x4));
		basic_vs->SetValue("_projection_matrix",(f32*)&observer_2d_->GetProjectionMatrix(),sizeof(float4x4));
		basic_vs->SetValue("_world_matrix",(f32*)&debug_sprite_object_->GetMatrix(),sizeof(float4x4));

		basic_ps->SetTexture("_texture_sampler",tex[_debugRenderTargetIndex]);

		debug_sprite_object_->Draw();
	}
#endif

}
