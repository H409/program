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

	virtual ~Action(void) = default;

	// update
	void Update(void);
	u32 Update(const u32& in_delta_time);

	// get position
	const float3& GetPosition(void)const;

	// get time
	const u32& GetTime(void)const;

	// is end
	bool IsEnd(void)const;

	// get reverse
	virtual TAction GetReverse(void)const = 0;

	// set start position
	void SetStartPosition(const float3& in_position);

	// is pause
	bool IsPause(void)const;

	// start
	void Start(void);

	// pause
	void Pause(void);

protected:
	Action(void);
	explicit Action(const u32& in_duration);

	u32 duration_;
	float3 position_;
	u32 time_count_;
	bool is_end_;
	float3 start_position_;

private:
	virtual void Update_(const u32& in_delta_time) = 0;
	bool is_pause_;
};

} // namespace action

#endif // _ACTION_H_

	//---------------------------------- EOF --------------------------------------
