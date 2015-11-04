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

// HACK
#include "shader/dx9_vertex_shader.h"
#include "shader/dx9_pixel_shader.h"
#include "texture/dx9_texture.h"
#include "mesh/sprite.h"
#include "observer/observer_2d.h"
#include "observer/observer_3d.h"
#include "observer/follower_observer.h"
#include "mesh/sprite_3d.h"
#include "object/mesh_object.h"
#include "mesh/mesh_sprite_3d.h"

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

	win_system->SetCallbacks(WinSystem::EVENT::STOP,{ [&is_loop] {is_loop = false;} });

	auto directx9 = GET_DIRECTX9_DEVICE();
	auto sprite = std::make_shared<mesh::MeshSprite3D>(10,10);
	auto texture = graphic_device->LoadTexture("resources/texture/test.png");
	auto vertex_shader = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto pixel_shader = graphic_device->LoadPixelShader("resources/shader/basic.psc");
	auto observer = std::make_shared<FollowerObserver>(utility::math::ToRadian(60.0f),800.0f,600.0f);
	observer->SetPosition(float3(0.0f,0.0f,0.0f));
	observer->SetVector(float3(0.0f,0.0f,1.0f));
	observer->SetLength(5.0f);
	observer->SetHeight(5.0f);
	observer->Update();
	auto object = std::make_shared<MeshObject>(sprite);

	object->SetTexture(0,texture);

	while(is_loop)
	{
		auto start_time = std::chrono::system_clock::now();

		graphic_device->BeginRendering();

		graphic_device->Clear(float4(1.0f,0.0f,0.0f,1.0f),1.0f);

		// set shader
		directx9->SetVertexShader(vertex_shader->GetShader());
		directx9->SetPixelShader(pixel_shader->GetShader());

		// observer
		vertex_shader->SetValue("_view_matrix",(f32*)&observer->GetViewMatrix(),sizeof(float4x4));
		vertex_shader->SetValue("_projection_matrix",(f32*)&observer->GetProjectionMatrix(),sizeof(float4x4));

		// object
		vertex_shader->SetValue("_world_matrix",(f32*)&object->GetMatrix(),sizeof(float4x4));
		vertex_shader->SetValue("_color",(f32*)&object->GetColor(),sizeof(float4));
		pixel_shader->SetTexture("_texture_sampler",object->GetTexture(0)->GetTexture());

		object->Draw();

		graphic_device->EndRendering();

		std::this_thread::sleep_until(start_time + std::chrono::milliseconds(1000 / 60));
	}

	return 0;
}

//---------------------------------- EOF --------------------------------------
