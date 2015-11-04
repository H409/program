//*****************************************************************************
//
// float3
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "float3.h"

//=============================================================================
// constructor
//=============================================================================
float3::float3(f32 xyz)
{
	_xy = xyz;
	_z = xyz;
}

//=============================================================================
// constructor
//=============================================================================
float3::float3(f32 x,f32 y,f32 z)
{
	_x = x;
	_y = y;
	_z = z;
}

//=============================================================================
// constructor
//=============================================================================
float3::float3(const float2& xy,f32 z)
{
	_xy = xy;
	_z = z;
}

//=============================================================================
// constructor
//=============================================================================
float3::float3(const float3& xyz)
{
	_xy = xyz._xy;
	_z = xyz._z;
}

//=============================================================================
// operator
//=============================================================================
float3 float3::operator+(void)const
{
	return *this;
}

//=============================================================================
// operator
//=============================================================================
float3 float3::operator-(void)const
{
	return float3(-_xy,-_z);
}

//=============================================================================
// operator
//=============================================================================
float3 float3::operator*(const f32& value)const
{
	return float3(_xy * value,_z * value);
}

//=============================================================================
// operator
//=============================================================================
float3 float3::operator/(const f32& value)const
{
	f32 inv = 1.0f;

	if(value != 0.0f)
	{
		inv /= value;
	}

	return float3(_xy * inv,_z * inv);
}

//=============================================================================
// operator
//=============================================================================
void float3::operator*=(const f32& value)
{
	_xy *= value;
	_z *= value;
}

//=============================================================================
// operator
//=============================================================================
void float3::operator/=(const f32& value)
{
	f32 inv = 1.0f;

	if(value != 0.0f)
	{
		inv /= value;
	}

	_xy *= inv;
	_z *= inv;
}

//=============================================================================
// operator
//=============================================================================
float3 float3::operator+(const float3& xyz)const
{
	return float3(_xy + xyz._xy,_z + xyz._z);
}

//=============================================================================
// operator
//=============================================================================
float3 float3::operator-(const float3& xyz)const
{
	return float3(_xy - xyz._xy,_z - xyz._z);
}

//=============================================================================
// operator
//=============================================================================
float3 float3::operator*(const float3& xyz)const
{
	return float3(_xy * xyz._xy,_z * xyz._z);
}

//=============================================================================
// operator
//=============================================================================
float3 float3::operator/(const float3& xyz)const
{
	if(xyz._z == 0.0f)
	{
		return float3(_xy - xyz._xy,0.0f);
	}

	return float3(_xy - xyz._xy,_z - xyz._z);
}

//=============================================================================
// operator
//=============================================================================
void float3::operator+=(const float3& xyz)
{
	_xy += xyz._xy;
	_z += xyz._z;
}

//=============================================================================
// operator
//=============================================================================
void float3::operator-=(const float3& xyz)
{
	_xy -= xyz._xy;
	_z -= xyz._z;
}

//=============================================================================
// operator
//=============================================================================
void float3::operator*=(const float3& xyz)
{
	_xy *= xyz._xy;
	_z *= xyz._z;
}

//=============================================================================
// operator
//=============================================================================
void float3::operator/=(const float3& xyz)
{
	_xy /= xyz._xy;

	if(xyz._z != 0.0f)
	{
		_z /= xyz._z;
	}
	else
	{
		_z = 0.0f;
	}
}

//-----------------------------------EOF---------------------------------------