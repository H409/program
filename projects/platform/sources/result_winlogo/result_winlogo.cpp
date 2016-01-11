//*****************************************************************************
//
// result_winlogo
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "result_winlogo.h"
#include "mesh/sprite.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "object/mesh_object.h"
#include "shader/dx9_vertex_shader.h"
#include "shader/dx9_pixel_shader.h"
//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
ResultWinLogo::ResultWinLogo(void)
{
	//�X�R�A�w�i�̐ݒ�
	size_._x = GET_DEFAULT_DISPLAY_SIZE()._x / 5;
	size_._y = GET_DEFAULT_DISPLAY_SIZE()._y / 5;

	//�X�R�A�\���w�i������
	sprite_ = std::make_shared<mesh::Sprite>(size_);
	sprite_->SetAnchorPoint(float2(0.5f, 1.0f));
	object_ = std::make_shared<MeshObject>(sprite_);
	object_->SetTexture(0, GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/window_256x384.png"));
	object_->SetPosition(GET_DEFAULT_DISPLAY_SIZE()._x * 0.5f-size_._x/2.0f, GET_DEFAULT_DISPLAY_SIZE()._y * 0.75f, 0.0f);
}

//=============================================================================
// destructor
//=============================================================================
ResultWinLogo::~ResultWinLogo(void)
{

}
//=============================================================================
// update
//=============================================================================
void ResultWinLogo::Update(void)
{

	if (state_ == STATE::NEUTRAL)
	{

	}
	else if (state_ == STATE::MOVE)
	{
	
	}
	else if (state_ == STATE::MOVED)
	{

	}
}
//=============================================================================
// draw
//=============================================================================
void ResultWinLogo::Draw(void)
{
	//�V�F�[�_�[���擾
	auto graphic_device = GET_GRAPHIC_DEVICE();
	auto basic_vs = graphic_device->LoadVertexShader("resources/shader/basic.vsc");
	auto basic_ps = graphic_device->LoadPixelShader("resources/shader/basic.psc");


	basic_vs->SetValue("_world_matrix", (f32*)&object_->GetMatrix(), sizeof(float4x4));	//�V�F�[�_�[�ɒl��ݒ�
	basic_ps->SetTexture("_texture_sampler", object_->GetTexture(0));

	object_->Draw();

}