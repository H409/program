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
#include "object/object.h"
#include "mesh/mesh_sprite_3d.h"
#include "action/move_to.h"
#include "action/move_by.h"
#include "action/sequence.h"
#include "action/callback.h"
#include "action/spawn.h"


#include "fbx/scene_kim.h"

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

	auto observer = std::make_shared<FollowerObserver>(utility::math::ToRadian(60.0f),800.0f,600.0f);
	observer->SetPosition(float3(0.0f,0.0f,0.0f));
	observer->SetVector(float3(0.0f,0.0f,1.0f));
	observer->SetLength(5.0f);
	observer->SetHeight(5.0f);
	observer->Update();
	auto aa = observer->GetViewMatrix();

	//ビューマトリックスの設定
	graphic_device->GetDevice()->SetTransform(D3DTS_VIEW,( D3DMATRIX* )&observer->GetViewMatrix());
	graphic_device->GetDevice()->SetTransform(D3DTS_PROJECTION,( D3DMATRIX* )&observer->GetProjectionMatrix());


	auto move_to = std::make_shared<action::MoveTo>(180,float3(0.0f,0.0f,10.0f));
	auto move_by = std::make_shared<action::MoveBy>(180,float3(-1.0f,0.0f,0.0f),1.0f);
	auto move_by_ = std::make_shared<action::MoveBy>(180,float3(0.0f,0.0f,1.0f),1.0f);
	auto sequence = std::make_shared<action::Sequence>(move_to,move_by);
	auto spaw = std::make_shared<action::Spawn>(move_by_,move_by);
	sequence->SetStartPosition(float3(10.0f,0.0f,0.0f));
	spaw->SetStartPosition(float3(10.0f,0.0f,0.0f));

	auto _kim = SCENE_KIM::Create( graphic_device->GetDevice() , "resources/model/ZZI_taiki4.kim" );
	
	while(is_loop)
	{
		auto start_time = std::chrono::system_clock::now();

		graphic_device->BeginRendering();

		graphic_device->Clear(float4(1.0f,0.0f,0.0f,1.0f),1.0f);

		float4x4 world_matrix;
		float4 color = float4(1.0f,1.0f,1.0f,1.0f);

		sequence->Update();
		spaw->Update();
		observer->SetPosition(spaw->GetPosition());
		observer->Update();
		world_matrix = utility::math::Identity();

		world_matrix = object->GetMatrix();

		vertex_shader->SetValue("_world_matrix",(f32*)&world_matrix,sizeof(float4x4));
		vertex_shader->SetValue("_view_matrix",(f32*)&observer->GetViewMatrix(),sizeof(float4x4));
		vertex_shader->SetValue("_projection_matrix",(f32*)&observer->GetProjectionMatrix(),sizeof(float4x4));
		vertex_shader->SetValue("_color",(f32*)&color,sizeof(float4));

		pixel_shader->SetTexture("_texture_sampler",texture->GetTexture());
		directx9->SetVertexShader(vertex_shader->GetShader());
		directx9->SetPixelShader(pixel_shader->GetShader());

		directx9->SetVertexDeclaration(vertex_declaration);
		directx9->SetStreamSource(0,sprite->GetBuffer(),0,sprite->GetStride());
		directx9->SetIndices(sprite->GetIndexBuffer());
		directx9->DrawIndexedPrimitive(sprite->GetPrimitiveType(),0,0,sprite->GetVertexCount(),0,sprite->GetPrimitiveCount());
		directx9->DrawPrimitive(sprite->GetPrimitiveType(),0,sprite->GetPrimitiveCount());




		D3DXMATRIX world , mtxScl , mtxPos ;
		D3DXVECTOR3 scl( 0.025f , 0.025f , 0.025f );
		static D3DXVECTOR3 pos( 0.025f , 0.025f , 0.025f );


		if( GetAsyncKeyState('W') )
		{
			pos.z += 0.05f ;
		}
		if( GetAsyncKeyState('S') )
		{
			pos.z -= 0.05f ;
		}
		if( GetAsyncKeyState('A') )
		{
			pos.x += 0.05f ;
		}
		if( GetAsyncKeyState('D') )
		{
			pos.x -= 0.05f ;
		}
		D3DXMatrixIdentity( &world );

		//--  スケールの反映  --//
		D3DXMatrixScaling( &mtxScl , scl.x , scl.y , scl.z );
		D3DXMatrixMultiply( &world , &world , &mtxScl );	//行列の掛け算

		//--  位置の反映  --//
		D3DXMatrixTranslation( &mtxPos , pos.x , pos.y , pos.z );
		D3DXMatrixMultiply( &world , &world , &mtxPos );	//行列の掛け算

		_kim->Update();
		_kim->SetWorld( world );
		_kim->Draw();

		graphic_device->EndRendering();

		std::this_thread::sleep_until(start_time + std::chrono::milliseconds(1000 / 60));
	}

	SafeRelease(vertex_declaration);

	return 0;
}

//---------------------------------- EOF --------------------------------------
