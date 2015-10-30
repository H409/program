//*****************************************************************************
//
// action
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _ACTION_H_
#define _ACTION_H_

//*****************************************************************************
// class declaration
//*****************************************************************************
namespace action {
class Action
{
public:
	using TAction = std::shared_ptr<Action>;

	struct PARAM
	{
		float3 _position;
		float3 _rotation;
		float3 _scale;
		float4 _color;

		PARAM() {};
		void operator+=(const PARAM& in_param)
		{
			_position += in_param._position;
			_rotation += in_param._rotation;
			_scale += in_param._scale;
			_color += in_param._color;
		}
		PARAM operator+(const PARAM& in_param)const
		{
			PARAM param;
			param._position = _position + in_param._position;
			param._rotation = _rotation + in_param._rotation;
			param._scale = _scale + in_param._scale;
			param._color = _color + in_param._color;
			return param;
		}
		PARAM operator-(const PARAM& in_param)const
		{
			PARAM param;
			param._position = _position - in_param._position;
			param._rotation = _rotation - in_param._rotation;
			param._scale = _scale - in_param._scale;
			param._color = _color - in_param._color;
			return param;
		}
	};

	virtual ~Action(void) = default;

	// update
	void Update(void);
	u32 Update(const u32& in_delta_time);

	// get position
	const float3& GetPosition(void)const;

	// get time
	const u32& GetTime(void)const;

	// get param
	const PARAM& GetParam(void)const;

	// is end
	bool IsEnd(void)const;

	// get reverse
	virtual TAction GetReverse(void)const;

	// set start param
	void SetStartParam(const PARAM& in_param);

	// set start position
	void SetStartPosition(const float3& in_position);

	// is pause
	bool IsPause(void)const;

	// resume
	void Resume(void);

	// pause
	void Pause(void);

protected:
	Action(void);
	explicit Action(const u32& in_duration);

	u32 duration_;
	PARAM param_;
	u32 time_count_;
	bool is_end_;
	PARAM start_param_;
	float4x4 matrix_;

private:
	virtual void Update_(const u32& in_delta_time) = 0;
	virtual void SetStartParam_(const PARAM& in_param) {}
	bool is_pause_;
};

} // namespace action

#endif // _ACTION_H_

	//---------------------------------- EOF --------------------------------------
