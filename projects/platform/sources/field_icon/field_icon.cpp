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
#include "math/math.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
FieldIcon::FieldIcon(void)
	:position_(0.0f,0.0f,0.0f)
	,front_vector_(0.0f,0.0f,1.0f)
{
	sprite_3d_ = std::make_shared<mesh::Sprite3D>(float2(1.0f,2.0f));
	mesh_object_ = std::make_shared<MeshObject>(sprite_3d_);
	mesh_object_->SetTexture(0,GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/test.png"));
	sprite_3d_->SetAnchorPoint(float2(0.5f,1.0f));
	sprite_3d_->Apply();
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
	auto keyboard = GET_INPUT_KEYBOARD();

	auto right_vector = utility::math::CrossProduct(float3(0.0f,1.0f,0.0f),front_vector_);

	if(keyboard->GetPress(DIK_I))
	{
		position_ += front_vector_;
	}

	if(keyboard->GetPress(DIK_K))
	{
		position_ -= front_vector_;
	}

	if(keyboard->GetPress(DIK_J))
	{
		position_ -= right_vector;
	}

	if(keyboard->GetPress(DIK_L))
	{
		position_ += right_vector;
	}
	mesh_object_->SetPosition(position_);
}

//=============================================================================
// get object
//=============================================================================
FieldIcon::TMeshObject FieldIcon::GetObject(void) const
{
	return mesh_object_;
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
const float3 FieldIcon::GetPosition(void) const
{
	return position_;
}

//---------------------------------- EOF --------------------------------------
