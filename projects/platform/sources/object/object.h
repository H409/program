//*****************************************************************************
//
// object
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_

//*****************************************************************************
// class declaration
//*****************************************************************************
class Object
{
public:
	// constructor
	Object(void);

	// destructor
	virtual ~Object(void) = default;

	// set position
	void SetPosition(const float3& in_position);
	void SetPosition(const f32& in_x,const f32& in_y,const f32& in_z);
	void SetPositionX(const f32& in_x);
	void SetPositionY(const f32& in_y);
	void SetPositionZ(const f32& in_z);

	// set rotation
	void SetRotation(const float3& in_rotation);
	void SetRotation(const f32& in_x,const f32& in_y,const f32& in_z);
	void SetRotationX(const f32& in_x);
	void SetRotationY(const f32& in_y);
	void SetRotationZ(const f32& in_z);

	// set scale
	void SetScale(const float3& in_scale);
	void SetScale(const f32& in_x,const f32& in_y,const f32& in_z);
	void SetScaleX(const f32& in_x);
	void SetScaleY(const f32& in_y);
	void SetScaleZ(const f32& in_z);

	// get position
	const float3& GetPosition(void)const;
	const f32& GetPositionX(void)const;
	const f32& GetPositionY(void)const;
	const f32& GetPositionZ(void)const;

	// get rotation
	const float3& GetRotation(void)const;
	const f32& GetRotationX(void)const;
	const f32& GetRotationY(void)const;
	const f32& GetRotationZ(void)const;

	// get scale
	const float3& GetScale(void)const;
	const f32& GetScaleX(void)const;
	const f32& GetScaleY(void)const;
	const f32& GetScaleZ(void)const;

	// get matrix
	const float4x4& GetMatrix(void);
	const float4x4& GetMatrix(void)const;

protected:
	float3 position_;
	float3 rotation_;
	float3 scale_;
	float4x4 matrix_;
	bool is_dirty_;
};

#endif // _OBJECT_H_

//---------------------------------- EOF --------------------------------------
