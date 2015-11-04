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
// forward declaration
//*****************************************************************************
namespace action {
class Action;
}

namespace graphic {
namespace directx9 {
namespace texture {
class DX9Texture;
} // namespace texture
} // namespace directx9
} // namespace graphic

//*****************************************************************************
// class declaration
//*****************************************************************************
class Object
{
public:
	using TAction = std::shared_ptr<action::Action>;
	using TObject = std::shared_ptr<Object>;
	using TTexture = std::shared_ptr<graphic::directx9::texture::DX9Texture>;

	// constructor
	Object(void);

	// destructor
	virtual ~Object(void) = default;

	// update
	void Update(void);

	// draw
	virtual void Draw(void) {}

	// run action
	void RunAction(TAction in_action);

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

	// set color
	void SetColor(const float3& in_color);
	void SetColor(const f32& in_red,const f32& in_green,const f32& in_blue);
	void SetColor(const float4& in_color);
	void SetColor(const f32& in_red,const f32& in_green,const f32& in_blue,const f32& in_alpha);

	// set texture
	void SetTexture(const u32& in_number,TTexture in_texture);

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

	// get color
	const float4& GetColor(void)const;
	const float3& GetColorRGB(void)const;
	const f32& GetColorRed(void)const;
	const f32& GetColorGreen(void)const;
	const f32& GetColorBlue(void)const;
	const f32& GetColorAlpha(void)const;

	// get matrix
	const float4x4& GetMatrix(void);
	const float4x4& GetMatrix(void)const;

	// get texture
	TTexture GetTexture(const u32& in_number);

protected:
	static const u32 TEXTURE_MAX;

	float3 position_;
	float3 rotation_;
	float3 scale_;
	float4x4 matrix_;
	float4 color_;
	bool is_dirty_;
	TAction action_;
	u32 priority_;
	std::vector<TTexture> textures_;

};

#endif // _OBJECT_H_

//---------------------------------- EOF --------------------------------------
