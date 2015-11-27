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
#include "flower.h"
#include "mesh/sprite_3d.h"
#include "object/mesh_object.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "system/input_keyboard.h"
#include "system/input_manager.h"
#include "math/math.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
Flower::Flower(void)
	:position_(0.0f,0.0f,0.0f)
	,is_show_(true)
{
	sprite_3d_ = std::make_shared<mesh::Sprite3D>(float2(0.5f,0.5f));
	mesh_object_ = std::make_shared<MeshObject>(sprite_3d_);
	mesh_object_->SetTexture(0,GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/flower.png"));
	sprite_3d_->SetAnchorPoint(float2(0.5f,0.5f));
	sprite_3d_->Apply();
	height_ = 0.25f;
}

//=============================================================================
// destructor
//=============================================================================
Flower::~Flower(void)
{
}

//=============================================================================
// update
//=============================================================================
void Flower::Update(void)
{
	auto position = float3(position_._x,position_._y + height_,position_._z);
	mesh_object_->SetPosition(position);
}

//=============================================================================
// get object
//=============================================================================
Flower::TMeshObject Flower::GetObject(void) const
{
	return mesh_object_;
}

//=============================================================================
// set position
//=============================================================================
void Flower::SetPosition(const float3& in_position)
{
	position_ = in_position;
}

//=============================================================================
// get position
//=============================================================================
const float3& Flower::GetPosition(void)const
{
	return position_;
}

void Flower::Show(bool in_is_show)
{
	is_show_ = in_is_show;
}

bool Flower::IsShow(void) const
{
	return is_show_;
}

//---------------------------------- EOF --------------------------------------
