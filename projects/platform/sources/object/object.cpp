//*****************************************************************************
//
// object
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object.h"
#include "action/action.h"
#include "math/math.h"

//=============================================================================
// constructor
//=============================================================================
Object::Object(void)
	:position_(0.0f,0.0f,0.0f)
	,rotation_(0.0f,0.0f,0.0f)
	,scale_(1.0f,1.0f,1.0f)
{
}

//=============================================================================
// update
//=============================================================================
void Object::Update(void)
{
	action_->Update();
}

//=============================================================================
// run action
//=============================================================================
void Object::RunAction(TAction in_action)
{
	in_action->SetStartPosition(position_);
}

//=============================================================================
// set position
//=============================================================================
void Object::SetPosition(const float3& in_position)
{
	position_ = in_position;
	is_dirty_ = true;
}

//=============================================================================
// set position
//=============================================================================
void Object::SetPosition(const f32 & in_x,const f32 & in_y,const f32 & in_z)
{
	SetPositionX(in_x);
	SetPositionY(in_y);
	SetPositionZ(in_z);
}

//=============================================================================
// set position x
//=============================================================================
void Object::SetPositionX(const f32& in_x)
{
	position_._x = in_x;
	is_dirty_ = true;
}

//=============================================================================
// set position y
//=============================================================================
void Object::SetPositionY(const f32& in_y)
{
	position_._y = in_y;
	is_dirty_ = true;
}

//=============================================================================
// set position z
//=============================================================================
void Object::SetPositionZ(const f32& in_z)
{
	position_._z = in_z;
	is_dirty_ = true;
}

//=============================================================================
// set rotation
//=============================================================================
void Object::SetRotation(const float3& in_rotation)
{
	rotation_ = in_rotation;
	is_dirty_ = true;
}

//=============================================================================
// set rotation
//=============================================================================
void Object::SetRotation(const f32 & in_x,const f32 & in_y,const f32 & in_z)
{
	SetRotationX(in_x);
	SetRotationY(in_y);
	SetRotationZ(in_z);
}

//=============================================================================
// set rotation x
//=============================================================================
void Object::SetRotationX(const f32& in_x)
{
	rotation_._x = in_x;
	is_dirty_ = true;
}

//=============================================================================
// set rotation y
//=============================================================================
void Object::SetRotationY(const f32& in_y)
{
	rotation_._y = in_y;
	is_dirty_ = true;
}

//=============================================================================
// set rotation z
//=============================================================================
void Object::SetRotationZ(const f32& in_z)
{
	rotation_._z = in_z;
	is_dirty_ = true;
}

//=============================================================================
// set scale
//=============================================================================
void Object::SetScale(const float3& in_scale)
{
	scale_ = in_scale;
	is_dirty_ = true;
}

//=============================================================================
// set scale
//=============================================================================
void Object::SetScale(const f32 & in_x,const f32 & in_y,const f32 & in_z)
{
	SetScaleX(in_x);
	SetScaleY(in_y);
	SetScaleZ(in_z);
}

//=============================================================================
// set scale x
//=============================================================================
void Object::SetScaleX(const f32& in_x)
{
	scale_._x = in_x;
	is_dirty_ = true;
}

//=============================================================================
// set scale y
//=============================================================================
void Object::SetScaleY(const f32& in_y)
{
	scale_._y = in_y;
	is_dirty_ = true;
}

//=============================================================================
// set scale z
//=============================================================================
void Object::SetScaleZ(const f32& in_z)
{
	scale_._z = in_z;
	is_dirty_ = true;
}

//=============================================================================
// set color
//=============================================================================
void Object::SetColor(const float3& in_color)
{
	color_._rgb = in_color;
}

//=============================================================================
// set color
//=============================================================================
void Object::SetColor(const f32 & in_red,const f32 & in_green,const f32 & in_blue)
{
	color_._r = in_red;
	color_._g = in_green;
	color_._b = in_blue;
}

//=============================================================================
// set color
//=============================================================================
void Object::SetColor(const float4& in_color)
{
	color_ = in_color;
}

//=============================================================================
// set color
//=============================================================================
void Object::SetColor(const f32 & in_red,const f32 & in_green,const f32 & in_blue,const f32 & in_alpha)
{
	SetColor(in_red,in_green,in_blue);
	color_._a = in_red;
}

//=============================================================================
// get position
//=============================================================================
const float3& Object::GetPosition(void)const
{
	return position_;
}

//=============================================================================
// get position x
//=============================================================================
const f32& Object::GetPositionX(void)const
{
	return position_._x;
}

//=============================================================================
// get position y
//=============================================================================
const f32& Object::GetPositionY(void)const
{
	return position_._y;
}

//=============================================================================
// get position z
//=============================================================================
const f32& Object::GetPositionZ(void)const
{
	return position_._z;
}

//=============================================================================
// get rotation
//=============================================================================
const float3& Object::GetRotation(void)const
{
	return rotation_;
}

//=============================================================================
// get rotation x
//=============================================================================
const f32& Object::GetRotationX(void)const
{
	return rotation_._x;
}

//=============================================================================
// get rotation y
//=============================================================================
const f32& Object::GetRotationY(void)const
{
	return rotation_._y;
}

//=============================================================================
// get rotation z
//=============================================================================
const f32& Object::GetRotationZ(void)const
{
	return rotation_._z;
}

//=============================================================================
// get scale
//=============================================================================
const float3& Object::GetScale(void)const
{
	return scale_;
}

//=============================================================================
// get scale x
//=============================================================================
const f32& Object::GetScaleX(void)const
{
	return scale_._x;
}

//=============================================================================
// get scale y
//=============================================================================
const f32& Object::GetScaleY(void)const
{
	return scale_._y;
}

//=============================================================================
// get scale z
//=============================================================================
const f32& Object::GetScaleZ(void)const
{
	return scale_._z;
}

//=============================================================================
// get color
//=============================================================================
const float4& Object::GetColor(void) const
{
	return color_;
}

//=============================================================================
// get color rgb
//=============================================================================
const float3& Object::GetColorRGB(void) const
{
	return color_._rgb;
}

//=============================================================================
// get color red
//=============================================================================
const f32& Object::GetColorRed(void) const
{
	return color_._r;
}

//=============================================================================
// get color green
//=============================================================================
const f32& Object::GetColorGreen(void) const
{
	return color_._g;
}

//=============================================================================
// get color blue
//=============================================================================
const f32& Object::GetColorBlue(void) const
{
	return color_._b;
}

//=============================================================================
// get color alpha
//=============================================================================
const f32& Object::GetColorAlpha(void) const
{
	return color_._a;
}

//=============================================================================
// get matrix
//=============================================================================
const float4x4& Object::GetMatrix(void)
{
	if(is_dirty_)
	{
		float4x4 tlanslation_matrix = utility::math::Tlanslation(position_);
		float4x4 rotation_matrix = utility::math::YawPitchRoll(rotation_);
		float4x4 scale_matrix = utility::math::Scaling(scale_);

		matrix_ = utility::math::Multiply(utility::math::Multiply(scale_matrix,rotation_matrix),tlanslation_matrix);

		is_dirty_ = false;
	}

	return matrix_;
}

//=============================================================================
// get matrix
//=============================================================================
const float4x4& Object::GetMatrix(void)const
{
	return matrix_;
}

//---------------------------------- EOF --------------------------------------
