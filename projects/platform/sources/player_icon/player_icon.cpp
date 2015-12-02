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
#include "player_icon.h"
#include "mesh/sprite_3d.h"
#include "object/mesh_object.h"
#include "system/win_system.h"
#include "dx9_device.h"
#include "math/math.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
PlayerIcon::PlayerIcon(u32 in_number)
	:position_(0.0f,0.0f,1.0f)
	,number_(in_number)
{
	sprite_3d_ = std::make_shared<mesh::Sprite3D>(float2(0.5f,0.5f));
	mesh_object_ = std::make_shared<MeshObject>(sprite_3d_);

	char work[256];
	sprintf_s(work,"resources/texture/marker_0%d.png",number_ + 1);
	mesh_object_->SetTexture(0,GET_GRAPHIC_DEVICE()->LoadTexture(work));
	sprite_3d_->SetAnchorPoint(float2(0.5f,1.0f));
	sprite_3d_->SetTexcoord(number_ / 2,2,1);
	sprite_3d_->Apply();
	height_ = 1.2f;
}

//=============================================================================
// destructor
//=============================================================================
PlayerIcon::~PlayerIcon(void)
{
}

//=============================================================================
// update
//=============================================================================
void PlayerIcon::Update(void)
{
	mesh_object_->SetPosition(float3(position_._x,position_._y + height_,position_._z));
}

//=============================================================================
// get object
//=============================================================================
PlayerIcon::TMeshObject PlayerIcon::GetObject(void) const
{
	return mesh_object_;
}

//=============================================================================
// set position
//=============================================================================
void PlayerIcon::SetPosition(const float3& in_position)
{
	position_ = in_position;
}

//---------------------------------- EOF --------------------------------------
