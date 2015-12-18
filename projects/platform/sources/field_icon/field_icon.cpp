//*****************************************************************************
//
// field
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "field_icon.h"
#include "mesh/sprite_3d.h"
#include "object/mesh_object.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "system/input_keyboard.h"
#include "system/input_manager.h"
#include "system/xi_pad.h"
#include "math/math.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
FieldIcon::FieldIcon(void)
	:position_(0.0f,0.0f,1.0f)
	,front_vector_(0.0f,0.0f,1.0f)
	,basic_position_(0.0f,0.0f,0.0f)
	,range_(5.0f)
	,speed_(0.1f)
	,min_(1.0f)
	,is_show_(false)
	,is_show_all_(false)
{
	sprite_3d_ = std::make_shared<mesh::Sprite3D>(float2(0.5f,0.5f));
	mesh_object_ = std::make_shared<MeshObject>(sprite_3d_);
	mesh_object_->SetTexture(0,GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/field_icon.png"));
	sprite_3d_->SetAnchorPoint(float2(0.5f,0.5f));
	sprite_3d_->Apply();
	mesh_object_->SetRotationX(utility::math::ToRadian(90.0f));
}

//=============================================================================
// destructor
//=============================================================================
FieldIcon::~FieldIcon(void)
{
}

//=============================================================================
// update
//=============================================================================
void FieldIcon::Update(void)
{
	auto vector = GetVector_();
	position_ += vector * speed_;

	if(IsOverRange_())
	{
		vector = utility::math::Normalize(position_ - basic_position_);
		position_ = basic_position_ + vector * range_;
	}

	if(utility::math::Length(position_ - basic_position_) < min_)
	{
		vector = utility::math::Normalize(position_ - basic_position_);
		position_ = basic_position_ + vector * min_;
	}

	mesh_object_->SetPosition(float3(position_._x,position_._y + 0.001f,position_._z));
}

//=============================================================================
// get object
//=============================================================================
FieldIcon::TMeshObject FieldIcon::GetObject(void) const
{
	return mesh_object_;
}

//=============================================================================
// set basic position
//=============================================================================
void FieldIcon::SetBasicPosition(const float3& in_position)
{
	auto vector = in_position - basic_position_;
	position_ += vector;
	basic_position_ = in_position;
}

//=============================================================================
// set front vector
//=============================================================================
void FieldIcon::SetFrontVector(const float3& in_front_vector)
{
	front_vector_ = float3(in_front_vector._x,0.0f,in_front_vector._z);
	front_vector_ = utility::math::Normalize(front_vector_);
}

//=============================================================================
// get position
//=============================================================================
const float3& FieldIcon::GetPosition(void)const
{
	return position_;
}

void FieldIcon::Show(bool in_is_show,bool in_is_show_all)
{
	if(!is_show_)
	{
		position_ = basic_position_ + front_vector_ * min_;
	}

	is_show_all_ = in_is_show_all;
	is_show_ = in_is_show;
}

bool FieldIcon::IsShow(void) const
{
	return is_show_;
}

bool FieldIcon::IsShowAll(void) const
{
	return is_show_all_;
}

void FieldIcon::SetRange(f32 in_range)
{
	range_ = in_range;
}

void FieldIcon::SetMin(f32 in_min)
{
	min_ = in_min;
}

void FieldIcon::SetSpeed(f32 in_speed)
{
	speed_ = in_speed;
}

void FieldIcon::SetNumber(u32 in_number)
{
	number_ = in_number;
}

//=============================================================================
// get vector
//=============================================================================
float3 FieldIcon::GetVector_(void) const
{
	auto keyboard = GET_INPUT_KEYBOARD();
	auto xi_pad = GET_INPUT_MANAGER()->GetXIPad(number_);
	auto right_vector = utility::math::CrossProduct(float3(0.0f,1.0f,0.0f),front_vector_);
	auto stick_vector = xi_pad->GetRStick();
	auto vector = front_vector_ * stick_vector._y + right_vector * stick_vector._x;

#ifndef _RELEASE
	if(keyboard->GetPress(DIK_I))
	{
		vector += front_vector_;
	}

	if(keyboard->GetPress(DIK_K))
	{
		vector -= front_vector_;
	}

	if(keyboard->GetPress(DIK_J))
	{
		vector -= right_vector;
	}

	if(keyboard->GetPress(DIK_L))
	{
		vector += right_vector;
	}
#endif 

	vector = utility::math::Normalize(vector);

	return vector;
}

bool FieldIcon::IsOverRange_(void) const
{
	auto vector = position_ - basic_position_;
	auto length = utility::math::Length(vector);
	return range_ < length;
}

//---------------------------------- EOF --------------------------------------
