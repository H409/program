//*****************************************************************************
//
// float4
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _FLOAT4_H_
#define _FLOAT4_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "float3.h"

//*****************************************************************************
// structure definition
//*****************************************************************************
struct float4
{
public:
	union
	{
		struct
		{
			f32 _x;
			f32 _y;
			f32 _z;
			f32 _w;
		};
		struct
		{
			f32 _r;
			f32 _g;
			f32 _b;
			f32 _a;
		};
		struct
		{
			f32 _left;
			f32 _right;
			f32 _top;
			f32 _bottom;
		};
		struct
		{
			float2 _xy;
		};
		struct
		{
			float3 _rgb;
		};
		struct
		{
			float3 _xyz;
		};
	};

	// constructor
	float4(f32 x = 0.0f,f32 y = 0.0f,f32 z = 0.0f,f32 w = 0.0f);
	float4(const float2& xy,f32 z = 0.0f,f32 w = 0.0f);
	float4(const float3& xyz,f32 w = 0.0f);
	float4(const float4& xyzw);

	// operator
	float4 operator+(void)const;
	float4 operator-(void)const;
	float4 operator*(const f32& value)const;
	float4 operator/(const f32& value)const;
	void operator*=(const f32& value);
	void operator/=(const f32& value);
	float4 operator+(const float4& xyzw)const;
	float4 operator-(const float4& xyzw)const;
	float4 operator*(const float4& xyzw)const;
	float4 operator/(const float4& xyzw)const;
	void operator+=(const float4& xyzw);
	void operator-=(const float4& xyzw);
	void operator*=(const float4& xyzw);
	void operator/=(const float4& xyzw);
};

#endif // _FLOAT4_H_

//---------------------------------- EOF --------------------------------------
