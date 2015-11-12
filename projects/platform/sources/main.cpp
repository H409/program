//*****************************************************************************
//
// main
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "main.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "render/mesh/mesh_format.h"
#include "render/mesh/mesh_buffer.h"
#include "math/math.h"
#include "system/input_keyboard.h"
#include "system/input_mouse.h"
#include "scene/base/scene_manager.h"

// HACK
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

//=============================================================================
// エントリーポイント
//=============================================================================
int main(int argc,char* argv)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	auto win_system = WinSystem::GetInstance();
	auto graphic_device = GET_GRAPHIC_DEVICE();
	bool is_loop = true;
	auto& scene_manager = SceneManager::Instance();

	win_system->SetCallbacks(WinSystem::EVENT::STOP,{ [&is_loop] {is_loop = false;} });

	auto vertex_shader = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto pixel_shader = graphic_device->LoadPixelShader("resources/shader/basic.psc");

	auto observer = std::make_shared<FollowerObserver>(utility::math::ToRadian(60.0f),800.0f,600.0f);
	observer->SetPosition(float3(0.0f,0.0f,0.0f));
	observer->SetVector(float3(0.0f,0.0f,-1.0f));
	observer->SetLength(5.0f);
	observer->SetHeight(5.0f);
	observer->Update();

	auto sprite = std::make_shared<mesh::Sprite>(float2(800,600));
	auto observer_2d = std::make_shared<Observer2D>(800.0f,600.0f);

	auto directx9 = GET_DIRECTX9_DEVICE();

	auto color_texture = graphic_device->CreateTexture(800,600,D3DFMT_A8R8G8B8);
	auto normal_texture = graphic_device->CreateTexture(800,600,D3DFMT_A16B16G16R16F);
	auto position_texture = graphic_device->CreateTexture(800,600,D3DFMT_A32B32G32R32F);

	auto default_texture = graphic_device->GetRenderTarget(0);
	auto sprite_object = std::make_shared<MeshObject>(sprite);
	sprite->SetAnchorPoint(float2(0.0f,0.0f));

	auto gb_vs = graphic_device->LoadVertexShader("resources/shader/graphics_buffer.vsc");
	auto gb_ps = graphic_device->LoadPixelShader("resources/shader/graphics_buffer.psc");

	auto d_vs = graphic_device->LoadVertexShader("resources/shader/deferred.vsc");
	auto d_ps = graphic_device->LoadPixelShader("resources/shader/deferred.psc");
	auto field = std::make_shared<Field>();

	sprite_object->SetPosition(-0.5f,-0.5f,0.0f);

	auto field_icon = std::make_shared<FieldIcon>();

	while(is_loop)
	{
		auto start_time = std::chrono::system_clock::now();

		GET_INPUT_KEYBOARD()->Update();
		GET_INPUT_MOUSE()->Update();

		scene_manager.Update();

		field_icon->SetFrontVector(float3(0.0f,0.0f,-1.0f));
		field_icon->Update();

		field->GetType(field_icon->GetPosition());
		graphic_device->BeginRendering();

		scene_manager.Draw();

		graphic_device->SetRenderTarget(0,color_texture);
		graphic_device->SetRenderTarget(1,normal_texture);
		graphic_device->SetRenderTarget(2,position_texture);

		graphic_device->Clear(float4(0.0f,0.0f,0.0f,0.0f),1.0f);

		// set shader
		graphic_device->SetVertexShader(gb_vs);
		graphic_device->SetPixelShader(gb_ps);
		//graphic_device->SetVertexShader(vertex_shader);
		//graphic_device->SetPixelShader(pixel_shader);

		// observer
		gb_vs->SetValue("_view_matrix",(f32*)&observer->GetViewMatrix(),sizeof(float4x4));
		gb_vs->SetValue("_projection_matrix",(f32*)&observer->GetProjectionMatrix(),sizeof(float4x4));
		//vertex_shader->SetValue("_view_matrix",(f32*)&observer->GetViewMatrix(),sizeof(float4x4));
		//vertex_shader->SetValue("_projection_matrix",(f32*)&observer->GetProjectionMatrix(),sizeof(float4x4));


		auto object = field->GetObject();

		auto view_matrix = observer->GetViewMatrix();
		auto i_view_matrix = utility::math::InverseT(view_matrix);
		auto world_matrix = object->GetMatrix();

		gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,sizeof(float4x4));
		gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

		object->Draw();

		object = field_icon->GetObject();

		world_matrix = object->GetMatrix();
		world_matrix = utility::math::Multiply(i_view_matrix,world_matrix);

		// object
		gb_vs->SetValue("_world_matrix",(f32*)&world_matrix,sizeof(float4x4));
		gb_ps->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());
		//vertex_shader->SetValue("_world_matrix",(f32*)&object->GetMatrix(),sizeof(float4x4));
		//vertex_shader->SetValue("_color",(f32*)&object->GetColor(),sizeof(float4));
		//pixel_shader->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

		object->Draw();

		graphic_device->SetRenderTarget(0,default_texture);
		graphic_device->SetRenderTarget(1,nullptr);
		graphic_device->SetRenderTarget(2,nullptr);
		graphic_device->SetRenderTarget(3,nullptr);

		graphic_device->Clear(float4(0.0f,0.0f,0.0f,0.0f),1.0f);

		graphic_device->SetVertexShader(d_vs);
		graphic_device->SetPixelShader(d_ps);

		d_vs->SetValue("_view_matrix",(f32*)&observer_2d->GetViewMatrix(),sizeof(float4x4));
		d_vs->SetValue("_projection_matrix",(f32*)&observer_2d->GetProjectionMatrix(),sizeof(float4x4));
		d_vs->SetValue("_world_matrix",(f32*)&sprite_object->GetMatrix(),sizeof(float4x4));

		d_ps->SetValue("_light_vector",(f32*)&float3(0.0f,-1.0f,0.0f),sizeof(float3));
		d_ps->SetValue("_light_deffuse",(f32*)&float3(1.0f,1.0f,1.0f),sizeof(float3));
		d_ps->SetTexture("_color_sampler",color_texture->GetTexture());
		d_ps->SetTexture("_normal_sampler",normal_texture->GetTexture());
		d_ps->SetTexture("_position_sampler",position_texture->GetTexture());
		//vertex_shader->SetValue("_view_matrix",(f32*)&observer_2d->GetViewMatrix(),sizeof(float4x4));
		//vertex_shader->SetValue("_projection_matrix",(f32*)&observer_2d->GetProjectionMatrix(),sizeof(float4x4));
		//vertex_shader->SetValue("_world_matrix",(f32*)&sprite_object->GetMatrix(),sizeof(float4x4));
		//pixel_shader->SetTexture("_texture_sampler",color_texture->GetTexture());

		sprite_object->Draw();

		graphic_device->EndRendering();

		std::this_thread::sleep_until(start_time + std::chrono::milliseconds(1000 / 60));
	}

	return 0;
}

//---------------------------------- EOF --------------------------------------
