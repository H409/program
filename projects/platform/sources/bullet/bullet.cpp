//*****************************************************************************
//
// bullet
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "bullet.h"
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
Bullet::Bullet(const float3& in_start_position,const float3& in_end_position,const TYPE in_type)
	:position_(in_start_position)
	,start_position_(in_start_position)
	,end_position_(in_end_position)
	,speed_(0.2f)
	,type_(in_type)
	,tag_(0)
	,is_death_(false)
{
	sprite_3d_ = std::make_shared<mesh::Sprite3D>(float2(0.5f,0.5f));
	mesh_object_ = std::make_shared<MeshObject>(sprite_3d_);
	mesh_object_->SetTexture(0,GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/test.png"));
	mesh_object_->SetPosition(position_);
	sprite_3d_->SetAnchorPoint(float2(0.5f,0.5f));
	sprite_3d_->Apply();
}

//=============================================================================
// destructor
//=============================================================================
Bullet::~Bullet(void)
{
}

//=============================================================================
// update
//=============================================================================
void Bullet::Update(void)
{
	if(!is_death_)
	{
		auto vector = utility::math::Normalize(end_position_ - start_position_);

		position_ += vector * speed_;
		mesh_object_->SetPosition(position_);
	}
}

void Bullet::Remove(void)
{
	is_death_ = true;
}

bool Bullet::IsDeath(void)const
{
	return is_death_;
}

//=============================================================================
// set tag
//=============================================================================
void Bullet::SetTag(const u32 in_tag)
{
	tag_ = in_tag;
}

//=============================================================================
// get object
//=============================================================================
Bullet::TMeshObject Bullet::GetObject(void) const
{
	return mesh_object_;
}

//=============================================================================
// get position
//=============================================================================
const float3& Bullet::GetPosition(void) const
{
	return position_;
}

const Bullet::TYPE& Bullet::GetType(void) const
{
	return type_;
}

const u32& Bullet::GetTag(void) const
{
	return tag_;
}

//---------------------------------- EOF --------------------------------------
