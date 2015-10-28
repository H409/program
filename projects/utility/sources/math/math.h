//*****************************************************************************
//
// math
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MATH_H_
#define _MATH_H_

namespace utility {
namespace math {
//*****************************************************************************
// constant definition
//*****************************************************************************
const f64 PI = (3.1415926535897932386);
const f64 OVER_RT2 = (0.7071067811865475);
const f64 LOG2 = (0.693147180559945309147);

//*****************************************************************************
// prototype definition
//*****************************************************************************
// length
f32 Length(const float2& vector);
f32 Length(const float3& vector);
f32 Length(const float4& vector);

// distance
f32 Distance(const float2& vector1,const float2& vector2);
f32 Distance(const float3& vector1,const float3& vector2);
f32 Distance(const float4& vector1,const float4& vector2);

// normalize
float2 Normalize(const float2& vector);
float3 Normalize(const float3& vector);
float4 Normalize(const float4& vector);

// dot product
f32 DotProduct(const float2& vector1,const float2& vector2);
f32 DotProduct(const float3& vector1,const float3& vector2);
f32 DotProduct(const float4& vector1,const float4& vector2);

// cross prucuct
f32 CrossProduct(const float2& vector1,const float2& vector2);
float3 CrossProduct(const float3& vector1,const float3& vector2);
float4 CrossProduct(const float4& vector1,const float4& vector2);// HACK

// saturate
f32 Saturate(const f32& x);
float2 Saturate(const float2& xy);
float3 Saturate(const float3& xyz);
float4 Saturate(const float4& xyzw);

// identity
float4x4 Identity(void);

// multiply
float4x4 Multiply(const float4x4& in_matrix1,const float4x4& in_matrix2);
float4 Multiply(const float4& in_vector,const float4x4& in_matrix);//HACK

// scaling
float4x4 Scaling(const float3& xyz);

// yaw pitch roll
float4x4 YawPitchRoll(const float3& xyz);

// tlanslation
float4x4 Tlanslation(const float3& xyz);

// ortho left hand
float4x4 OrthoLH(const f32& in_width,const f32& in_height,const f32& in_near,const f32& in_far);

// ortho right hand
float4x4 OrthoRH(const f32& in_width,const f32& in_height,const f32& in_near,const f32& in_far);

// perspective left hand
float4x4 PerspectiveFovLH(const f32& in_radian,const f32& in_aspect,const f32& in_near,const f32& in_far);

// perspective right hand
float4x4 PerspectiveFovRH(const f32& in_radian,const f32& in_aspect,const f32& in_near,const f32& in_far);

// look at left hand
float4x4 LookAtLH(const float3& in_eye,const float3& in_look_at,const float3& in_up);

// look at right hand
float4x4 LookAtRH(const float3& in_eye,const float3& in_look_at,const float3& in_up);

// to radian
// 角度から弧度法に変換
f32 ToRadian(const f32& in_degree);

// to degree
// 弧度法から角度に変換
f32 ToDegree(const f32& in_radian);

// create normal
// 3頂点から法線を求める
float3 CreateNormal(const float3& in_point_a,const float3& in_point_b,const float3& in_point_c);

// minimum
template<class T> T Minimum(const T& in_value1,const T& in_value2)
{
	T minimum = in_value2;

	if(in_value1 < in_value2)
	{
		minimum = in_value1;
	}

	return minimum;
}

// maximum
template<class T> T Maximum(const T& in_value1,const T& in_value2)
{
	T maximum = in_value2;

	if(in_value1 > in_value2)
	{
		maximum = in_value1;
	}

	return maximum;
}

// clamp
template<class T> T Clamp(const T& in_value,const T& in_minimum,const T& in_maximum)
{
	DEBUG_ASSERT_EXP(in_minimum >= in_maximum,"in_minimum < in_maximum\n");

	if(in_minimum >= in_maximum)
	{
		return in_value;
	}

	return Maximum(Minimum(in_value,in_maximum),in_minimum);
}

// wrap
template<class T> T Wrap(const T& in_value,const T& in_minimum,const T& in_maximum)
{
	T wrap = in_value;

	DEBUG_ASSERT_EXP(in_minimum >= in_maximum,"in_minimum < in_maximum\n");

	if(in_value < in_minimum)
	{
		wrap = Wrap(in_maximum - (in_minimum - in_value),in_minimum,in_maximum);
	}

	if(in_value > in_maximum)
	{
		wrap = Wrap(in_minimum + (in_value - in_maximum),in_minimum,in_maximum);
	}

	return wrap;
}

} // math
} // utility

#endif	// _MATH_H_

//---------------------------------- EOF --------------------------------------
