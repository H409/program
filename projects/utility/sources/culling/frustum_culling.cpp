//*****************************************************************************
//
// frustum culling
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#include "frustum_culling.h"
#include "math/math.h"

namespace utility {
namespace culling {
FrustumCulling::FrustumCulling(f32 in_angle,f32 in_aspect,f32 in_near,f32 in_far)
	:angle_(in_angle)
	,aspect_(in_aspect)
	,near_(in_near)
	,far_(in_far)
	,is_dirty_(true)
{
	view_matrix_ = utility::math::Identity();
	CreatePlane();
	is_dirty_ = false;
}

FrustumCulling::~FrustumCulling(void)
{
}

bool FrustumCulling::IsCulling(const float3& in_position,f32 in_radius) const
{
	if(in_radius == 0.0f)
	{
		return true;
	}

	f32 dist;
	float3 view_position;
	
	//--  ビュー空間Ｚ変換  --//	
	view_position._z = view_matrix_._13 * in_position._x + view_matrix_._23 * in_position._y + view_matrix_._33 * in_position._z + view_matrix_._43;

	//--  ニアクリップ平面より手前か  --//
	if((view_position._z + in_radius) < near_)
	{
		return false;
	}

	//--  ファークリップ平面より奥か  --//
	if((view_position._z - in_radius) > far_)
	{
		return false;
	}

	//--  ビュー空間Ｘ変換  --//
	view_position._x = view_matrix_._11 * in_position._x + view_matrix_._21 * in_position._y + view_matrix_._31 * in_position._z + view_matrix_._41;

	//--  左側面より左側か  --//
	dist = (view_position._x * left_plane_._x) + (view_position._z * left_plane_._z);

	if(dist > in_radius)
	{
		return false;
	}

	//--  右側面より右側か  --//
	dist = (view_position._x * right_plane_._x) + (view_position._z * right_plane_._z);

	if(dist > in_radius)
	{
		return false;
	}

	//--  ビュー空間Ｙ変換  --//
	view_position._y = view_matrix_._12 * in_position._x + view_matrix_._22 * in_position._y + view_matrix_._32 * in_position._z + view_matrix_._42 ;

	//--  上側面より上側か  --//
	dist = ( view_position._y * top_plane_._y ) + ( view_position._z * top_plane_._z );

	if(dist > in_radius)
	{
		return false;
	}

	//--  下側面より下側か  --//
	dist = ( view_position._y * bottom_plane_._y ) + ( view_position._z * bottom_plane_._z );

	if(dist > in_radius)
	{
		return false;
	}

	return true;
}
void FrustumCulling::SetViewMatrix(const float4x4 & in_view_matrix)
{
	view_matrix_ = in_view_matrix;
}

void FrustumCulling::CreatePlane(void)
{
	f32 tangent = tanf(angle_ * 0.9f);
	float3 point_a;
	float3 point_b;
	float3 point_c;

	point_a._x = 0.0f;
	point_a._y = 0.0f;
	point_a._z = 0.0f;

	point_b._x = -far_ * tangent / aspect_;
	point_b._y = -far_ * tangent;
	point_b._z = far_;

	point_c._x = point_b._x;
	point_c._y = -point_b._y;
	point_c._z = point_b._z;

	left_plane_ = CreatePlane(point_a,point_b,point_c);

	point_a._x = 0.0f;
	point_a._y = 0.0f;
	point_a._z = 0.0f;

	point_b._x = far_ * tangent / aspect_;
	point_b._y = far_ * tangent;
	point_b._z = far_;

	point_c._x = point_b._x;
	point_c._y = -point_b._y;
	point_c._z = point_b._z;

	right_plane_ = CreatePlane(point_a,point_b,point_c);

	point_a._x = 0.0f;
	point_a._y = 0.0f;
	point_a._z = 0.0f;

	point_b._x = -far_ * tangent / aspect_;
	point_b._y = far_ * tangent;
	point_b._z = far_;

	point_c._x = -point_b._x;
	point_c._y = point_b._y;
	point_c._z = point_b._z;

	top_plane_ = CreatePlane(point_a,point_b,point_c);

	point_a._x = 0.0f;
	point_a._y = 0.0f;
	point_a._z = 0.0f;

	point_b._x = far_ * tangent / aspect_;
	point_b._y = -far_ * tangent;
	point_b._z = far_;

	point_c._x = -point_b._x;
	point_c._y = point_b._y;
	point_c._z = point_b._z;

	bottom_plane_ = CreatePlane(point_a,point_b,point_c);
}

float4 FrustumCulling::CreatePlane(const float3 & in_point_a,const float3 & in_point_b,const float3 & in_point_c)
{
	float4 plane;
	float3 vector_a_b;
	float3 vector_a_c;
	float3 vector_cross;
	
	vector_a_b = in_point_b - in_point_a;
	vector_a_c = in_point_c - in_point_a;

	vector_cross = utility::math::CrossProduct(vector_a_b,vector_a_c);
	vector_cross = utility::math::Normalize(vector_cross);

	plane._x = vector_cross._x ;
	plane._y = vector_cross._y ;
	plane._z = vector_cross._z ;
	plane._w = -(vector_cross._x * in_point_a._x + vector_cross._y * in_point_a._y + vector_cross._z * in_point_a._z );

	return plane;
}
} // namespace culling
} // namespace utility

	//---------------------------------- EOF --------------------------------------
