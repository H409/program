//*****************************************************************************
//
// timer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
public:
	Timer(void);
	~Timer(void);

	void Update(void);

	void Draw(void);

	void Reset(void);

	u32 GetTimeLeft(void) const;
private:
	static const u32 DEFAULT_TIME_MAX;
	u32 time_max_;
	u32 time_count_;
	u32 time_left_;
};

#endif // _TIMER_H_

//---------------------------------- EOF --------------------------------------
