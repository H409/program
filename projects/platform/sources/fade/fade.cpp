//*****************************************************************************
//
// fade
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#include "fade.h"
#include "system/win_system.h"
#include "mesh/sprite.h"
#include "object/mesh_object.h"
#include "observer/observer_2d.h"

Fade::Fade(void)
	:color_(1.0f,1.0f,1.0f)
	,frame_(0)
	,frame_count_(0)
	,alpha_(0.0f)
	,is_work_(false)
{
	auto window = GET_WINDOW();
	auto width = window->GetWidth();
	auto height = window->GetHeight();

	observer_ = std::make_shared<Observer2D>(window->GetWidth(),window->GetHeight());
	sprite_ = std::make_shared<mesh::Sprite>(float2(width,height));
	sprite_->SetAnchorPoint(float2(0.0f,0.0f));
	sprite_->Apply();

	mesh_object_ = std::make_shared<MeshObject>(sprite_);
	mesh_object_->SetPosition(-0.5f,-0.5f,0.0f);

}

Fade::~Fade(void)
{
}

void Fade::Update(void)
{
	if(frame_count_ < frame_)
	{
		frame_count_++;
		switch(type_)
		{
			case TYPE::FADE_IN:
			{
				alpha_ = 1.0f - (f32)frame_count_ / frame_;
				break;
			}

			case TYPE::FADE_OUT:
			{
				alpha_ = (f32)frame_count_ / frame_;
				break;
			}
		}

		if(frame_count_ >= frame_)
		{
			if(callback_)
			{
				callback_();
				callback_ = nullptr;
				is_work_ = false;
			}
		}
	}
}

void Fade::Draw(void)
{
	auto graphic_device = GET_GRAPHIC_DEVICE();

	auto b_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto b_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");

	auto color = float4(color_,alpha_);
	auto world_matrix = mesh_object_->GetMatrix();
	auto view_matrix = observer_->GetViewMatrix();
	auto projection_matrix = observer_->GetProjectionMatrix();

	b_vs->SetValue("_world_matrix",(f32*)&world_matrix,16);
	b_vs->SetValue("_view_matrix",(f32*)&view_matrix,16);
	b_vs->SetValue("_projection_matrix",(f32*)&projection_matrix,16);
	b_vs->SetValue("_color",(f32*)&color,4);
	b_ps->SetTexture("_texture_sampler",mesh_object_->GetTexture(0));

	graphic_device->SetVertexShader(b_vs);
	graphic_device->SetPixelShader(b_ps);

	auto direct3ddevice9 = GET_DIRECTX9_DEVICE();
	direct3ddevice9->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	direct3ddevice9->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	direct3ddevice9->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	mesh_object_->Draw();

	direct3ddevice9->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

}

void Fade::SetColor(const float3& in_color)
{
	color_ = in_color;
}

void Fade::Start(u32 in_frame,TYPE in_type,TCallback in_callback)
{
	frame_count_ = 0;
	frame_ = in_frame;
	type_ = in_type;
	callback_ = in_callback;
	is_work_ = true;
}

bool Fade::IsWork(void) const
{
	return is_work_;
}

//---------------------------------- EOF --------------------------------------
