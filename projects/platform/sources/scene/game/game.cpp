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
#include "system/input_manager.h"
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

//=============================================================================
// constructor
//=============================================================================
Game::Game()
{
	auto graphic_device = GET_GRAPHIC_DEVICE();

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		observers_[i] = std::make_shared<FollowerObserver>(utility::math::ToRadian(60.0f),800.0f,600.0f);
		observers_[i]->SetTargetPosition(float3(0.0f,0.0f,0.0f));
		observers_[i]->SetTargetVector(float3(0.0f,0.0f,1.0f));
		observers_[i]->SetLength(5.0f);
		observers_[i]->SetHeight(5.0f);
		observers_[i]->Update();
	}

	observer_2d_ = std::make_shared<Observer2D>(800.0f,600.0f);

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		color_textures_[i] = graphic_device->CreateTexture(800,600,D3DFMT_A8R8G8B8);
		normal_textures_[i] = graphic_device->CreateTexture(800,600,D3DFMT_A16B16G16R16F);
		position_textures_[i] = graphic_device->CreateTexture(800,600,D3DFMT_A32B32G32R32F);
	}

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		field_icons_[i] = std::make_shared<FieldIcon>();
	}

	float2 positions[]
	{
		float2(  0.0f,  0.0f),
		float2(400.0f,  0.0f),
		float2(  0.0f,300.0f),
		float2(400.0f,300.0f),
	};
	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		auto sprite = std::make_shared<mesh::Sprite>(float2(400,300));
		sprite_objects_[i] = std::make_shared<MeshObject>(sprite);
		sprite->SetAnchorPoint(float2(0.0f,0.0f));
		sprite_objects_[i]->SetPosition(positions[i]._x  - 0.5f,positions[i]._y - 0.5f,0.0f);
	}

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		players_[i] = std::make_shared<Player>(graphic_device->GetDevice());
	}

	field_ = std::make_shared<Field>();

#ifdef _DEBUG
	debug_player_number_ = 0;
	auto sprite = std::make_shared<mesh::Sprite>(float2(200,150));
	debug_sprite_object_ = std::make_shared<MeshObject>(sprite);
	debug_sprite_object_->SetPosition(-0.5f,-0.5f,0.0f);
	sprite = std::make_shared<mesh::Sprite>(float2(800,600));
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
	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		players_[i]->Init(float3(0.0f,0.0f,0.0f));
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
	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		players_[i]->SetCameraVector(observers_[i]->GetFrontVector());
		players_[i]->Update();

		auto front_vector = observers_[i]->GetFrontVector();
		field_icons_[i]->SetFrontVector(front_vector);
		field_icons_[i]->SetBasicPosition(players_[i]->GetPosition());
		field_icons_[i]->Update();

		if(GET_INPUT_KEYBOARD()->GetTrigger(DIK_SPACE))
		{
			// Ží‚Ü‚«
			{
				auto start_position = players_[i]->GetPosition();
				start_position._y += 2.0f;
				auto end_position = field_->GetBlockPosition(field_icons_[i]->GetPosition());

				auto is_create = true;

				for(auto bullet : bullets_)
				{
					if(bullet->IsDeath())
					{
						bullet->Reset(start_position,end_position);
						is_create = false;
						break;
					}
				}

				if(is_create)
				{
					bullets_.push_back(std::make_shared<Bullet>(start_position,end_position));
				}
			}

			// Œ@‚è•Ô‚µ
			{
				auto position = players_[i]->GetPosition();
				if(field_->GetType(position) == 2)
				{
					field_->SetType(position,1);
				}
			}
		}

		auto icon_position = field_icons_[i]->GetPosition();
		auto player_position = players_[i]->GetPosition();

		if(field_->GetBlockIndex(icon_position) == field_->GetBlockIndex(player_position))
		{
		}
		observers_[i]->SetTargetPosition(players_[i]->GetPosition());
		observers_[i]->SetTargetVector(float3(sinf(players_[i]->GetRotation()._y),0,cosf(players_[i]->GetRotation()._y)));
		observers_[i]->Update();
	}

	field_->Update();

	for(auto bullet : bullets_)
	{
		bullet->Update();
	}

	// 
	for(auto bullet : bullets_)
	{
		if(!bullet->IsDeath())
		{
			auto position = bullet->GetPosition();
			if(position._y <= 0.0f)
			{
				if(field_->GetType(position) == 1)
				{
					field_->SetType(position,2);
				}
				bullet->Remove();
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

	auto default_texture = graphic_device->GetRenderTarget(0);

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		graphic_device->SetRenderTarget(0,color_textures_[i]);
		graphic_device->SetRenderTarget(1,normal_textures_[i]);
		graphic_device->SetRenderTarget(2,position_textures_[i]);

		graphic_device->Clear(float4(1.0f,0.0f,0.0f,0.0f),1.0f);

		field_->SelectBlock(field_icons_[i]->GetPosition());

		// set shader
		graphic_device->SetVertexShader(gb_vs);
		graphic_device->SetPixelShader(gb_ps);

		// observer
		gb_vs->SetValue("_view_matrix",(f32*)&observers_[i]->GetViewMatrix(),sizeof(float4x4));
		gb_vs->SetValue("_projection_matrix",(f32*)&observers_[i]->GetProjectionMatrix(),sizeof(float4x4));

		auto object = field_->GetObject();

		auto view_matrix = observers_[i]->GetViewMatrix();
		auto i_view_matrix = utility::math::InverseB(view_matrix);
		auto world_matrix = object->GetMatrix();

		gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,sizeof(float4x4));
		gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

		object->Draw();

		object = field_icons_[i]->GetObject();

		world_matrix = object->GetMatrix();
		world_matrix = utility::math::Multiply(i_view_matrix,world_matrix);

		// object
		gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,sizeof(float4x4));
		gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

		object->Draw();

		for(auto bullet : bullets_)
		{
			if(!bullet->IsDeath())
			{
				object = bullet->GetObject();
				world_matrix = object->GetMatrix();
				world_matrix = utility::math::Multiply(i_view_matrix,world_matrix);

				gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,sizeof(float4x4));
				gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

				object->Draw();
			}
		}

		players_[i]->GetKimPointer()->SetView((D3DXMATRIX*)&observers_[i]->GetViewMatrix());
		players_[i]->GetKimPointer()->SetProjection((D3DXMATRIX*)&observers_[i]->GetProjectionMatrix());
		players_[i]->Draw();
	}

	graphic_device->SetRenderTarget(0,default_texture);
	graphic_device->SetRenderTarget(1,nullptr);
	graphic_device->SetRenderTarget(2,nullptr);
	graphic_device->SetRenderTarget(3,nullptr);

	graphic_device->Clear(float4(0.0f,0.0f,0.0f,0.0f),1.0f);

	for(u32 i = 0;i < PLAYER_MAX;++i)
	{
		graphic_device->SetVertexShader(d_vs);
		graphic_device->SetPixelShader(d_ps);

		d_vs->SetValue("_view_matrix",(f32*)&observer_2d_->GetViewMatrix(),sizeof(float4x4));
		d_vs->SetValue("_projection_matrix",(f32*)&observer_2d_->GetProjectionMatrix(),sizeof(float4x4));
		d_vs->SetValue("_world_matrix",(f32*)&sprite_objects_[i]->GetMatrix(),sizeof(float4x4));

		d_ps->SetValue("_light_vector",(f32*)&float3(0.0f,-1.0f,0.0f),sizeof(float3));
		d_ps->SetValue("_light_deffuse",(f32*)&float3(1.0f,1.0f,1.0f),sizeof(float3));
		d_ps->SetTexture("_color_sampler",color_textures_[i]->GetTexture());
		d_ps->SetTexture("_normal_sampler",normal_textures_[i]->GetTexture());
		d_ps->SetTexture("_position_sampler",position_textures_[i]->GetTexture());

		sprite_objects_[i]->Draw();
	}

#ifdef _DEBUG 
	static bool _debugRenderTarget = false;
	static int _debugRenderTargetIndex = 0;

	LPDIRECT3DTEXTURE9 tex[3];
	tex[0] = color_textures_[debug_player_number_]->GetTexture();
	tex[1] = normal_textures_[debug_player_number_]->GetTexture();
	tex[2] = position_textures_[debug_player_number_]->GetTexture();

	if(GET_INPUT_KEYBOARD()->GetTrigger(DIK_0) == true)
	{
		_debugRenderTarget = !_debugRenderTarget;
	}

	if(_debugRenderTarget == true)
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
