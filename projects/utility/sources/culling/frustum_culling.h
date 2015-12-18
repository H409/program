//*****************************************************************************
//
// frustam culling
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#pragma once
#ifndef _FRUSTAM_CULLING_H_
#define _FRUSTAM_CULLING_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace utility {
namespace culling {
class FrustumCulling
{
public:
	// constructor
	FrustumCulling(f32 in_angle,f32 in_aspect,f32 in_near,f32 in_far);

	// destructor
	virtual ~FrustumCulling(void);


	// 
	bool IsCulling(const float3& in_position,f32 in_radius)const;

	// 
	void SetViewMatrix(const float4x4& in_view_matrix);

private:
	f32 angle_;
	f32 aspect_;
	f32 near_;
	f32 far_;
	float4x4 view_matrix_;

	float4 left_plane_;
	float4 right_plane_;
	float4 top_plane_;
	float4 bottom_plane_;

	bool is_dirty_;

	void CreatePlane(void);
	//float4 CreateLeftPlane(void);
	float4 CreatePlane(const float3& in_point_a,const float3& in_point_b,const float3& in_point_c);
};
} // namespace culling
} // namespace utility

#endif // _FRUSTAM_CULLING_H_

	//---------------------------------- EOF --------------------------------------
