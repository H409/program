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
#include "mesh/sprite_3d.h"
#include "object/object.h"
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

	D3DVERTEXELEMENT9 vertex_elements[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0,sizeof(float3),D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
		D3DDECL_END()
	};
	LPDIRECT3DVERTEXDECLARATION9 vertex_declaration = nullptr;

	directx9->CreateVertexDeclaration(vertex_elements,&vertex_declaration);

	auto sprite = std::make_shared<mesh::MeshSprite3D>(10,10);

	auto texture = graphic_device->LoadTexture("resources/texture/test.png");

	auto vertex_shader = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto pixel_shader = graphic_device->LoadPixelShader("resources/shader/basic.psc");

	auto observer_2d = std::make_shared<Observer2D>(800.0f,600.0f);
	auto observer_3d = std::make_shared<Observer3D>(utility::math::ToRadian(60.0f),800.0f,600.0f);

	auto object = std::make_shared<Object>();

	//object->SetPositionX(100.0f);
	//object->SetRotationZ(utility::math::ToRadian(-90.0f));
	//object->SetScale(float2(2.0f,2.0f));
	while(is_loop)
	{
		auto start_time = std::chrono::system_clock::now();

		graphic_device->BeginRendering();

		graphic_device->Clear(float4(1.0f,0.0f,0.0f,1.0f),1.0f);

		float4x4 world_matrix;
		float4x4 view_matrix;
		float4x4 projection_matrix;
		float4 color = float4(1.0f,1.0f,1.0f,1.0f);
		float3 eye = float3(0.0f,0.0f,-5.0f);
		float3 at = float3(0.0f,0.0f,0.0f);
		float3 up = float3(0.0f,1.0f,0.0f);

		world_matrix = utility::math::Identity();
		view_matrix = utility::math::Identity();
		//projection_matrix = utility::math::OrthoLH(800.0f,600.0f,1.0f,1000.0f);
		view_matrix = utility::math::LookAtLH(eye,at,up);
		projection_matrix = utility::math::PerspectiveFovLH(utility::math::ToRadian(60.0f),800.0f / 600.0f,1.0f,1000.0f);
		//projection_matrix = utility::math::PerspectiveFovRH(utility::math::ToRadian(60.0f),800.0f / 600.0f,1.0f,1000.0f);

		world_matrix = object->GetMatrix();

		vertex_shader->SetValue("_world_matrix",(f32*)&world_matrix,sizeof(float4x4));
		vertex_shader->SetValue("_view_matrix",(f32*)&observer_3d->GetViewMatrix(),sizeof(float4x4));
		vertex_shader->SetValue("_projection_matrix",(f32*)&observer_3d->GetProjectionMatrix(),sizeof(float4x4));
		vertex_shader->SetValue("_color",(f32*)&color,sizeof(float4));

		pixel_shader->SetTexture("_texture_sampler",texture->GetTexture());
		directx9->SetVertexShader(vertex_shader->GetShader());
		directx9->SetPixelShader(pixel_shader->GetShader());

		directx9->SetVertexDeclaration(vertex_declaration);
		directx9->SetStreamSource(0,sprite->GetBuffer(),0,sprite->GetStride());
		directx9->SetIndices(sprite->GetIndexBuffer());
		directx9->DrawIndexedPrimitive(sprite->GetPrimitiveType(),0,0,sprite->GetVertexCount(),0,sprite->GetPrimitiveCount());
		//directx9->DrawPrimitive(sprite->GetPrimitiveType(),0,sprite->GetPrimitiveCount());

		graphic_device->EndRendering();

		std::this_thread::sleep_until(start_time + std::chrono::milliseconds(1000 / 60));
	}

	SafeRelease(vertex_declaration);

	return 0;
}

//---------------------------------- EOF --------------------------------------
