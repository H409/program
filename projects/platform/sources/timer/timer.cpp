//*****************************************************************************
//
// timer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#include "timer.h"
#include "develop_tool/develop_tool.h"

const u32 Timer::DEFAULT_TIME_MAX = 60 * 60 * 3;

Timer::Timer(void)
	:time_count_(0)
	,time_max_(DEFAULT_TIME_MAX)
{
}

Timer::~Timer(void)
{
}

void Timer::Update(void)
{
	time_count_++;

	time_left_ = (time_max_ - time_count_) / 60;
	DEVELOP_DISPLAY("Žc‚èŽžŠÔ : %d\n",time_left_);
}

void Timer::Reset(void)
{
	time_count_ = 0;
}

//---------------------------------- EOF --------------------------------------
