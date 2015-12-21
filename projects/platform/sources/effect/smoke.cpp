//*****************************************************************************
//
// smoke
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#include "smoke.h"
#include "action/move_to.h"
#include "mesh/sprite_3d.h"
#include "object/mesh_object.h"
#include "system/win_system.h"

Smoke::Smoke(void)
	:Effect()
{
	sprite_ = std::make_shared<mesh::Sprite3D>();
	sprite_->SetSize(float2(0.5f,0.5f));
	sprite_->SetAnchorPoint(float2(0.5f,0.5f));
	sprite_->Apply();
	mesh_object_ = std::make_shared<MeshObject>(sprite_);
	mesh_object_->SetTexture(0,GET_GRAPHIC_DEVICE()->LoadTexture("resources/texture/smoke.png"));
}

Smoke::~Smoke(void)
{
}

void Smoke::Update_(void)
{
}

//---------------------------------- EOF --------------------------------------
