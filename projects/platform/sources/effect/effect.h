//*****************************************************************************
//
// effect
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

namespace mesh {
class Sprite3D;
} // namespace mesh
class MeshObject;

class Effect
{
public:
	using TMeshObject = std::shared_ptr<MeshObject>;

	Effect(void);

	virtual ~Effect(void);

	void Update(void);

	void Start(u32 in_frame,const float3& in_start_position);

	TMeshObject GetObject(void)const;

	bool IsDeath(void) const;
protected:
	u32 frame_count_;
	u32 frame_;
	float3 start_position_;
	std::shared_ptr<mesh::Sprite3D> sprite_;
	TMeshObject mesh_object_;

	virtual void Update_(void) = 0;
private:
};

#endif // _EFFECT_H_

//---------------------------------- EOF --------------------------------------
