//*****************************************************************************
//
// float3
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _FLOAT3_H_
#define _FLOAT3_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "float2.h"

//*****************************************************************************
// structure definition
//*****************************************************************************
struct float3
{
public:
	union
	{
		struct
		{
			f32 _x;
			f32 _y;
			f32 _z;
		};
		struct
		{
			float2 _xy;
		};
	};

	// constructor
	float3(f32 xyz = 0.0f);
	float3(f32 x,f32 y,f32 z = 0.0f);
	float3(const float2& xy,f32 z = 0.0f);
	float3(const float3& xyz);

	// operator
	float3 operator+(void)const;
	float3 operator-(void)const;
	float3 operator*(const f32& value)const;
	float3 operator/(const f32& value)const;
	void operator*=(const f32& value);
	void operator/=(const f32& value);
	float3 operator+(const float3& xyz)const;
	float3 operator-(const float3& xyz)const;
	float3 operator*(const float3& xyz)const;
	float3 operator/(const float3& xyz)const;
	void operator+=(const float3& xyz);
	void operator-=(const float3& xyz);
	void operator*=(const float3& xyz);
	void operator/=(const float3& xyz);
};

#endif // _FLOAT3_H_

//---------------------------------- EOF --------------------------------------
