//*****************************************************************************
//
// float2
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _FLOAT2_H_
#define _FLOAT2_H_

//*****************************************************************************
// structure definition
//*****************************************************************************
struct float2
{
public:
	union
	{
		struct
		{
			f32 _x;
			f32 _y;
		};
	};

	// constructor
	float2(f32 xy = 0.0f);
	float2(f32 x,f32 y);
	float2(const float2& xy);

	// operator
	float2 operator+(void)const;
	float2 operator-(void)const;
	float2 operator*(const f32& value)const;
	float2 operator/(const f32& value)const;
	void operator*=(const f32& value);
	void operator/=(const f32& value);
	float2 operator+(const float2& xy)const;
	float2 operator-(const float2& xy)const;
	float2 operator*(const float2& xy)const;
	float2 operator/(const float2& xy)const;
	void operator+=(const float2& xy);
	void operator-=(const float2& xy);
	void operator*=(const float2& xy);
	void operator/=(const float2& xy);
};

#endif // _FLOAT2_H_

//---------------------------------- EOF --------------------------------------
