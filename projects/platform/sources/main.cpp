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

#include "object/object.h"
#include "system/mouseinput.h"
#include "system/keyboardinput.h"

#include "player/player.h"

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

	D3DVERTEXELEMENT9 vertex_elements[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0,sizeof(float3),D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
		D3DDECL_END()
	};
	LPDIRECT3DVERTEXDECLARATION9 vertex_declaration = nullptr;

	directx9->CreateVertexDeclaration(vertex_elements,&vertex_declaration);


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

	auto observer_2d = std::make_shared<Observer2D>(800.0f,600.0f);
	auto observer_3d = std::make_shared<Observer3D>(utility::math::ToRadian(60.0f),800.0f,600.0f);


	//object->SetPositionX(100.0f);
	//object->SetRotationZ(utility::math::ToRadian(-90.0f));
	//object->SetScale(float2(2.0f,2.0f));

	// eyeposition
	D3DXVECTOR3 eye_pos_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	auto player = std::make_shared<Player>( graphic_device->GetDevice() );
	player->Init( float3( 0 , 0 , 0 ) );

	while(is_loop)
	{
		auto start_time = std::chrono::system_clock::now();

		//Get and Update Input Classes
		std::shared_ptr<InputMouse> p_mouse = win_system->GetMouse();
		std::shared_ptr<InputKeyboard> p_keyboard = win_system->GetKeyboard();
		p_mouse->Update();
		p_keyboard->Update();

		//Get Mouse Point Accelelation When Mouse Dragging
		D3DXVECTOR2 point_accelelation = p_mouse->GetDrag(MOUSE_KEY::MOUSE_KEY_RIGHT);

		graphic_device->BeginRendering();

		graphic_device->Clear(float4(1.0f,0.0f,0.0f,1.0f),1.0f);


		float4x4 world_matrix;
		float4x4 view_matrix;
		float4x4 projection_matrix;
		float4 color = float4(1.0f,1.0f,1.0f,1.0f);
		float3 eye = float3(0.0f,0.0f,-5.0f);
		float3 at = float3(0.0f,0.0f,0.0f);
		float3 up = float3(0.0f,1.0f,0.0f);

		//eyepotionsettings
		eye_pos_rot.y += p_mouse->GetDrag(MOUSE_KEY::MOUSE_KEY_RIGHT).x;
		eye_pos_rot.x += p_mouse->GetDrag(MOUSE_KEY::MOUSE_KEY_RIGHT).y;
		eye._x = 0.0f - sinf(eye_pos_rot.y) * -5.0f;
		eye._y = 0.0f - sinf(eye_pos_rot.x) * -5.0f;
		eye._z = 0.0f - cosf(eye_pos_rot.y) * -5.0f;
		

		world_matrix = utility::math::Identity();
		view_matrix = utility::math::Identity();
		//projection_matrix = utility::math::OrthoLH(800.0f,600.0f,1.0f,1000.0f);
		view_matrix = utility::math::LookAtLH(eye,at,up);
		projection_matrix = utility::math::PerspectiveFovLH(utility::math::ToRadian(60.0f),800.0f / 600.0f,1.0f,1000.0f);
		//projection_matrix = utility::math::PerspectiveFovRH(utility::math::ToRadian(60.0f),800.0f / 600.0f,1.0f,1000.0f);


		vertex_shader->SetValue("_world_matrix",(f32*)&world_matrix,sizeof(float4x4));
		vertex_shader->SetValue("_view_matrix",(f32*)&observer_3d->GetViewMatrix(),sizeof(float4x4));
		vertex_shader->SetValue("_projection_matrix",(f32*)&observer_3d->GetProjectionMatrix(),sizeof(float4x4));
		vertex_shader->SetValue("_color",(f32*)&color,sizeof(float4));

		pixel_shader->SetTexture("_texture_sampler",texture->GetTexture());

		directx9->SetVertexShader(vertex_shader->GetShader());
		directx9->SetPixelShader(pixel_shader->GetShader());

		// set texture
		pixel_shader->SetTexture("_texture_sampler",texture->GetTexture());

		// observer
		vertex_shader->SetValue("_view_matrix",(f32*)&observer->GetViewMatrix(),sizeof(float4x4));
		vertex_shader->SetValue("_projection_matrix",(f32*)&observer->GetProjectionMatrix(),sizeof(float4x4));


		player->GetKimPointer()->SetProjection( ( D3DXMATRIX& )observer->GetProjectionMatrix() );
		player->GetKimPointer()->SetView( ( D3DXMATRIX& )observer->GetViewMatrix() );
		player->Update();
		player->Draw();


		graphic_device->EndRendering();

		std::this_thread::sleep_until(start_time + std::chrono::milliseconds(1000 / 60));
	}

	return 0;
}

//---------------------------------- EOF --------------------------------------
