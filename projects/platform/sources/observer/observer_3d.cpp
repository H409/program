//*****************************************************************************
//
// observer 3D
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "observer_3d.h"
#include "math/math.h"

//=============================================================================
// constructor
//=============================================================================
Observer3D::Observer3D(const f32& in_radian,const f32& in_width,const f32& in_height)
{
	view_matrix_ = utility::math::Identity();
	projection_matrix_ = utility::math::PerspectiveFovLH(in_radian,in_width / in_height,1.0f,1000.0f);
	eye_ = float3(0.0f,5.0f,-5.0f);
	look_at_ = float3(0.0f,0.0f,0.0f);
	up_ = float3(0.0f,1.0f,0.0f);
	view_matrix_ = utility::math::LookAtLH(eye_,look_at_,up_);
}

//---------------------------------- EOF --------------------------------------
