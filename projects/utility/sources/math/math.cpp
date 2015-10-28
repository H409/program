//*****************************************************************************
//
// math
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "math.h"
#include <cmath>

namespace utility {
namespace math {
//=============================================================================
// length
//=============================================================================
f32 Length(const float2& vector)
{
	return sqrtf(vector._x * vector._x + vector._y * vector._y);
}

//=============================================================================
// length
//=============================================================================
f32 Length(const float3& vector)
{
	return sqrtf(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
}

//=============================================================================
// length
//=============================================================================
f32 Length(const float4& vector)
{
	return sqrtf(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z + vector._w * vector._w);
}

//=============================================================================
// distance
//=============================================================================
f32 Distance(const float2& vector1,const float2& vector2)
{
	return Length(vector2 - vector1);
}

//=============================================================================
// distance
//=============================================================================
f32 Distance(const float3& vector1,const float3& vector2)
{
	return Length(vector2 - vector1);
}

//=============================================================================
// distance
//=============================================================================
f32 Distance(const float4& vector1,const float4& vector2)
{
	return Length(vector2 - vector1);
}

//=============================================================================
// normalize
//=============================================================================
float2 Normalize(const float2& vector)
{
	f32 length = Length(vector);

	if(length == 0.0f)
	{
		return float2();
	}

	return vector / length;
}

//=============================================================================
// normalize
//=============================================================================
float3 Normalize(const float3& vector)
{
	f32 length = Length(vector);

	if(length == 0.0f)
	{
		return float3();
	}

	return vector / length;
}

//=============================================================================
// normalize
//=============================================================================
float4 Normalize(const float4& vector)
{
	f32 length = Length(vector);

	if(length == 0.0f)
	{
		return float4();
	}

	return vector / length;
}

//=============================================================================
// dot product
//=============================================================================
f32 DotProduct(const float2& vector1,const float2& vector2)
{
	return vector1._x * vector2._x + vector1._y * vector2._y;
}

//=============================================================================
// dot product
//=============================================================================
f32 DotProduct(const float3& vector1,const float3& vector2)
{
	return vector1._x * vector2._x + vector1._y * vector2._y + vector1._z * vector2._z;
}

//=============================================================================
// dot product
//=============================================================================
f32 DotProduct(const float4& vector1,const float4& vector2)
{
	return vector1._x * vector2._x + vector1._y * vector2._y + vector1._z * vector2._z + vector1._w * vector2._w;
}

//=============================================================================
// cross prucuct
//=============================================================================
f32 CrossProduct(const float2& vector1,const float2& vector2)
{
	return vector1._x * vector2._y - vector1._y * vector2._x;
}

//=============================================================================
// cross prucuct
//=============================================================================
float3 CrossProduct(const float3& vector1,const float3& vector2)
{
	float3 vector;

	vector._x = vector1._y * vector2._z - vector1._z * vector2._y;
	vector._y = vector1._z * vector2._x - vector1._x * vector2._z;
	vector._z = vector1._x * vector2._y - vector1._y * vector2._x;

	return vector;
}

//=============================================================================
// cross prucuct
//=============================================================================
float4 CrossProduct(const float4& vector1,const float4& vector2)
{
	return float4();
}

//=============================================================================
// saturate
//=============================================================================
f32 Saturate(const f32& x)
{
	if(x < 0.0f)
	{
		return 0.0f;
	}

	if(x > 1.0f)
	{
		return 1.0f;
	}

	return x;
}

//=============================================================================
// saturate
//=============================================================================
float2 Saturate(const float2& xy)
{
	return float2(Saturate(xy._x),Saturate(xy._y));
}

//=============================================================================
// saturate
//=============================================================================
float3 Saturate(const float3& xyz)
{
	return float3(Saturate(xyz._xy),Saturate(xyz._z));
}

//=============================================================================
// saturate
//=============================================================================
float4 Saturate(const float4& xyzw)
{
	return float4(Saturate(xyzw._xyz),Saturate(xyzw._w));
}

//=============================================================================
// identity
//=============================================================================
float4x4 Identity(void)
{
	float4x4 matrix;

	matrix._11 = 1.0f;
	matrix._22 = 1.0f;
	matrix._33 = 1.0f;
	matrix._44 = 1.0f;

	return matrix;
}

//=============================================================================
// multiply
//=============================================================================
float4x4 Multiply(const float4x4& matrix1,const float4x4& matrix2)
{
	float4x4 matrix;

	matrix._11 = matrix1._11 * matrix2._11 + matrix1._12 * matrix2._21 + matrix1._13 * matrix2._31 + matrix1._14 * matrix2._41;
	matrix._12 = matrix1._11 * matrix2._12 + matrix1._12 * matrix2._22 + matrix1._13 * matrix2._32 + matrix1._14 * matrix2._42;
	matrix._13 = matrix1._11 * matrix2._13 + matrix1._12 * matrix2._23 + matrix1._13 * matrix2._33 + matrix1._14 * matrix2._43;
	matrix._14 = matrix1._11 * matrix2._14 + matrix1._12 * matrix2._24 + matrix1._13 * matrix2._34 + matrix1._14 * matrix2._44;

	matrix._21 = matrix1._21 * matrix2._11 + matrix1._22 * matrix2._21 + matrix1._23 * matrix2._31 + matrix1._24 * matrix2._41;
	matrix._22 = matrix1._21 * matrix2._12 + matrix1._22 * matrix2._22 + matrix1._23 * matrix2._32 + matrix1._24 * matrix2._42;
	matrix._23 = matrix1._21 * matrix2._13 + matrix1._22 * matrix2._23 + matrix1._23 * matrix2._33 + matrix1._24 * matrix2._43;
	matrix._24 = matrix1._21 * matrix2._14 + matrix1._22 * matrix2._24 + matrix1._23 * matrix2._34 + matrix1._24 * matrix2._44;

	matrix._31 = matrix1._31 * matrix2._11 + matrix1._32 * matrix2._21 + matrix1._33 * matrix2._31 + matrix1._34 * matrix2._41;
	matrix._32 = matrix1._31 * matrix2._12 + matrix1._32 * matrix2._22 + matrix1._33 * matrix2._32 + matrix1._34 * matrix2._42;
	matrix._33 = matrix1._31 * matrix2._13 + matrix1._32 * matrix2._23 + matrix1._33 * matrix2._33 + matrix1._34 * matrix2._43;
	matrix._34 = matrix1._31 * matrix2._14 + matrix1._32 * matrix2._24 + matrix1._33 * matrix2._34 + matrix1._34 * matrix2._44;

	matrix._41 = matrix1._41 * matrix2._11 + matrix1._42 * matrix2._21 + matrix1._43 * matrix2._31 + matrix1._44 * matrix2._41;
	matrix._42 = matrix1._41 * matrix2._12 + matrix1._42 * matrix2._22 + matrix1._43 * matrix2._32 + matrix1._44 * matrix2._42;
	matrix._43 = matrix1._41 * matrix2._13 + matrix1._42 * matrix2._23 + matrix1._43 * matrix2._33 + matrix1._44 * matrix2._43;
	matrix._44 = matrix1._41 * matrix2._14 + matrix1._42 * matrix2._24 + matrix1._43 * matrix2._34 + matrix1._44 * matrix2._44;

	return matrix;
}

//=============================================================================
// multiply
//=============================================================================
float4 Multiply(const float4& vector,const float4x4& matrix)
{
	return float4();
}

//=============================================================================
// scaling
//=============================================================================
float4x4 Scaling(const float3& xyz)
{
	float4x4 matrix;

	matrix._11 = xyz._x;
	matrix._22 = xyz._y;
	matrix._33 = xyz._z;

	return matrix;
}

//=============================================================================
// yaw pitch roll
//=============================================================================
float4x4 YawPitchRoll(const float3& xyz)
{
	float4x4 matrix;
	f32 sin_x = sinf(xyz._x);
	f32 cos_x = cosf(xyz._x);
	f32 sin_y = sinf(xyz._y);
	f32 cos_y = cosf(xyz._y);
	f32 sin_z = sinf(xyz._z);
	f32 cos_z = cosf(xyz._z);

	matrix._11 = cos_y * cos_z - sin_x * sin_y * sin_z;
	matrix._12 = cos_y * sin_z + sin_x * sin_y * cos_z;
	matrix._13 = -cos_x * sin_y;
	matrix._21 = -cos_x * sin_z;
	matrix._22 = cos_x * cos_z;
	matrix._23 = sin_x;
	matrix._31 = sin_y * cos_z + cos_y * sin_x * sin_z;
	matrix._32 = sin_y * sin_z - cos_y * sin_x * cos_z;
	matrix._33 = cos_y * cos_x;

	return matrix;

}

//=============================================================================
// tlanslation
//=============================================================================
float4x4 Tlanslation(const float3& xyz)
{
	float4x4 matrix;

	matrix._41 = xyz._x;
	matrix._42 = xyz._y;
	matrix._43 = xyz._z;

	return matrix;
}

//=============================================================================
// ortho left hand
//=============================================================================
float4x4 OrthoLH(const f32& in_width,const f32& in_height,const f32& in_near,const f32& in_far)
{
	auto matrix = Identity();

	matrix._11 = 2.0f / in_width;
	matrix._22 = -2.0f / in_height;
	matrix._41 = -1.0f;
	matrix._42 = 1.0f;

	return matrix;
}

//=============================================================================
// ortho right hand
//=============================================================================
float4x4 OrthoRH(const f32& in_width,const f32& in_height,const f32& in_near,const f32& in_far)
{
	float4x4 matrix;

	matrix._11 = 2.0f / in_width;
	matrix._22 = 2.0f / in_height;
	matrix._33 = 1.0f / (in_near - in_far);
	matrix._43 = in_near * (1.0f / (in_near - in_far));

	return matrix;
}

//=============================================================================
// perspective left hand
//=============================================================================
float4x4 PerspectiveFovLH(const f32& in_radian,const f32 & in_aspect,const f32 & in_near,const f32 & in_far)
{
	float4x4 matrix = Identity();

	f32 div = tanf(in_radian * 0.5f);
	f32 far_minus_near = in_far - in_near;

	// ゼロチェック
	if((div >= -0.00005f && div <= 0.00005f) || far_minus_near <= 0.0f || in_aspect <= 0.f)
	{
		// 何もせずに返す
		return matrix;
	}

	// 行列に値を設定
	matrix._11 = 1.0f / (in_aspect * div);
	matrix._22 = 1.0f / div;
	matrix._33 = in_far / far_minus_near;
	matrix._34 = 1.0f;
	matrix._43 = -(in_far * in_near) / far_minus_near;
	matrix._44 = 0.0f;

	return matrix;
}

//=============================================================================
// perspective right hand
//=============================================================================
float4x4 PerspectiveFovRH(const f32& in_radian,const f32 & in_aspect,const f32 & in_near,const f32 & in_far)
{
	auto matrix = Identity();

	f32 div = tanf(in_radian * 0.5f);
	f32 far_minus_near = in_far - in_near;
	// ゼロチェック
	if((div >= -0.00005f && div <= 0.00005f) || far_minus_near <= 0.0f || in_aspect <= 0.f)
	{
		// 何もせずに返す
		return matrix;
	}

	// 行列に値を設定
	matrix._11 = 1.0f / (in_aspect * div);
	matrix._22 = 1.0f / div;
	matrix._33 = -(in_far + in_near) / far_minus_near;
	matrix._34 = -1.0f;
	matrix._43 = -2 * (in_far * in_near) / far_minus_near;
	matrix._44 = 0.0f;

	return matrix;
}

//=============================================================================
// look at left hand
//=============================================================================
float4x4 LookAtLH(const float3 & in_eye,const float3 & in_look_at,const float3 & in_up)
{
	auto matrix = Identity();
	// 注視ベクトル設定
	float3 norm_ray;	// 注視ベクトル
	float3 norm_right;	// 右方向ベクトル
	float3	norm_up;
	float3 inv_pos;

	norm_ray._x = in_look_at._x - in_eye._x;
	norm_ray._y = in_look_at._y - in_eye._y;
	norm_ray._z = in_look_at._z - in_eye._z;

	// 注視ベクトルを正規化
	norm_ray = Normalize(norm_ray);

	// 右方向ベクトルを算出
	norm_right = CrossProduct(in_up,norm_ray);

	// 正規化
	norm_right = Normalize(norm_right);

	// 上方向ベクトルを設定
	norm_up = CrossProduct(norm_ray,norm_right);

	// 現在の座標の逆位置を求める
	inv_pos._x = -(in_eye._x * norm_right._x + in_eye._y * norm_right._y + in_eye._z * norm_right._z);
	inv_pos._y = -(in_eye._x * norm_up._x + in_eye._y * norm_up._y + in_eye._z * norm_up._z);
	inv_pos._z = -(in_eye._x * norm_ray._x + in_eye._y * norm_ray._y + in_eye._z * norm_ray._z);

	// 行列に値を設定
	matrix._11 = norm_right._x;
	matrix._21 = norm_right._y;
	matrix._31 = norm_right._z;
	matrix._12 = norm_up._x;
	matrix._22 = norm_up._y;
	matrix._32 = norm_up._z;
	matrix._13 = norm_ray._x;
	matrix._23 = norm_ray._y;
	matrix._33 = norm_ray._z;
	matrix._41 = inv_pos._x;
	matrix._42 = inv_pos._y;
	matrix._43 = inv_pos._z;
	matrix._14 = 0.0f;
	matrix._24 = 0.0f;
	matrix._34 = 0.0f;
	matrix._44 = 1.0f;

	return matrix;
}

float4x4 LookAtRH(const float3 & in_eye,const float3 & in_look_at,const float3 & in_up)
{
	auto matrix = Identity();

	// 注視ベクトル設定
	float3 norm_ray;	// 注視ベクトル
	float3 norm_right;	// 右方向ベクトル
	float3 norm_up;
	float3 inv_pos;

	norm_ray._x = in_eye._x - in_look_at._x;
	norm_ray._y = in_eye._y - in_look_at._y;
	norm_ray._z = in_eye._z - in_look_at._z;

	// 注視ベクトルを正規化
	norm_ray = Normalize(norm_ray);

	// 右方向ベクトルを算出
	norm_right = CrossProduct(in_up,norm_ray);

	// 右方向ベクトルを正規化
	norm_right = Normalize(norm_right);

	// 上方向ベクトルを設定
	norm_up = CrossProduct(norm_ray,norm_right);

	// 現在の座標の逆位置を求める
	inv_pos._x = -(in_eye._x * norm_right._x + in_eye._y * norm_right._y + in_eye._z * norm_right._z);
	inv_pos._y = -(in_eye._x * norm_up._x + in_eye._y * norm_up._y + in_eye._z * norm_up._z);
	inv_pos._z = -(in_eye._x * norm_ray._x + in_eye._y * norm_ray._y + in_eye._z * norm_ray._z);

	// 行列に値を設定
	matrix._11 = norm_right._x;
	matrix._21 = norm_right._y;
	matrix._31 = norm_right._z;
	matrix._12 = norm_up._x;
	matrix._22 = norm_up._y;
	matrix._32 = norm_up._z;
	matrix._13 = norm_ray._x;
	matrix._23 = norm_ray._y;
	matrix._33 = norm_ray._z;
	matrix._41 = inv_pos._x;
	matrix._42 = inv_pos._y;
	matrix._43 = inv_pos._z;
	matrix._14 = 0.0f;
	matrix._24 = 0.0f;
	matrix._34 = 0.0f;
	matrix._44 = 1.0f;

	return matrix;
}

//=============================================================================
// to radian
//=============================================================================
f32 ToRadian(const f32& in_degree)
{
	static const f32 CONSTANT = static_cast<f32>(PI) / 180.0f;
	return in_degree * CONSTANT;
}

//=============================================================================
// to degree
//=============================================================================
f32 ToDegree(const f32 & in_radian)
{
	static const f32 CONSTANT = 180.0f / static_cast<f32>(PI);
	return in_radian * CONSTANT;
}

//=============================================================================
// create normal
//=============================================================================
float3 CreateNormal(const float3 & in_point_a,const float3 & in_point_b,const float3 & in_point_c)
{
	auto a_b = in_point_b - in_point_a;
	auto b_c = in_point_c - in_point_b;

	auto normal = Normalize(CrossProduct(a_b,b_c));

	return normal;
}

} // math
} // utility

//-----------------------------------EOF---------------------------------------
