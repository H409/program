//*****************************************************************************
//
// fade
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#pragma once
#ifndef _FADE_H_
#define _FADE_H_

namespace mesh {
class Sprite;
} // namespace mesh
class MeshObject;
class Observer2D;

class Fade
{
public:
	using TCallback = std::function<void(void)>;
	using TSprite = std::shared_ptr<mesh::Sprite>;
	using TMeshObject = std::shared_ptr<MeshObject>;
	using TObserver = std::shared_ptr<Observer2D>;

	enum class TYPE
	{
		NONE = -1,
		FADE_IN,
		FADE_OUT,
	};

	Fade(void);
	virtual ~Fade(void);

	void Update(void);

	void Draw(void);

	void SetColor(const float3& in_color);

	void Start(u32 in_frame,TYPE in_type,TCallback in_callback = nullptr);

	bool IsWork(void)const;
private:
	u32 frame_count_;
	u32 frame_;
	f32 alpha_;
	float3 color_;
	TCallback callback_;
	TYPE type_;
	bool is_work_;

	TSprite sprite_;
	TMeshObject mesh_object_;
	TObserver observer_;
};

#endif // _FADE_H_

//---------------------------------- EOF --------------------------------------
