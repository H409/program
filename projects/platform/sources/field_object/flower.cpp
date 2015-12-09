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

//=============================================================================
// constructor
//=============================================================================
Flower::Flower(u32 in_number)
	:position_(0.0f,0.0f,0.0f)
	,is_show_(true)
{
	sprite_3d_ = std::make_shared<mesh::Sprite3D>(float2(0.5f,0.5f));
	mesh_object_ = std::make_shared<MeshObject>(sprite_3d_);
	sprite_3d_->SetAnchorPoint(float2(0.5f,0.5f));
	sprite_3d_->Apply();
	height_ = 0.25f;
	SetNumber(in_number);
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
	auto position = float3(position_._x,position_._y + height_,position_._z);
	mesh_object_->SetPosition(position);
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

void Flower::SetNumber(u32 in_number)
{
	SetTexture(in_number);
}

bool Flower::IsShow(void) const
{
	return is_show_;
}

void Flower::SetTexture(u32 in_number)
{
	char work[256] = { 0 };
	int a = rand()%8 + 1;
	sprintf_s(work,"resources/texture/flower_00%d.png",a);
	mesh_object_->SetTexture(0,GET_GRAPHIC_DEVICE()->LoadTexture(work));
}

//---------------------------------- EOF --------------------------------------
